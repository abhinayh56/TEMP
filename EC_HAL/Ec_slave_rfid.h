#ifndef EC_SLAVE_RFID_H
#define EC_SLAVE_RFID_H

#include "Ec_config.h"
#include "Ec_slave.h"

class Ec_slave_rfid : public Ec_slave<T_slave_info>
{
public:
    Ec_slave_rfid(T_slave_info info_) : Ec_slave<T_slave_info>(info_) {}
    ~Ec_slave_rfid() {}

protected:
private:
};

#endif // EC_SLAVE_RFID_H
