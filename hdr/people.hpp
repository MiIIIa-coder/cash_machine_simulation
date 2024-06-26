#ifndef people_h
#define people_h

#include <iostream>
#include <random>

//#include "simualtion.hpp"
//#include "cash_machine.h"

namespace peop {

   enum interection_type {NOP, DEPOSIT, WITHDRAW}; 

   class people {
      public:
         
         virtual bool deposit ();
         virtual bool withdraw();
         bool want_interection(int& sec_per_user) const;  //sec_per_user - time in seconds for one user of cash machine on averadge

         void increment_queue_count  () { ++in_queue_count; }
         void increment_time_in_queue() { ++time_queued_in; }

         void init_person(int& deposit, int& withdraw, int& sec_per_usr, int& max_money_user, int& max_attemts_user);

      public:
         bool is_in_queue () const { return in_queue; }
         int get_delay_deposit()  { return delay_deposit; }
         int get_money_deposit()  { return money_deposit; }
         int get_delay_withdraw() { return delay_withdraw; }
         int get_money_withdraw() { return money_withdraw; }
         bool  is_deposit_inter() { return deposit_interect; }
         bool is_withdraw_inter() { return withdraw_interect; }
         int get_attemts()  const { return attemts; }

         interection_type interection(int& delay, int& money);
         void cancel_c_m(interection_type inter);
         void cancel_in_queue();
         void failed_attemt();

         int  get_queue_time()     const { return time_queued_in; }
         int  get_queue_count()    const {return in_queue_count;  }
         void set_time_queued_in(int time) { time_queued_in = time; }

         void print_dep_inter() const { std::cout << deposit_interect << std::endl; }


      private:
         bool in_queue;
         int  in_queue_count;
         int  happyness;
         int  delay_deposit;    //time in cach mashine
         int  delay_withdraw;   //time in cach mashine
         int  sec_per_user;
         int  max_money;
         int  max_attemts;

         int  time_queued_in;

      private:
         bool deposit_interect;
         int money_deposit;
         bool withdraw_interect;
         int money_withdraw;

         int attemts;
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