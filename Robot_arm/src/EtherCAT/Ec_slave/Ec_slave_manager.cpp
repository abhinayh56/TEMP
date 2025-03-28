#include "Slave_manager.h"
#include <iostream>

void Slave_manager::add_slave(Ec_slave_base *slave)
{
    slaves.push_back(slave);
}

void Slave_manager::config()
{
#ifdef UPDATE_METHOD_SEQ
    for (auto &slave : slaves)
    {
        slave->check_slave_status();
        slave->config_slave();
        slave->config_subscriber();
        slave->config_publisher();
        slave->config_rx_pdo();
        slave->config_tx_pdo();
    }
#endif

#ifdef UPDATE_METHOD_PAR
    for (auto &slave : slaves)
    {
        slave->check_slave_status();
    }
    for (auto &slave : slaves)
    {
        slave->config_slave();
    }
    for (auto &slave : slaves)
    {
        slave->config_subscriber();
    }
    for (auto &slave : slaves)
    {
        slave->config_publisher();
    }
    for (auto &slave : slaves)
    {
        slave->config_rx_pdo();
    }
    for (auto &slave : slaves)
    {
        slave->config_tx_pdo();
    }
#endif
}

void Slave_manager::update()
{
#ifdef UPDATE_METHOD_SEQ
    for (auto &slave : slaves)
    {
        slave->check_slave_status();
        slave->read_tx_pdo();
        slave->transfer_tx_pdo();
        slave->transfer_rx_pdo();
        slave->write_rx_pdo();
    }
    std::cout << "---" << std::endl;
#endif

#ifdef UPDATE_METHOD_PAR
    for (auto &slave : slaves)
    {
        slave->check_slave_status();
    }
    std::cout << "---" << std::endl;
    for (auto &slave : slaves)
    {
        slave->read_tx_pdo();
    }
    std::cout << "---" << std::endl;
    for (auto &slave : slaves)
    {
        slave->transfer_tx_pdo();
    }
    std::cout << "---" << std::endl;
    for (auto &slave : slaves)
    {
        slave->transfer_rx_pdo();
    }
    std::cout << "---" << std::endl;
    for (auto &slave : slaves)
    {
        slave->write_rx_pdo();
    }
    std::cout << "---" << std::endl;
#endif
}

void Slave_manager::run()
{

    std::cout << "Initial configuration of slaves" << std::endl;
    config();

    std::cout << "\nContinuous function for slaves" << std::endl;
    while (true)
    {
        update();
        break;
    }
}
