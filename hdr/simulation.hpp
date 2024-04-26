#ifndef simul_h
#define simul_h

#include <vector>
#include <memory>
#include <algorithm>

#include "people.hpp"
#include "cash_machine.hpp"

namespace sim {

    enum interection {DEPOSIT, WITHDRAW};

    struct simulation {
        private:
            int number_cash_m_, max_size_queue_, initial_money_c_m_;
            int all_people_, percent_adult_, percent_homeless_, percent_senior_, percent_child_;
            int delay_deposit_ad_, delay_withdraw_ad_, sec_per_user_ad_, max_money_ad_;

        public:
            //int -> double
            simulation(
           int number_cash_m, int max_size_queue, int initial_money_c_m,
           int all_people, int percent_adult, int percent_homeless, int percent_senior, 
           int percent_child, int delay_deposit_ad, int delay_withdraw_ad, 
           int sec_per_user_ad, int max_money_ad) 
           : number_cash_m_(number_cash_m), max_size_queue_(max_size_queue), initial_money_c_m_(initial_money_c_m),
             all_people_(all_people), percent_adult_(percent_adult), percent_homeless_(percent_homeless), 
             percent_senior_(percent_senior), percent_child_(percent_child), delay_deposit_ad_(delay_deposit_ad), 
             delay_withdraw_ad_(delay_withdraw_ad), sec_per_user_ad_(sec_per_user_ad), max_money_ad_(max_money_ad)  {}


            void initial();  //initial vector of people and cash_mashines

            int  get_number_people () const { return all_people_;    }
            int  get_number_cash_m () const { return number_cash_m_; }
            int  get_max_size_queue() const { return max_size_queue_;}  //ret from user's settings value, not max_size in all queues

            bool push_in_queue(int& person_idx);

            std::vector<std::unique_ptr<peop::people>> population;
            std::vector<std::unique_ptr<cash_m::cash_machine>> set_cash_m;
    };
}

#endif // simul_h