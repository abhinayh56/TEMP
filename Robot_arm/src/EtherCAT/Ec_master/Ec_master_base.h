#ifndef EC_MASTER_BASE_H
#define EC_MASTER_BASE_H

#include "iostream"
#include "../../../utility/Data_type.h"
#include "../../../utility/Constants.h"
#include "../../../libraries/Timer/Timer.h"

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

    enum Status
    {
        STATUS_1 = 1,
        STATUS_2 = 2,
        STATUS_3 = 3,
        STATUS_4 = 4,
        STATUS_5 = 5
    };

    struct Timeout_esm_us
    {
        Ec_uint64 timeout_preop = 3000;
        Ec_uint64 timeout_safeop_op = 10000;
        Ec_uint64 timeout_back_2_safeop = 200;
        Ec_uint64 timeout_back_2_init = 5000;
        Ec_uint64 timeout_max = 30000;
    };

    struct Param
    {
        Ec_string mac_address = "";
        Ec_string network_adapter = "";
        Ec_string eni_file_name = "";
        Ec_string eni_file_path = "";
        Ec_uint64 cycle_time_ns = 4000000;
        Timeout_esm_us timeout_esm_us = {3000000, 10000000, 200000, 5000000, 30000000};
        Ec_uint16 esm_attemp_max = 10;
    };
}

class Ec_master_base
{
public:
    Ec_uint16 config(const Ec::Param param);

    Ec_uint16 validate_param();
    Ec_uint16 validate_eni();
    Ec_string get_mac_addr() const;
    Ec_string get_network_adapter() const;
    Ec_string get_eni_file_name() const;
    Ec_string get_eni_file_path() const;

    virtual Ec_uint16 start() = 0;
    virtual Ec_uint16 stop() = 0;
    virtual Ec_uint16 update() = 0;
    virtual Ec_uint16 set_state_initialize() = 0;
    virtual Ec_uint16 set_state_pre_operational() = 0;
    virtual Ec_uint16 set_state_safe_operational() = 0;
    virtual Ec_uint16 set_state_operational() = 0;
    virtual Ec_uint16 get_state()= 0;
    virtual Ec_boolean is_initialized() = 0;
    virtual Ec_boolean is_operational() = 0;

    Ec_uint16 set_state(const Ec_uint16 state);

protected:
    Ec_uint16 ec_master_state = Ec::State::UNKNOWN;
    Ec_boolean ec_initialized = Ec_false;
    Ec_boolean ec_operational = Ec_false;
    Ec_uint16 status;

private:
    Ec_string mac_address = "";
    Ec_string network_adapter = "";
    Ec_string eni_file_name = "";
    Ec_string eni_file_path = "";
    Ec_uint64 cycle_time_ns = 4000000;
    Ec_uint64 timeout_preop = 3000;
    Ec_uint64 timeout_safeop_op = 10000;
    Ec_uint64 timeout_back_2_safeop = 200;
    Ec_uint64 timeout_back_2_init = 5000;
    Ec_uint64 timeout_max = 30000;
    Ec_uint64 timeout_exceed_flag = Ec_false;
    Ec_uint16 esm_attemp_max = 10;

    Ec_uint16 esm(const Ec_uint16 requested_state);
};

#endif // EC_MASTER_BASE_H