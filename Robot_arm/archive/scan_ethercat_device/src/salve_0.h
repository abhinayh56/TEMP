#include <ecrt.h>

static ec_slave_config_t *sc_ek1100;
static ec_slave_config_state_t sc_ek1100_state;

// Ethercat coupler ------------------------
#define ek1100_alias_pos 0, 0
#define ek1100_vendorid_prod_code 0x00000002, 0x044c2c52

int configure_slave_0(ec_master_t *master_)
{
    if (!(sc_ek1100 = ecrt_master_slave_config(master, ek1100_alias_pos, ek1100_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    return 1;
}