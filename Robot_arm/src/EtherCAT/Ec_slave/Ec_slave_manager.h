#ifndef SLAVE_MANAGER_H
#define SLAVE_MANAGER_H

#include "Ec_slave_base.h"
#include <vector>

// #define UPDATE_METHOD_SEQ 1
#define UPDATE_METHOD_PAR 1

class Slave_manager
{
private:
    std::vector<Ec_slave_base *> slaves;

public:
    // Add slaves dynamically
    void add_slave(Ec_slave_base *slave);

    // Configure all slaves
    void config();

    // Run update functions of all slaves
    void update();

    // Run all functions of all slaves
    void run();
};

#endif // SLAVE_MANAGER_H
