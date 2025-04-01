#ifndef EC_MASTER_H
#define EC_MASTER_H

#include <ecrt.h>
#include <iostream>
#include <cstring>
#include "../../../utility/Data_type.h"
#include "../../../utility/Constants.h"

namespace Ec
{
    enum State
    {
        UNKNOWN = 0,
        BOOTSTRAP = 1,
        ERROR = 2,
        INIT = 3,
        PREOP = 4,
        SAFE_OP = 5,
        OP = 6
    };

    enum Return_status
    {
        SUCCESS = 0,
        FAILURE = 1,
    };
}

class Ec_master
{
public:
    Ec_master();
    ~Ec_master();

    Ec_uint16 start();
    Ec_uint16 stop();
    Ec_uint16 update();

    Ec_uint16 set_state_initialize();
    Ec_uint16 set_state_pre_operational();
    Ec_uint16 set_state_safe_operational();
    Ec_uint16 set_state_operational();

    Ec_uint16 set_state(const Ec_uint16 state);
    Ec_uint16 get_state();

    Ec_boolean is_initialized();
    Ec_boolean is_operational();

    bool config();
    void check_domain_state();
    void check_master_state();

private:
    ec_master_t *master = nullptr;
    ec_domain_t *domain = nullptr;
    ec_slave_config_t *slave_config = nullptr;

    Ec_boolean ec_initialized = Ec_false;
    Ec_boolean ec_operational = Ec_false;
};

#endif // EC_MASTER_H