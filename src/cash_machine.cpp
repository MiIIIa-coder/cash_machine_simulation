#include "../hdr/cash_machine.hpp"

namespace cash_m {

    void  cash_machine::init_cash_m(int& initial_money_c_m, int& max_size_queue_, int& work_ability_) {
        balance = initial_money_c_m;
        max_queue_size = max_size_queue_;
        new_interect = true;
        time_end_interect = -1;
        broke = false;
        work_ability = work_ability_;
    }

    std::size_t cash_machine::get_size_queue() const { return queue_.size(); }

    void cash_machine::add_in_queue(peop::people* person) { queue_.push(person); }

    cash_machine_resp cash_machine::service(int clk_time) {
        int delay = -1, money = 0;
        peop::interection_type inter_type;
        //std::cout << "DELAY = " << delay << " MONEY = " << money << std::endl;

        if (new_interect && !(queue_.empty())) {
            inter_type = queue_.front()->interection(delay, money);
            std::cout << "DELAY = " << delay << " MONEY = " << money << std::endl;
            if (inter_type == peop::NOP) {
                std::cout << "POPA" << std::endl;
                { queue_.pop(); }
                return IN_SERVICE; 
            }
            new_interect = false;
            time_end_interect = clk_time + delay;
            balance += money;
            work_ability -= 1;

            if (balance < 0) {     //return before clk
                balance -= money;
                new_interect = true;
                time_end_interect = clk_time;
                queue_.front()->cancel_c_m(inter_type);
                return LACK_MONEY;
            }
        }

        if (work_ability == 0) {
            std::cout << "ATM IS DEAD" << std::endl;
            broke = true;
            return BR_DOWN;
        }

        if (clk_time != (time_end_interect-1))
            return IN_SERVICE;
        new_interect = true;

        return IN_SERVICE;
    }

}