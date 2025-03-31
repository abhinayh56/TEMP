#include "Ec_master.h"

Ec_master::Ec_master()
{
    std::cout << "Ec_master constructor" << std::endl;
}

Ec_master::~Ec_master()
{
    stop();
    std::cout << "Ec_master destructor" << std::endl;
}

Ec_uint16 Ec_master::start()
{
    std::cout << "Starting IGH EtherCAT Master..." << std::endl;

    master = ecrt_request_master(0);
    if (!master)
    {
        std::cerr << "Failed to acquire master" << std::endl;
        return Ec::Return_status::FAILURE;
    }

    domain = ecrt_master_create_domain(master);
    if (!domain)
    {
        std::cerr << "Failed to create domain" << std::endl;
        return Ec::Return_status::FAILURE;
    }

    if (!configure_master())
    {
        std::cerr << "Failed to configure master" << std::endl;
        return Ec::Return_status::FAILURE;
    }

    ec_initialized = Ec_true;
    std::cout << "Master started successfully." << std::endl;
    return Ec::Return_status::SUCCESS;
}

Ec_uint16 Ec_master::stop()
{
    std::cout << "Stopping IGH EtherCAT Master..." << std::endl;

    if (master) {
        ecrt_release_master(master);
        master = nullptr;
    }

    ec_initialized = Ec_false;
    ec_operational = Ec_false;
    
    std::cout << "Master stopped successfully." << std::endl;
    return Ec::Return_status::SUCCESS;
}

Ec_uint16 Ec_master::update()
{
    if (!ec_initialized) {
        std::cerr << "Master is not initialized" << std::endl;
        return Ec::Return_status::FAILURE;
    }

    ecrt_master_receive(master);
    ecrt_domain_process(domain);

    check_domain_state();
    check_master_state();

    ecrt_domain_queue(domain);
    ecrt_master_send(master);

    return Ec::Return_status::SUCCESS;
}

Ec_uint16 Ec_master::set_state_initialize()
{
    std::cout << "Setting state to INIT..." << std::endl;
    return set_state(Ec::INIT);
}

Ec_uint16 Ec_master::set_state_pre_operational()
{
    std::cout << "Setting state to PRE-OP..." << std::endl;
    return set_state(Ec::PREOP);
}

Ec_uint16 Ec_master::set_state_safe_operational()
{
    std::cout << "Setting state to SAFE-OP..." << std::endl;
    return set_state(Ec::SAFE_OP);
}

Ec_uint16 Ec_master::set_state_operational()
{
    std::cout << "Setting state to OPERATIONAL..." << std::endl;
    return set_state(Ec::OP);
}

Ec_uint16 Ec_master::get_state()
{
    return ec_master_state;
}

Ec_boolean Ec_master::is_initialized()
{
    return ec_initialized;
}

Ec_boolean Ec_master::is_operational()
{
    return ec_operational;
}

bool Ec_master::configure_master()
{
    std::cout << "Configuring master..." << std::endl;

    // Add slave configuration (replace with actual vendor and product ID)
    slave_config = ecrt_master_slave_config(
        master, 0, 0, 0x00000002, 0x12345678);  // Example Vendor ID and Product ID

    if (!slave_config) {
        std::cerr << "Failed to configure slave" << std::endl;
        return false;
    }

    // Configure slave parameters
    // ecrt_slave_config_pdos(slave_config, nullptr);  // PDO configuration
    // ecrt_domain_reg_pdo_entry_list(domain, nullptr);  // PDO entry registration

    return true;
}

void Ec_master::check_domain_state()
{
    ec_domain_state_t domain_state;
    ecrt_domain_state(domain, &domain_state);

    if (domain_state.working_counter != 0) {
        std::cout << "Domain state: WC=" << domain_state.working_counter
                  << ", State=" << domain_state.wc_state << std::endl;
    }
}

void Ec_master::check_master_state()
{
    ec_master_state_t master_state;
    ecrt_master_state(master, &master_state);

    if (master_state.al_states != ec_master_state) {
        std::cout << "Master state changed: " << master_state.al_states << std::endl;
        ec_master_state = master_state.al_states;
    }
}
