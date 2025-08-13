#ifndef EC_SLAVE_SERVO_H
#define EC_SLAVE_SERVO_H

#include "Ec_config.h"
#include "Ec_slave.h"

class Ec_slave_servo : public Ec_slave<T_slave_info>
{
public:
    Ec_slave_servo(T_slave_info info_) : Ec_slave<T_slave_info>(info_) {}
    ~Ec_slave_servo() {}

protected:
private:
};

#endif // EC_SLAVE_SERVO_H
