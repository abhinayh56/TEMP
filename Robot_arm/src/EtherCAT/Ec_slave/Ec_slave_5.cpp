#include "Ec_slave_5.h"

Ec_slave_5::Ec_slave_5(Slave_5::Param* param_)
{
    param = *param_;
}

Ec_slave_5::~Ec_slave_5()
{
}

void Ec_slave_5::config_slave()
{
    std::cout << "Configuring slave 5..." << std::endl;
}

void Ec_slave_5::config_publisher()
{
    std::cout << "Configuring publisher for slave 5..." << std::endl;
}

void Ec_slave_5::config_subscriber()
{
    std::cout << "Configuring subscriber for slave 5..." << std::endl;
}

void Ec_slave_5::config_rx_pdo()
{
    std::cout << "Configuring RX PDO for slave 5..." << std::endl;
}

void Ec_slave_5::config_tx_pdo()
{
    std::cout << "Configuring TX PDO for slave 5..." << std::endl;
}

void Ec_slave_5::read_tx_pdo()
{
    std::cout << "Reading TX PDO from slave 5..." << std::endl;
}

void Ec_slave_5::write_rx_pdo()
{
    std::cout << "Writing RX PDO to slave 5..." << std::endl;
}

void Ec_slave_5::transfer_tx_pdo()
{
    std::cout << "Transferring TX PDO from slave 5..." << std::endl;
}

void Ec_slave_5::transfer_rx_pdo()
{
    std::cout << "Transferring RX PDO to slave 5..." << std::endl;
}

void Ec_slave_5::check_slave_status()
{
    std::cout << "Checking status of slave 5..." << std::endl;
}
