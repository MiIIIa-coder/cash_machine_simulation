#include "simualtion.hpp"

namespace sim {
    void simulation::initial() {

        int index = 0;

        //PEOPLE
        population.reserve(all_people_);
        for (; index < all_people_ * percent_adult_/100; ++index) {

            population.push_back(std::make_unique<peop::adult>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_);
        }

        for (; index < all_people_ * percent_homeless_/100; ++index) {
            population.push_back(std::make_unique<peop::homeless>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_);
        }

        for (; index < all_people_ * percent_senior_/100; ++index) {
            population.push_back(std::make_unique<peop::senior>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_);
        }

        for (; index < all_people_ * percent_child_/100; ++index) {
            population.push_back(std::make_unique<peop::child>());
            population.back()->init_person(delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_);
        }

        index = 0;

        //CASH MASHINES
        set_cash_m.reserve(number_cash_m_);
        for (; index < number_cash_m_; ++index) {
            set_cash_m.push_back(std::make_unique<cash_m::cash_machine>());
            set_cash_m.back()->init_cash_m(initial_money_c_m_, max_size_queue_);
        }

    }

    bool simulation::push_in_queue(int& const person_idx) {
        std::vector<int> vctr_size_queues {number_cash_m_};

        //FIND MIN QUEUE
        for (int index = 0; index < number_cash_m_; ++index) {
            vctr_size_queues[index] = set_cash_m[index]->get_size_queue();
        }

        int min_size = *(std::min_element(vctr_size_queues.begin(), vctr_size_queues.end()));

        if (min_size > get_max_size_queue()) 
            return false;

        //ADDING IN MIN QUEUE
        for (int index = 0; index < number_cash_m_; ++index) {
            if (vctr_size_queues[index] == min_size)
                set_cash_m[index]->add_in_queue(population[person_idx]);
        }   

        return true;  
    }

}