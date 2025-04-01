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

    if (!config())
    {
        std::cerr << "Failed to configure master" << std::endl;
        return Ec::Return_status::FAILURE;
    }

    ec_initialized = Ec_true;
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
    return set_state(Ec::State::INIT);
}

Ec_uint16 Ec_master::set_state_pre_operational()
{
    std::cout << "Setting state to PRE-OP..." << std::endl;
    return set_state(Ec::State::PREOP);
}

Ec_uint16 Ec_master::set_state_safe_operational()
{
    std::cout << "Setting state to SAFE-OP..." << std::endl;
    return set_state(Ec::State::SAFE_OP);
}

Ec_uint16 Ec_master::set_state_operational()
{
    std::cout << "Setting state to OPERATIONAL..." << std::endl;
    return set_state(Ec::State::OP);
}

Ec_uint16 Ec_master::set_state(const Ec_uint16 state)
{
    if(state==Ec::State::INIT)
    {
    }
    else if(state==Ec::State::PREOP)
    {
    }
    else if(state==Ec::State::SAFE_OP)
    {
    }
    else if(state==Ec::State::OP)
    {
    }
    else
    {
        std::cout << "UNKNOWN STATE requested" << std::endl;
    }
}

Ec_uint16 Ec_master::get_state(){}

Ec_boolean Ec_master::is_initialized()
{
    return ec_initialized;
}

Ec_boolean Ec_master::is_operational()
{
    return ec_operational;
}

bool Ec_master::config()
{
    std::cout << "Configuring master..." << std::endl;

    // Add slave configuration (replace with actual vendor and product ID)
    // slave_config = ecrt_master_slave_config(master, 0, 0, 0x00000002, 0x12345678);  // Example Vendor ID and Product ID

    // if (!slave_config)
    // {
    //     std::cerr << "Failed to configure slave" << std::endl;
    //     return false;
    // }

    // Configure slave parameters
    // ecrt_slave_config_pdos(slave_config, nullptr);  // PDO configuration
    // ecrt_domain_reg_pdo_entry_list(domain, nullptr);  // PDO entry registration

    static ec_domain_t *domain1 = NULL;
    static uint8_t *domain1_pd = NULL;

    //------------------------
    #define BusCouplerPos 0, 0
    #define Beckhoff_EK1100 0x00000002, 0x044c2c52

    #define DigOutSlavePos 0, 1                    //  alias, position
    #define Beckhoff_EL2008 0x00000002, 0x07d83052 // vendor id, product code
    static unsigned int off_dig_out;

    static const ec_pdo_entry_reg_t domain1_regs[] = {
        {DigOutSlavePos, Beckhoff_EL2008, 0x7000, 1, &off_dig_out}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
        {}};

    // Digital out ------------------------
    static const ec_pdo_entry_info_t el2008_channels[] = {
        {0x7000, 1, 1}, // Value 1
        {0x7010, 1, 1}, // Value 2
        {0x7020, 1, 1}, // Value 3
        {0x7030, 1, 1}, // Value 4
        {0x7040, 1, 1}, // Value 5
        {0x7050, 1, 1}, // Value 6
        {0x7060, 1, 1}, // Value 7
        {0x7070, 1, 1}, // Value 8
    };

    static const ec_pdo_info_t el2008_pdos[] = {
        {0x1600, 1, &el2008_channels[0]},
        {0x1601, 1, &el2008_channels[1]},
        {0x1602, 1, &el2008_channels[2]},
        {0x1603, 1, &el2008_channels[3]},
        {0x1604, 1, &el2008_channels[4]},
        {0x1605, 1, &el2008_channels[5]},
        {0x1606, 1, &el2008_channels[6]},
        {0x1607, 1, &el2008_channels[7]}};

    static const ec_sync_info_t el2008_syncs[] = {
        {0, EC_DIR_OUTPUT, 8, el2008_pdos},
        {1, EC_DIR_INPUT},
        {0xff}};

    //------------------------

    sc = ecrt_master_slave_config(master, DigOutSlavePos, Beckhoff_EL2008)
    if (!sc)
    {
        std::cerr << "Failed to configure slave" << std::endl;
        return false;
    }

    // Configure slave parameters
    sc = ecrt_slave_config_pdos(slave_config, EC_END, el2008_syncs);  // PDO configuration
    if (sc)
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    // ecrt_domain_reg_pdo_entry_list(domain, nullptr);  // PDO entry registration

    slave_config = ecrt_master_slave_config(master, BusCouplerPos, Beckhoff_EK1100);
    if (!slave_config)
    {
        return -1;
    }

    if (ecrt_domain_reg_pdo_entry_list(domain1, domain1_regs))
    {
        fprintf(stderr, "PDO entry registration failed!\n");
        return -1;
    }

    // Activate master
    if (ecrt_master_activate(master))
    {
        return -1;
    }

    if (!(domain1_pd = ecrt_domain_data(domain1)))
    {
        // return -1;
    }

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
