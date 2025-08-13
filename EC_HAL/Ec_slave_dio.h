#ifndef EC_SLAVE_DIO_H
#define EC_SLAVE_DIO_H

#include "Ec_config.h"
#include "Ec_slave.h"

class Ec_slave_dio : public Ec_slave<T_slave_info>
{
public:
    Ec_slave_dio(T_slave_info info_) : Ec_slave<T_slave_info>(info_) {}
    ~Ec_slave_dio() {}

protected:
private:
};

#endif // EC_SLAVE_DIO_H
