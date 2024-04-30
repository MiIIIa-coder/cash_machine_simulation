#include "../hdr/people.hpp"
#include "../hdr/simulation.hpp"
#include "../hdr/cash_machine.hpp"

#define ALL_TIME 100

//void ask_settings();

int main()
{

    sim::simulation my_settings{4, 10, 70000, 3, 1000, 60, 15, 5, 20, 6, 8, 36000, 10000};
    my_settings.initial();

    for (int clk = 0; clk < ALL_TIME; ++clk) {

        //pass through the vector of person
        int people_number = my_settings.get_number_people();
        for (int person_idx = 0; person_idx < people_number; ++person_idx) {
            //std::cout << person_idx << std::endl;
            if (!(my_settings.population[person_idx]->is_in_queue())) {
                peop::people* person = my_settings.population[person_idx].get();
                if (my_settings.population[person_idx]->deposit()) {
                    //std::cout << "I IN QUEUE!!!" << person_idx << std::endl;
                    if (!(my_settings.push_in_queue(person)))
                        my_settings.population[person_idx]->cancel_in_queue();
                }
                if (my_settings.population[person_idx]->withdraw()) {
                    //std::cout << "I IN QUEUE!!!" << person_idx << std::endl;
                    if (!(my_settings.push_in_queue(person)))
                        my_settings.population[person_idx]->cancel_in_queue();
                }
            }
            
        }

        std::cout << clk << std::endl;
        for (int index_c_m = 0; index_c_m < my_settings.get_number_cash_m(); ++index_c_m) {
            std::cout << my_settings.set_cash_m[index_c_m]->get_size_queue() << "  ";
            cash_m::cash_machine_resp c_m_resp = my_settings.set_cash_m[index_c_m]->service(clk);
            switch (c_m_resp) {
                case cash_m::IN_SERVICE:
                    break;
                
                case cash_m::BR_DOWN:
                    my_settings.cash_m_broke(index_c_m);
                    break;

                default:
                    break;
            }

        }
        std::cout << std::endl;
        
    }

    for (int index_c_m = 0; index_c_m < my_settings.get_number_cash_m(); ++index_c_m) {
            std::cout << my_settings.set_cash_m[index_c_m]->get_balance() << "  ";
        }
        std::cout << std::endl;

    return 0;
}

//void ask_settings(int& all_people, int& percent_adult, int& percent_homeless, int& percent_senior, int& percent_child) {}
