#include "Ec_master_base.h"

Ec_uint16 Ec_master_base::set_mac_addr(Ec_string &mac_address_)
{
    mac_address = mac_address_;
}

Ec_string Ec_master_base::get_mac_addr() const
{
    return mac_address;
}

Ec_uint16 Ec_master_base::set_network_adapter(Ec_string &network_adapter_)
{
    network_adapter = network_adapter_;
}

Ec_string Ec_master_base::get_network_adapter() const
{
    return network_adapter;
}

Ec_uint16 Ec_master_base::set_eni_file_name(const Ec_string &eni_file_name_)
{
    eni_file_name = eni_file_name_;
}

Ec_string Ec_master_base::get_eni_file_name() const
{
    return eni_file_name;
}

Ec_uint16 Ec_master_base::set_eni_file_path(const Ec_string &eni_file_path_)
{
    eni_file_path = eni_file_path_;
}

Ec_string Ec_master_base::get_eni_file_path() const
{
    return eni_file_path;
}

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
    }

    ret_val |= validate_eni();
    if (ret_val != Ec_master::Return_status::SUCCESS)
    {
        std::cout << "Failed to validate eni" << std::endl;
    }

    return Ec_master::Return_status::SUCCESS;
}

Ec_uint16 Ec_master_base::set_state(const Ec_uint16 state)
{
    return esm(state);
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

Ec_uint16 Ec_master_base::set_state_machine_timeout(const Ec_master::Timeout_esm_us timeout)
{
    timeout_preop = timeout.timeout_preop;
    timeout_safeop_op = timeout.timeout_safeop_op;
    timeout_back_2_safeop = timeout.timeout_back_2_safeop;
    timeout_back_2_init = timeout.timeout_back_2_init;
    timeout_max = timeout.timeout_max;
}

Ec_uint16 Ec_master_base::esm(const Ec_uint16 requested_state)
{
    Ec_uint16 esm_attemp = 0;
    timeout_exceed_flag = Ec_false;

    Timer timer;
    timer.start();

    while (esm_attemp <= esm_attemp_max)
    {
        esm_attemp++;
        update();

        while(requested_state != ec_master_state)
        {
            if (timeout_exceed_flag == Ec_false)
            {
            }
            else
            {
            }
        }
    }

    while (requested_state != get_state())
    {
        if (timer.get_time_micro() < timeout_max)
        {
            if (requested_state == Ec_master::State::INIT)
            {
                set_state_initialize(timeout_back_2_init);
            }
            else if (requested_state == Ec_master::State::PREOP)
            {
                if (get_state() == Ec_master::State::INIT)
                {
                    set_state(Ec_master::State::PREOP);
                }
                else if (get_state() == Ec_master::State::SAFE_OP)
                {
                    set_state(Ec_master::State::PREOP);
                }
                else if (get_state() == Ec_master::State::OP)
                {
                    set_state(Ec_master::State::PREOP);
                }
                else
                {
                    set_state_initialize(timeout_back_2_init);
                }
            }
            else if (requested_state == Ec_master::State::SAFE_OP)
            {
                if (get_state() == Ec_master::State::INIT)
                {
                    set_state(Ec_master::State::PREOP);
                }
                else if (get_state() == Ec_master::State::PREOP)
                {
                    set_state(Ec_master::State::SAFE_OP);
                }
                else if (get_state() == Ec_master::State::OP)
                {
                    set_state(Ec_master::State::SAFE_OP);
                }
                else
                {
                    set_state_initialize(timeout_back_2_init);
                }
            }
            else if (requested_state == Ec_master::State::OP)
            {
                if (get_state() == Ec_master::State::INIT)
                {
                    set_state(Ec_master::State::PREOP);
                }
                else if (get_state() == Ec_master::State::PREOP)
                {
                    set_state(Ec_master::State::SAFE_OP);
                }
                else if (get_state() == Ec_master::State::SAFE_OP)
                {
                    set_state(Ec_master::State::OP);
                }
                else
                {
                    set_state_initialize(timeout_back_2_init);
                }
            }
            else
            {
                // "print(f "ERROR Requested {interpret_state(requested_state)}")"
                break;
            }

            if (requested_state == get_state())
            {
                // print(f "INFO Requested state {interpret_state(requested_state)} ({requested_state}) | Current state {interpret_state(get_state())} ({get_state()})") break
            }
        }
        else
        {
            if (requested_state != get_state())
            {
                // print(f "ERROR Requested state ({requested_state}) not reached in {timeout_max} seconds")
            }
            else
            {
                // print(f "INFO Requested state ({requested_state}) reached in {timer.time_elapsed()} seconds")
                // print(f "INFO Requested state {interpret_state(requested_state)} ({requested_state}) | Current state {interpret_state(get_state())} ({get_state()})")
            }
            break;
        }
    }
}

Ec_uint16 Ec_master_base::set_state_initialize(const Ec_uint64 timeout)
{
    return esm(Ec_master::State::INIT);
}

Ec_uint16 Ec_master_base::set_state_pre_operational(const Ec_uint64 timeout)
{
    return esm(Ec_master::State::PREOP);
}

Ec_uint16 Ec_master_base::set_state_safe_operational(const Ec_uint64 timeout)
{
    return esm(Ec_master::State::SAFE_OP);
}

Ec_uint16 Ec_master_base::set_state_operational(const Ec_uint64 timeout)
{
    return esm(Ec_master::State::OP);
}
