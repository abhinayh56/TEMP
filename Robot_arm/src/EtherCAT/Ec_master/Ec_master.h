#ifndef EC_MASTER_H
#define EC_MASTER_H

#include <ecrt.h>
#include <iostream>
#include <cstring>
#include "Ec_master_base.h"
#include "../../../utility/Data_type.h"
#include "../../../utility/Constants.h"

class Ec_master : public Ec_master_base
{
public:
    Ec_master();
    ~Ec_master();

    Ec_uint16 start() override;
    Ec_uint16 stop() override;
    Ec_uint16 update() override;

    Ec_uint16 set_state_initialize() override;
    Ec_uint16 set_state_pre_operational() override;
    Ec_uint16 set_state_safe_operational() override;
    Ec_uint16 set_state_operational() override;

    Ec_uint16 get_state() override;

    Ec_boolean is_initialized() override;
    Ec_boolean is_operational() override;

private:
    ec_master_t *master = nullptr;
    ec_domain_t *domain = nullptr;
    ec_slave_config_t *slave_config = nullptr;

    bool configure_master();
    bool configure_slaves();
    void check_domain_state();
    void check_master_state();
};

#endif // EC_MASTER_H