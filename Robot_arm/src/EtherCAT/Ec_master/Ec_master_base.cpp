#include "Ec_master_base.h"

Ec_uint16 Ec_master_base::config(const Ec_master::Param param)
{
    Ec_uint16 ret_val = Ec_master::Return_status::SUCCESS;

    mac_address = param.mac_address;
    network_adapter = param.network_adapter;
    eni_file_name = param.eni_file_name;
    eni_file_path = param.eni_file_path;
    cycle_time_ns = param.cycle_time_ns;
    timeout_preop = param.timeout_esm_us.timeout_preop;
    timeout_safeop_op = param.timeout_esm_us.timeout_safeop_op;
    timeout_back_2_safeop = param.timeout_esm_us.timeout_back_2_safeop;
    timeout_back_2_init = param.timeout_esm_us.timeout_back_2_init;
    timeout_max = param.timeout_esm_us.timeout_max;
    esm_attemp_max = param.esm_attemp_max;

    ret_val |= validate_param();
    if (ret_val != Ec_master::Return_status::SUCCESS)
    {
        std::cout << "Failed to validate param" << std::endl;
        return ret_val;
    }

    ret_val |= validate_eni();
    if (ret_val != Ec_master::Return_status::SUCCESS)
    {
        std::cout << "Failed to validate eni" << std::endl;
        return ret_val;
    }

    return ret_val;
}

Ec_uint16 Ec_master_base::validate_param()
{
    Ec_uint16 ret_val = Ec_master::Return_status::SUCCESS;
    // TODO
    return Ec_master::Return_status::SUCCESS;
}

Ec_uint16 Ec_master_base::validate_eni()
{
    Ec_uint16 ret_val = Ec_master::Return_status::SUCCESS;
    // TODO
    return Ec_master::Return_status::SUCCESS;
}

Ec_string Ec_master_base::get_mac_addr() const
{
    return mac_address;
}

Ec_string Ec_master_base::get_network_adapter() const
{
    return network_adapter;
}

Ec_string Ec_master_base::get_eni_file_name() const
{
    return eni_file_name;
}

Ec_string Ec_master_base::get_eni_file_path() const
{
    return eni_file_path;
}

Ec_uint16 Ec_master_base::set_state(const Ec_uint16 state)
{
    Ec_uint16 ret_val = Ec_master::Return_status::SUCCESS;
    
    ret_val |= esm(state);

    return ret_val;
}

Ec_uint16 Ec_master_base::get_state()
{
    return ec_master_state;
}

const Ec_boolean Ec_master_base::is_running() const
{
    return ec_running;
}

const Ec_boolean Ec_master_base::is_initialized() const
{
    return ec_initialized;
}

const Ec_boolean Ec_master_base::is_operational() const
{
    return ec_operational;
}

Ec_uint16 Ec_master_base::esm(const Ec_uint16 requested_state)
{
    Ec_uint16 ret_val = Ec_master::Return_status::SUCCESS;
    
    Ec_uint16 current_state = get_state();

    while (requested_state != current_state)
    {
        if (requested_state == Ec_master::State::INIT)
        {
            set_state_initialize();
        }
        else if (requested_state == Ec_master::State::PREOP)
        {
            if (get_state() == Ec_master::State::INIT)
            {
                set_state_pre_operational();
            }
            else if (get_state() == Ec_master::State::SAFE_OP)
            {
                set_state_pre_operational();
            }
            else if (get_state() == Ec_master::State::OP)
            {
                set_state_pre_operational();
            }
            else
            {
                set_state_initialize();
            }
        }
        else if (requested_state == Ec_master::State::SAFE_OP)
        {
            if (get_state() == Ec_master::State::INIT)
            {
                set_state_pre_operational();
            }
            else if (get_state() == Ec_master::State::PREOP)
            {
                set_state_safe_operational();
            }
            else if (get_state() == Ec_master::State::OP)
            {
                set_state(Ec_master::State::SAFE_OP);
            }
            else
            {
                set_state_initialize();
            }
        }
        else if (requested_state == Ec_master::State::OP)
        {
            if (get_state() == Ec_master::State::INIT)
            {
                set_state_pre_operational();
            }
            else if (get_state() == Ec_master::State::PREOP)
            {
                set_state_safe_operational();
            }
            else if (get_state() == Ec_master::State::SAFE_OP)
            {
                set_state_operational();
            }
            else
            {
                set_state_initialize();
            }
        }
        else
        {
            std::cout << "Unknown state requested" << std::endl;
            ret_val = Ec_master::Return_status::UNKNOWN;
            break;
        }

        current_state = get_state();
        std::cout << "current state is: " << current_state << std::endl;
    }

    return ret_val;
}
