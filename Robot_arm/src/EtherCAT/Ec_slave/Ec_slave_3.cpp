#include "Ec_slave_3.h"

Ec_slave_3::Ec_slave_3(Slave_3::Param* param_)
{
    param = *param_;
}

Ec_slave_3::~Ec_slave_3()
{
}

void Ec_slave_3::config_slave()
{
    std::cout << "Configuring slave 3..." << std::endl;
}

void Ec_slave_3::config_publisher()
{
    std::cout << "Configuring publisher for slave 3..." << std::endl;
}

void Ec_slave_3::config_subscriber()
{
    std::cout << "Configuring subscriber for slave 3..." << std::endl;
}

void Ec_slave_3::config_rx_pdo()
{
    std::cout << "Configuring RX PDO for slave 3..." << std::endl;
}

void Ec_slave_3::config_tx_pdo()
{
    std::cout << "Configuring TX PDO for slave 3..." << std::endl;
}

void Ec_slave_3::read_tx_pdo()
{
    std::cout << "Reading TX PDO from slave 3..." << std::endl;
}

void Ec_slave_3::write_rx_pdo()
{
    std::cout << "Writing RX PDO to slave 3..." << std::endl;
}

void Ec_slave_3::transfer_tx_pdo()
{
    std::cout << "Transferring TX PDO from slave 3..." << std::endl;
}

void Ec_slave_3::transfer_rx_pdo()
{
    std::cout << "Transferring RX PDO to slave 3..." << std::endl;
}

void Ec_slave_3::check_slave_status()
{
    std::cout << "Checking status of slave 3..." << std::endl;
}
