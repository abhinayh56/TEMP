#include "Ec_slave_1.h"

Ec_slave_1::Ec_slave_1(Slave_1::Param* param_)
{
    param = *param_;
}

Ec_slave_1::~Ec_slave_1()
{
}

void Ec_slave_1::config_slave()
{
    std::cout << "------" << std::endl;
    std::cout << "Configuring slave 1..." << std::endl;
    std::cout << "a1: " << param.a1 << std::endl;
    std::cout << "a2: " << param.a2 << std::endl;
    std::cout << "a3: " << param.a3 << std::endl;
    std::cout << "a4: " << param.a4 << std::endl;
    std::cout << "a5: " << param.a5 << std::endl;
    std::cout << "------" << std::endl;
}

void Ec_slave_1::config_publisher()
{
    std::cout << "Configuring publisher for slave 1..." << std::endl;
}

void Ec_slave_1::config_subscriber()
{
    std::cout << "Configuring subscriber for slave 1..." << std::endl;
}

void Ec_slave_1::config_rx_pdo()
{
    std::cout << "Configuring RX PDO for slave 1..." << std::endl;
}

void Ec_slave_1::config_tx_pdo()
{
    std::cout << "Configuring TX PDO for slave 1..." << std::endl;
}

void Ec_slave_1::read_tx_pdo()
{
    std::cout << "Reading TX PDO from slave 1..." << std::endl;
}

void Ec_slave_1::write_rx_pdo()
{
    std::cout << "Writing RX PDO to slave 1..." << std::endl;
}

void Ec_slave_1::transfer_tx_pdo()
{
    std::cout << "Transferring TX PDO from slave 1..." << std::endl;
}

void Ec_slave_1::transfer_rx_pdo()
{
    std::cout << "Transferring RX PDO to slave 1..." << std::endl;
}

void Ec_slave_1::check_slave_status()
{
    std::cout << "Checking status of slave 1..." << std::endl;
}
