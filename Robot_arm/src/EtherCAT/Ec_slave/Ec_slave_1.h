#ifndef EC_SLAVE_1_H
#define EC_SLAVE_1_H

#include "Ec_slave_base.h"
#include <iostream>

namespace Slave_1
{
    struct Param
    {
        int a1 = 1;
        int a2 = 2;
        int a3 = 3;
        int a4 = 4;
        int a5 = 5;
    };
}

class Ec_slave_1 : public Ec_slave_base
{
private:
    Slave_1::Param param;

public:
    Ec_slave_1(Slave_1::Param* param_);
    ~Ec_slave_1();
    void config_slave() override;
    void config_publisher() override;
    void config_subscriber() override;
    void config_rx_pdo() override;
    void config_tx_pdo() override;
    void read_tx_pdo() override;
    void write_rx_pdo() override;
    void transfer_tx_pdo() override;
    void transfer_rx_pdo() override;
    void check_slave_status() override;
};

#endif // EC_SLAVE_1_H
