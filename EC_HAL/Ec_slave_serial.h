#ifndef EC_SLAVE_SERIAL_H
#define EC_SLAVE_SERIAL_H

#include "Ec_config.h"
#include "Ec_slave.h"

class Ec_slave_serial : public Ec_slave<T_slave_info>
{
public:
    Ec_slave_serial(T_slave_info info_) : Ec_slave<T_slave_info>(info_) {}
    ~Ec_slave_serial() {}

protected:
private:
};

#endif // EC_SLAVE_SERIAL_H
