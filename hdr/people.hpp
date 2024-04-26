#ifndef people_h
#define people_h

#include <iostream>
#include <random>

//#include "simualtion.hpp"
//#include "cash_machine.h"

namespace peop {

   class people {
      public:
         
         virtual bool deposit ();
         virtual bool withdraw();
         bool want_interection(int& sec_per_user) const;  //sec_per_user - time in seconds for one user of cash machine on averadge

         void init_person(int& deposit, int& withdraw, int& sec_per_usr, int& max_money_user) {
            in_queue = false;
            happyness = 100;
            dealy_deposit = deposit;
            delay_withdraw = withdraw;
            sec_per_user = sec_per_usr;
            max_money = max_money_user;

            deposit_interect  = false;
            withdraw_interect = false;
         }

         bool is_in_queue () const { return in_queue; }
         void add_in_queue_deposit (int& money_dep);
         void add_in_queue_withdraw(int& money_wit);
      
      private:
         bool in_queue;
         int  happyness;
         int  dealy_deposit;    //time in cach mashine
         int  delay_withdraw;   //time in cach mashine
         int  sec_per_user;
         int  max_money;

      private:
         bool deposit_interect;
         int money_deposit;
         bool withdraw_interect;
         int money_withdraw;
   };

   class adult : public people {

   };

   class child : public people {

   };

   class homeless : public people {

   };

   class senior : public people {

   };

   int money_quantity_action(int& max_money);

}

#endif // people_h