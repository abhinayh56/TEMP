#include "Ec_slave_2.h"

Ec_slave_2::Ec_slave_2(Slave_2::Param* param_)
{
    param = *param_;
}

Ec_slave_2::~Ec_slave_2()
{
}

void Ec_slave_2::config_slave()
{
    std::cout << "Configuring slave 2..." << std::endl;
}

void Ec_slave_2::config_publisher()
{
    std::cout << "Configuring publisher for slave 2..." << std::endl;
}

void Ec_slave_2::config_subscriber()
{
    std::cout << "Configuring subscriber for slave 2..." << std::endl;
}

void Ec_slave_2::config_rx_pdo()
{
    std::cout << "Configuring RX PDO for slave 2..." << std::endl;
}

void Ec_slave_2::config_tx_pdo()
{
    std::cout << "Configuring TX PDO for slave 2..." << std::endl;
}

void Ec_slave_2::read_tx_pdo()
{
    std::cout << "Reading TX PDO from slave 2..." << std::endl;
}

void Ec_slave_2::write_rx_pdo()
{
    std::cout << "Writing RX PDO to slave 2..." << std::endl;
}

void Ec_slave_2::transfer_tx_pdo()
{
    std::cout << "Transferring TX PDO from slave 2..." << std::endl;
}

void Ec_slave_2::transfer_rx_pdo()
{
    std::cout << "Transferring RX PDO to slave 2..." << std::endl;
}

void Ec_slave_2::check_slave_status()
{
    std::cout << "Checking status of slave 2..." << std::endl;
}
