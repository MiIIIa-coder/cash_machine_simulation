#include <iostream>

#include "people.h"
#include "simualtion.hpp"
#include "cash_machine.h"

#define ALL_TIME 1000

//void ask_settings();

int main()
{
    //int all_people, percent_adult, percent_homeless, percent_senior, percent_child;
    //ask_settings();

    sim::simulation my_settings{2, 5, 70000, 100, 70, 5, 5, 20, 300, 350, 360, 10000};
    my_settings.initial();

    for (int clk = 0; clk < ALL_TIME; ++clk) {

        //pass through the vector of person
        int people_number = my_settings.get_number_people();
        for (int person_idx = 0; person_idx < people_number; ++person_idx) {
            if (!(my_settings.population[person_idx]->is_in_queue())) {
                if (my_settings.population[person_idx]->deposit())
                    my_settings.push_in_queue(person_idx);
                my_settings.population[person_idx]->withdraw();
            }
        }
    }

    return 0;
}

//void ask_settings(int& all_people, int& percent_adult, int& percent_homeless, int& percent_senior, int& percent_child) {}
