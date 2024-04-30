#ifndef cash_machine_h
#define cash_machine_h

#include <queue>

//#include "simulation.hpp"
#include "people.hpp"

namespace cash_m {

   enum cash_machine_resp {IN_SERVICE, BR_DOWN, LACK_MONEY};

   class cash_machine final {
      private:
         int balance;
         int max_queue_size;
         int work_ability;  //if = 0 => broke
         bool broke;
         
         std::queue<peop::people*> queue_;

      public:
         void init_cash_m(int& initial_money_c_m, int& max_size_queue_, int& work_ability_);

         std::size_t  get_size_queue() const;
         void add_in_queue(peop::people* person);
         const peop::people* get_front() { return queue_.front(); }
         void pop_front() { queue_.pop(); }
         int get_balance() { return balance; }
         bool is_work() { return !broke; }

         cash_machine_resp service(int clk_time);

      private:
         bool new_interect;  //wait new consumer
         int time_interect;
         int time_end_interect;

   };

}

#endif // cash_machine_h