#ifndef EC_CONFIG_H
#define EC_CONFIG_H

#include <string>

struct Slave_info_struct
{
    int address;
    std::string name;
};

typedef Slave_info_struct T_slave_info;

#endif // EC_CONFIG_H
