#include "../hdr/simulation.hpp"

#define ALL_TIME 4320

namespace sim {

    std::string start_simulation(int number_cash_m, int max_size_queue, int initial_money_c_m, int work_ability,
            int all_people, int percent_adult, int percent_homeless, int percent_senior, 
            int percent_child, int delay_deposit_ad, int delay_withdraw_ad, 
            int sec_per_user_ad, int max_money_ad, int max_attemts) { 
        
        std::vector<int> sum_queue_length;
         sim::simulation my_settings{number_cash_m, max_size_queue, initial_money_c_m, work_ability,
            all_people, percent_adult, percent_homeless, percent_senior, 
            percent_child, delay_deposit_ad, delay_withdraw_ad, 
            sec_per_user_ad, max_money_ad, max_attemts};
        my_settings.initial();

        std::ofstream file("log.txt", std::ios::out);
        if (file.is_open()) {

        for (int clk = 0; clk < ALL_TIME; ++clk) {
            
            file << "\n" << clk << std::endl;
            std::queue<std::pair<int, peop::people*>> queue_inter_people;

            //pass through the vector of person
            int people_number = my_settings.get_number_people();
            #pragma omp parallel for
            for (int person_idx = 0; person_idx < people_number; ++person_idx) {            
                if (!(my_settings.population[person_idx]->is_in_queue())) {

                    my_settings.population[person_idx]->deposit();
                    my_settings.population[person_idx]->withdraw();

                    if (my_settings.population[person_idx]->is_in_queue()) {
                        peop::people* person = my_settings.population[person_idx].get();
                        std::pair<int, peop::people*> q_pair_el(person_idx, person);
                        queue_inter_people.push(q_pair_el);
                        //if (!(my_settings.push_in_queue(person)))
                            //my_settings.population[person_idx]->cancel_in_queue();
                        //else
                            //std::cout << "ADDED in QUEUE  pers# " << person_idx << std::endl;
                    }
                    
                }   
            }

            //std::cout << queue_inter_people.size() << std::endl;
            std::size_t q_inter_size = queue_inter_people.size();
            for (int q_person_idx = 0; static_cast<std::size_t>(q_person_idx) < q_inter_size; ++q_person_idx) {
                auto q_elt = queue_inter_people.front();
                if (!(my_settings.push_in_queue(q_elt.second)))
                    my_settings.population[q_elt.first]->cancel_in_queue();
                else
                    file << "ADDED in QUEUE  pers# " << q_elt.first << std::endl;
                queue_inter_people.pop();
            }

            //std::cout << queue_inter_people.size() << std::endl;
            //std::cout << std::endl;

            file << "befor " << std::endl;
            for (int person_idx = 0; person_idx < people_number; ++person_idx) {
                if (my_settings.population[person_idx]->is_in_queue()) {
                    file << "pers idx = " << person_idx << "  ";
                }
            }
            file << std::endl;

            for (int index_c_m = 0; index_c_m < my_settings.get_number_cash_m(); ++index_c_m) {
                file << "queue size: " << my_settings.set_cash_m[index_c_m]->get_size_queue() << "  ";

                int queue_length = my_settings.set_cash_m[index_c_m]->get_size_queue();

                sum_queue_length.push_back(queue_length);
                
                file << std::endl;

                cash_m::cash_machine_resp c_m_resp = my_settings.set_cash_m[index_c_m]->service(clk);

                switch (c_m_resp) {
                    case cash_m::IN_SERVICE:
                        break;
                    
                    case cash_m::LACK_MONEY:
                        std::cout << "LACK MONEY" << std::endl;
                        my_settings.first_change_queue(index_c_m);
                        break;
                    
                    case cash_m::BR_DOWN:
                        my_settings.cash_m_broke(index_c_m);
                        break;

                    default:
                        break;
                }
                file << "after queue size: " << my_settings.set_cash_m[index_c_m]->get_size_queue() << "  ";
                file << std::endl;

            }
            //std::cout << std::endl;
            for (int person_idx = 0; person_idx < people_number; ++person_idx) {
                if (my_settings.population[person_idx]->is_in_queue()) {
                    file << "pers idx = " << person_idx << "  ";
                    my_settings.population[person_idx]->increment_time_in_queue();
                }
            }
            file << std::endl;
        
        }

        //BALANCE CASH MICHINES
        for (int index_c_m = 0; index_c_m < my_settings.get_number_cash_m(); ++index_c_m) {
                std::cout << my_settings.set_cash_m[index_c_m]->get_balance() << "  ";
            }
            std::cout << std::endl;
        
        std::cout << "TIME " << std::endl;
        int people_number = my_settings.get_number_people();
        for (int person_idx = 0; person_idx < people_number; ++person_idx) {
            if (my_settings.population[person_idx]->get_queue_count() != 0)
            std::cout << my_settings.population[person_idx]->get_queue_time()/my_settings.population[person_idx]->get_queue_count() << " <-> " << person_idx << "    ";
        }

        std::cout << std::endl;
        int c = 0;
        for (int person_idx = 0; person_idx < people_number; ++person_idx) {
            if (my_settings.population[person_idx]->get_queue_count() > -1) {
                std::cout << my_settings.population[person_idx]->get_queue_count() << " <-> " << person_idx << "    ";
            }

            if (my_settings.population[person_idx]->get_queue_count() > 0) {
                ++c;
            }
        }

        std::cout << c << " <- c" << std::endl;
        file.close();
        } else {
            std::cout << "ERROR OPEN FILE\n";
            //exception
        }

        // calculating average length & wait_time 

        int sum_time = 0;
        int sum_attempts = 0;

        // calculating sum time in queue ( sum_time ) and sum amount of attempts of using ATM 
        // of people who was in queue at least once
        int people_number = my_settings.get_number_people();
        for (int person_idx = 0; person_idx < people_number; ++person_idx) {
            if (my_settings.population[person_idx]->get_queue_count() != 0) {
                sum_time += my_settings.population[person_idx]->get_queue_time();
                sum_attempts += my_settings.population[person_idx]->get_queue_count();
            }
        }

        float aver_queue_length = float(std::accumulate(sum_queue_length.begin(), sum_queue_length.end(), 0)) / number_cash_m / ALL_TIME;
        float aver_customer_wait_time = static_cast<float>(sum_time / float(sum_attempts));  

        // returning results
        std::string result = "Average queue length = " + floatToString(aver_queue_length) + "\n" +
                                "Average waiting time = " + floatToString(aver_customer_wait_time) + "\n";
        
        return result; 
    }

//---------------------------------------------------------------------------

    void simulation::initial() {

        int index = 0;
        int offset = 0;

        //PEOPLE
        population.reserve(all_people_);
        for (; index < all_people_ * percent_adult_/100; ++index) {
            population.push_back(std::make_unique<peop::adult>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_, max_attemts_);
        }
        offset += index;

        for (; index < offset + all_people_ * percent_homeless_/100; ++index) {
            population.push_back(std::make_unique<peop::homeless>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_, max_attemts_);
        }
        offset += index;

        for (; index < offset + all_people_ * percent_senior_/100; ++index) {
            population.push_back(std::make_unique<peop::senior>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_, max_attemts_);
        }
        offset += index;

        for (; index < offset + all_people_ * percent_child_/100; ++index) {
            population.push_back(std::make_unique<peop::child>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_, max_attemts_);
        }

        index = 0;

        //CASH MASHINES
        set_cash_m.reserve(number_cash_m_);
        for (; index < number_cash_m_; ++index) {
            set_cash_m.push_back(std::make_unique<cash_m::cash_machine>());
            set_cash_m.back()->init_cash_m(initial_money_c_m_, max_size_queue_, work_ability_);
        }

    }

    bool simulation::push_in_queue(peop::people* person) {

        //std::cout << "push_in_queue\n"<< std::endl;


        std::vector<int> vctr_size_queues(number_cash_m_);

        //FIND MIN QUEUE
        for (int index = 0; index < number_cash_m_; ++index) {
            if (set_cash_m[index]->is_work())
                vctr_size_queues[index] = set_cash_m[index]->get_size_queue();
        }

        if (vctr_size_queues.size() < 1)
            return false;

        int min_size = *(std::min_element(vctr_size_queues.begin(), vctr_size_queues.end()));

        if (min_size >= get_max_size_queue()) 
            return false;

        //ADDING IN MIN QUEUE
        for (int index = 0; index < number_cash_m_; ++index) {
            if (set_cash_m[index]->is_work() && vctr_size_queues[index] == min_size) {
                set_cash_m[index]->add_in_queue(person);
                person->increment_queue_count();
                break;
            }
        }   

        return true;  
    }

    bool simulation::push_in_queue(peop::people* person, int& index_c_m) {
        
        //std::cout << "push_in_queue_for_c_m\n"<< std::endl;

        std::vector<int> vctr_size_queues(number_cash_m_);

        //FIND MIN QUEUE
        for (int index = 0; index < number_cash_m_; ++index) {
            if (set_cash_m[index]->is_work() && index != index_c_m)
                vctr_size_queues[index] = set_cash_m[index]->get_size_queue();
        }

        int min_size = *(std::min_element(vctr_size_queues.begin(), vctr_size_queues.end()));

        if (min_size >= get_max_size_queue()) 
            return false;

        //ADDING IN MIN QUEUE
        for (int index = 0; index < number_cash_m_; ++index) {
            if (set_cash_m[index]->is_work() && index != index_c_m && vctr_size_queues[index] == min_size) {
                set_cash_m[index]->add_in_queue(person);
                break;
            }
        }   

        return true; 
    }

    void simulation::first_change_queue(int& index_c_m) {

        //std::cout << "first_change_queue\n"<< std::endl;

        if (set_cash_m[index_c_m]->get_size_queue() > 0) {
            peop::people* first_pers = const_cast<peop::people*>(set_cash_m[index_c_m]->get_front());
            first_pers->failed_attemt();
            if (first_pers->get_attemts() <= max_attemts_) {
                if (!(push_in_queue(first_pers, index_c_m)))
                    first_pers->cancel_in_queue();
            } else {
                first_pers->cancel_in_queue();
            }
            
            std::cout << "POPA1" << std::endl;
            set_cash_m[index_c_m]->pop_front();
        }
    }

    void simulation::cash_m_broke(int& index_c_m) {
        while (set_cash_m[index_c_m]->get_size_queue() != 0) {
            first_change_queue(index_c_m);
        }
    }

    std::string floatToString(float value){
        std::ostringstream result;
        result << std::fixed << std::setprecision(2) << value;
        return result.str();
    }

}