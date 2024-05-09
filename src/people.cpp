#include "../hdr/people.hpp"

namespace peop {

    void people::init_person(int& deposit, int& withdraw, int& sec_per_usr, int& max_money_user, int& max_attemts_user) {
        in_queue = false;
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
        //std::cout << "probabil = " << prob << std::endl;
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
        if (deposit_interect) {
            delay = delay_deposit;
            money = money_deposit;
            deposit_interect = false;
            return DEPOSIT;
        } 

        if (withdraw_interect) {
            delay = delay_withdraw;
            money = money_withdraw;
            withdraw_interect = false;
            return WITHDRAW;
        } 

        delay = -1; 
        money = 0;
        return NOP;
    }

    void people::cancel_c_m(interection_type inter) {  //for c_m
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
        in_queue = false;
        attemts = 0;
        deposit_interect  = false;
        withdraw_interect = false;
    }

}