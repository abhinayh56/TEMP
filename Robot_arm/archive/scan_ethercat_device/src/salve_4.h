#include <ecrt.h>

static ec_slave_config_t *sc_mact_1;

static ec_slave_config_state_t sc_mact_1_state;

//------------------------
/* Master 0, Slave 8, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

#define mact_1_alias_pos 0, 8                            //  alias, position
#define mact_1_vendorid_prod_code 0x00113322, 0x00001022 // vendor id, product code
static unsigned int off_mact_1;

ec_pdo_entry_info_t mact_1_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8},  /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8},  /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8},  /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8},  /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t mact_1_pdos[] = {
    {0x1600, 7, mact_1_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, mact_1_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t mact_1_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, mact_1_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, mact_1_pdos + 1, EC_WD_DISABLE},
    {0xff}};

//------------------------

int configure_slave_4(ec_master_t *master_)
{
    if (!(sc_mact_1 = ecrt_master_slave_config(master_, mact_1_alias_pos, mact_1_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_mact_1, EC_END, mact_1_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    return 1;
}