#include "people.h"

namespace peop {

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
            money_withdraw = money_quantity_action(max_money);
            in_queue = true;
            return true;
        }
        return false;
    }

    bool people::want_interection(int& sec_per_user) const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, RAND_MAX);
        return (dist(gen)*sec_per_user/RAND_MAX < 1);
    }

    int money_quantity_action(int& const max_money) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, max_money);
        return dist(gen);
    }

}