#include "../hdr/people.hpp"
#include "../hdr/simulation.hpp"
#include "../hdr/cash_machine.hpp"


#define ALL_TIME 4320

int main()
{
    std::cout << sim::start_simulation(4, 10, 5000000, 10000, 300, 60, 15, 5, 20, 3, 4, 100, 10000, 2) << std::endl;
    
    return 0;
}

