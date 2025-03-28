#include "Ec_slave_4.h"

Ec_slave_4::Ec_slave_4(Slave_4::Param* param_)
{
    param = *param_;
}

Ec_slave_4::~Ec_slave_4()
{
}

void Ec_slave_4::config_slave()
{
    std::cout << "Configuring slave 4..." << std::endl;
}

void Ec_slave_4::config_publisher()
{
    std::cout << "Configuring publisher for slave 4..." << std::endl;
}

void Ec_slave_4::config_subscriber()
{
    std::cout << "Configuring subscriber for slave 4..." << std::endl;
}

void Ec_slave_4::config_rx_pdo()
{
    std::cout << "Configuring RX PDO for slave 4..." << std::endl;
}

void Ec_slave_4::config_tx_pdo()
{
    std::cout << "Configuring TX PDO for slave 4..." << std::endl;
}

void Ec_slave_4::read_tx_pdo()
{
    std::cout << "Reading TX PDO from slave 4..." << std::endl;
}

void Ec_slave_4::write_rx_pdo()
{
    std::cout << "Writing RX PDO to slave 4..." << std::endl;
}

void Ec_slave_4::transfer_tx_pdo()
{
    std::cout << "Transferring TX PDO from slave 4..." << std::endl;
}

void Ec_slave_4::transfer_rx_pdo()
{
    std::cout << "Transferring RX PDO to slave 4..." << std::endl;
}

void Ec_slave_4::check_slave_status()
{
    std::cout << "Checking status of slave 4..." << std::endl;
}
