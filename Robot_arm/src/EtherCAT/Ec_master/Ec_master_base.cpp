#include "Ec_master_base.h"

Ec_uint16 Ec_master_base::set_network_adapter(Ec_string &adapter_name_)
{
    adapter_name = adapter_name_;
}

Ec_string Ec_master_base::get_network_adapter() const
{
    return adapter_name;
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

Ec_uint16 Ec_master_base::stop() {}

Ec_uint16 Ec_master_base::stop() {}

Ec_uint16 Ec_master_base::status() {}

Ec_uint16 Ec_master_base::set_state(const Ec_uint16 state)
{
    return ec_state_machine(state);
}

Ec_uint16 Ec_master_base::get_state()
{
    return ec_master_state;
}

const Ec_boolean Ec_master_base::is_initialized() const
{
    return ec_initialized;
}

const Ec_boolean Ec_master_base::is_operational() const
{
    return ec_operational;
}

Ec_uint16 Ec_master_base::ec_state_machine(const Ec_uint16 requested_state)
{
    timeout_exceed_flag = Ec_false;

    timer = Timer(timeout_max);
    timer.start();

    while (requested_state != get_state())
    {
        if (not timer.reached())
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
    return ec_state_machine(Ec_master::State::INIT);
}

Ec_uint16 Ec_master_base::set_state_pre_operational(const Ec_uint64 timeout)
{
    return ec_state_machine(Ec_master::State::PREOP);
}

Ec_uint16 Ec_master_base::set_state_safe_operational(const Ec_uint64 timeout)
{
    return ec_state_machine(Ec_master::State::SAFE_OP);
}

Ec_uint16 Ec_master_base::set_state_operational(const Ec_uint64 timeout)
{
    return ec_state_machine(Ec_master::State::OP);
}
