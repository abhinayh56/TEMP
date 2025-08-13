#ifndef EC_SLAVE_ADC_H
#define EC_SLAVE_ADC_H

#include "Ec_config.h"
#include "Ec_slave.h"

class Ec_slave_adc : public Ec_slave<T_slave_info>
{
public:
    Ec_slave_adc(T_slave_info info_) : Ec_slave<T_slave_info>(info_) {}
    ~Ec_slave_adc() {}

protected:
private:
};

#endif // EC_SLAVE_ADC_H
