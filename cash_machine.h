#ifndef cash_machine_h
#define cash_machine_h

#include <queue>

#include "simualtion.hpp"
#include "people.h"

namespace cash_m {

   class cash_machine final {
      public:
         void init_cash_m(int& initial_money_c_m, int& max_size_queue_) {
            money = initial_money_c_m;
            max_queue_size = max_size_queue_;
         }

         std::size_t  get_size_queue() const { return queue_.size(); }
         void add_in_queue(std::unique_ptr<peop::people> person) { queue_.push(person); }
      
      private:
         int money;
         int max_queue_size;
         int work_ability;  //if = 0 => broke
         
         std::queue<std::unique_ptr<peop::people>> queue_;
   };

}

#endif // cash_machine_h