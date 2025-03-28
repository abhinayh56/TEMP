#ifndef EC_MASTER_BASE_H
#define EC_MASTER_BASE_H

#include "iostream"
#include "../../../utility/Data_type.h"
#include "../../../utility/Constants.h"

namespace Ec_master
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
        UNKNOWN = 3
    };

    struct Timeout_esm
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
        Timeout_esm timeout_esm = {3000, 10000, 200, 5000, 30000};
        Ec_uint16 esm_attemp_max = 10;
    };
}

class Ec_master_base
{
public:
    Ec_uint16 set_mac_addr(Ec_string &mac_address_);
    Ec_string get_mac_addr() const;

    Ec_uint16 set_network_adapter(Ec_string &network_adapter_);
    Ec_string get_network_adapter() const;

    Ec_uint16 set_eni_file_name(const Ec_string &eni_file_name_);
    Ec_string get_eni_file_name() const;

    Ec_uint16 set_eni_file_path(const Ec_string &eni_file_path_);
    Ec_string get_eni_file_path() const;

    Ec_uint16 config(const Ec_master::Param param);
    Ec_uint16 validate_param();
    Ec_uint16 validate_eni();

    virtual Ec_uint16 start() = 0;
    virtual Ec_uint16 stop() = 0;
    virtual Ec_uint16 update() = 0;
    virtual Ec_uint16 status() = 0;

    Ec_uint16 set_state(const Ec_uint16 state);
    Ec_uint16 get_state();

    virtual const Ec_boolean is_running() const = 0;
    virtual const Ec_boolean is_initialized() const = 0;
    virtual const Ec_boolean is_operational() const = 0;

protected:
    Ec_uint16 set_state_machine_timeout(const Ec_master::Timeout_esm timeout);
    Ec_uint16 esm(const Ec_uint16 requested_state);
    Ec_uint16 set_state_initialize(const Ec_uint64 timeout);
    Ec_uint16 set_state_pre_operational(const Ec_uint64 timeout);
    Ec_uint16 set_state_safe_operational(const Ec_uint64 timeout);
    Ec_uint16 set_state_operational(const Ec_uint64 timeout);

    Ec_uint16 ec_master_state = Ec_master::State::UNKNOWN;
    Ec_boolean ec_running = Ec_false;
    Ec_boolean ec_initialized = Ec_false;
    Ec_boolean ec_operational = Ec_false;

private:
    Ec_string mac_address = "";
    Ec_string network_adapter = "";
    // master = pysoem.Master()
    // pdo_layout

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
};

#endif // EC_MASTER_BASE_H