#include "../hdr/people.hpp"

namespace peop {

    void people::init_person(int& deposit, int& withdraw, int& sec_per_usr, int& max_money_user, int& max_attemts_user) {
        in_queue = false;
        in_queue_count = 0;
        time_queued_in = 0;
        happyness = 100;
        delay_deposit = deposit;
        delay_withdraw = withdraw;
        sec_per_user = sec_per_usr;
        max_money = max_money_user;
        max_attemts = max_attemts_user;

        deposit_interect  = false;
        withdraw_interect = false;
        attemts = 0;
    }

    bool people::deposit() {
        if (want_interection(sec_per_user)) {
            deposit_interect = true;
            money_deposit = money_quantity_action(max_money);
            in_queue = true;
            return true;
        }
        return false;
    }

    bool people::withdraw() {
        if (want_interection(sec_per_user)) {
            withdraw_interect = true;
            money_withdraw = (-1)*money_quantity_action(max_money);
            in_queue = true;
            return true;
        }
        return false;
    }

    bool people::want_interection(int& sec_per_user) const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 10000);
        double prob = dist(gen)*sec_per_user/double(10000);
        return (prob < 1);
    }

    int money_quantity_action(int& max_money) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, max_money);
        return dist(gen);
    }

    void people::failed_attemt() {
        attemts += 1;
    }

    interection_type people::interection(int& delay, int& money) {

        //std::cout << "in interection" << std::endl;

        if (deposit_interect) {

            //std::cout << "in deposit_interection" << std::endl;

            delay = delay_deposit;
            money = money_deposit;
            deposit_interect = false;
            return DEPOSIT;
        } 

        //std::cout << "in interection after deposit" << std::endl;

        if (withdraw_interect) {
            delay = delay_withdraw;
            money = money_withdraw;
            withdraw_interect = false;
            return WITHDRAW;
        } 

        //std::cout << "in interection after withdraw" << std::endl;

        delay = -1; 
        money = 0;
        return NOP;
    }

    void people::cancel_c_m(interection_type inter) {  //for c_m

        //std::cout << "cancel_c_m" << std::endl;

        switch (inter)
        {
        case DEPOSIT:
            deposit_interect = true;
            break;

        case WITHDRAW:
            withdraw_interect = true;
            break;
        
        default:
            break;
        }
    }

    void people::cancel_in_queue() {

        //std::cout << "cancel_in_queue" << std::endl;

        in_queue = false;
        attemts  = 0;
        deposit_interect  = false;
        withdraw_interect = false;
    }

}