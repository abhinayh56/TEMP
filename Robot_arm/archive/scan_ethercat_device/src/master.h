#include <ecrt.h>

static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};
static ec_domain_t *domain1 = NULL;
static ec_domain_state_t domain1_state = {};

static uint8_t *domain1_pd = NULL;

void check_domain1_state()
{
    ec_domain_state_t ds;

    ecrt_domain_state(domain1, &ds);

    if (ds.working_counter != domain1_state.working_counter)
    {
        // printf("Domain1: WC %u.\n", ds.working_counter);
    }
    if (ds.wc_state != domain1_state.wc_state)
    {
        // printf("Domain1: State %u.\n", ds.wc_state);
    }

    domain1_state = ds;
}

void check_master_state()
{
    ec_master_state_t ms;

    ecrt_master_state(master, &ms);

    if (ms.slaves_responding != master_state.slaves_responding)
    {
        printf("%u slave(s).\n", ms.slaves_responding);
    }
    if (ms.al_states != master_state.al_states)
    {
        printf("AL states: 0x%02X.\n", ms.al_states);
    }
    if (ms.link_up != master_state.link_up)
    {
        printf("Link is %s.\n", ms.link_up ? "up" : "down");
    }

    master_state = ms;
}

void check_slave_config_states(const std::string &my_slave_name, const ec_slave_config_t *sc_my_slave, ec_slave_config_state_t my_slave_state)
{
    // ec_slave_config_state_t my_slave_state = {};
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc_my_slave, &s);

    if (s.al_state != my_slave_state.al_state)
    {
        std::cout << my_slave_name;
        printf(": State 0x%02X.\n", s.al_state);
    }
    if (s.online != my_slave_state.online)
    {
        std::cout << my_slave_name;
        printf(": %s.\n", s.online ? "online" : "offline");
    }
    if (s.operational != my_slave_state.operational)
    {
        std::cout << my_slave_name;
        printf(": %soperational.\n", s.operational ? "" : "Not ");
    }

    my_slave_state = s;
}

