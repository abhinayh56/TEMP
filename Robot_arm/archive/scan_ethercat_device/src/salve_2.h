#include <ecrt.h>

static ec_slave_config_t *sc_el1008;

static ec_slave_config_state_t sc_el1008_state;

// Digital in ------------------------
/* Master 0, Slave 2, "EL1008"
 * Vendor ID:       0x00000002
 * Product code:    0x03f03052
 * Revision number: 0x00120000
 */

#define el1008_alias_pos 0, 2                            //  alias, position
#define el1008_vendorid_prod_code 0x00000002, 0x03f03052 // vendor id, product code
static unsigned int off_el1008;

ec_pdo_entry_info_t el1008_pdo_entries[] = {
    {0x6000, 0x01, 1}, /* Input */
    {0x6010, 0x01, 1}, /* Input */
    {0x6020, 0x01, 1}, /* Input */
    {0x6030, 0x01, 1}, /* Input */
    {0x6040, 0x01, 1}, /* Input */
    {0x6050, 0x01, 1}, /* Input */
    {0x6060, 0x01, 1}, /* Input */
    {0x6070, 0x01, 1}, /* Input */
};

ec_pdo_info_t el1008_pdos[] = {
    {0x1a00, 1, el1008_pdo_entries + 0}, /* Channel 1 */
    {0x1a01, 1, el1008_pdo_entries + 1}, /* Channel 2 */
    {0x1a02, 1, el1008_pdo_entries + 2}, /* Channel 3 */
    {0x1a03, 1, el1008_pdo_entries + 3}, /* Channel 4 */
    {0x1a04, 1, el1008_pdo_entries + 4}, /* Channel 5 */
    {0x1a05, 1, el1008_pdo_entries + 5}, /* Channel 6 */
    {0x1a06, 1, el1008_pdo_entries + 6}, /* Channel 7 */
    {0x1a07, 1, el1008_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t el1008_syncs[] = {
    {0, EC_DIR_OUTPUT},
    {0, EC_DIR_INPUT, 8, el1008_pdos + 0, EC_WD_DISABLE},
    {0xff}};

int configure_slave_2(ec_master_t *master_)
{
    if (!(sc_el1008 = ecrt_master_slave_config(master_, el1008_alias_pos, el1008_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_el1008, EC_END, el1008_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    return 1;
}