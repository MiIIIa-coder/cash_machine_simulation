#ifndef simul_h
#define simul_h

#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <numeric> // for std::accumulate in average queue length calculating

#include <omp.h>


#include "people.hpp"
#include "cash_machine.hpp"

namespace sim {

    struct simulation {
        private:
            int number_cash_m_, max_size_queue_, initial_money_c_m_, work_ability_;
            int all_people_, percent_adult_, percent_homeless_, percent_senior_, percent_child_;
            int delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_;
            int max_attemts_;

            std::vector<int> time_service;


        public:
            //int -> double
            simulation(
           int number_cash_m, int max_size_queue, int initial_money_c_m, int work_ability,
           int all_people, int percent_adult, int percent_homeless, int percent_senior, 
           int percent_child, int delay_deposit_ad, int delay_withdraw_ad, 
           int sec_per_user_ad, int max_money_ad, int max_attemts) 
           : number_cash_m_(number_cash_m), max_size_queue_(max_size_queue), initial_money_c_m_(initial_money_c_m), work_ability_(work_ability),
             all_people_(all_people), percent_adult_(percent_adult), percent_homeless_(percent_homeless), 
             percent_senior_(percent_senior), percent_child_(percent_child), delay_deposit_ad_(delay_deposit_ad), 
             delay_withdraw_ad_(delay_withdraw_ad), sec_per_user_ad_(sec_per_user_ad), max_money_ad_(max_money_ad), max_attemts_(max_attemts)  {}

            void initial();  //initial vector of people and cash_mashines

            int  get_number_people () const { return all_people_;    }
            int  get_number_cash_m () const { return number_cash_m_; }
            int  get_max_size_queue() const { return max_size_queue_;}  //ret from user's settings value, not max_size in all queues

            bool push_in_queue(peop::people* person);
            bool push_in_queue(peop::people* person, int& index_c_m);  //NOT in queue of index_c_m
            void first_change_queue(int& index_c_m);
            void cash_m_broke(int& index_c_m);

            std::vector<std::unique_ptr<peop::people>> population;
            std::vector<std::unique_ptr<cash_m::cash_machine>> set_cash_m;
    };

    std::string start_simulation(int number_cash_m, int max_size_queue, int initial_money_c_m, int work_ability,
                                int all_people, int percent_adult, int percent_homeless, int percent_senior,
                                int percent_child, int delay_deposit_ad, int delay_withdraw_ad,
                                int sec_per_user_ad, int max_money_ad, int max_attemts);

    std::string floatToString(float value);
}

#endif // simul_h