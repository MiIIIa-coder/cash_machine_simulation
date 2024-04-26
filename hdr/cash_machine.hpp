#ifndef cash_machine_h
#define cash_machine_h

#include <queue>

#include "simulation.hpp"
#include "people.hpp"

namespace cash_m {

   class cash_machine final {
      private:
         int money;
         int max_queue_size;
         int work_ability;  //if = 0 => broke
         
         std::queue<peop::people*> queue_;

      public:
         void init_cash_m(int& initial_money_c_m, int& max_size_queue_) {
            money = initial_money_c_m;
            max_queue_size = max_size_queue_;
         }

         std::size_t  get_size_queue() const { return queue_.size(); }
         void add_in_queue(peop::people* person) { queue_.push(person); }
      
   };

}

#endif // cash_machine_h