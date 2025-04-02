#include <ecrt.h>

static ec_slave_config_t *sc_el2008;

static ec_slave_config_state_t sc_el2008_state;

// Digital out ------------------------
/* Master 0, Slave 1, "EL2008"
 * Vendor ID:       0x00000002
 * Product code:    0x07d83052
 * Revision number: 0x00120000
 */

#define el2008_alias_pos 0, 1                            //  alias, position
#define el2008_vendorid_prod_code 0x00000002, 0x07d83052 // vendor id, product code
static unsigned int off_el2008;

static const ec_pdo_entry_info_t el2008_pdo_entries[] = {
    {0x7000, 0x01, 1}, /* Output */
    {0x7010, 0x01, 1}, /* Output */
    {0x7020, 0x01, 1}, /* Output */
    {0x7030, 0x01, 1}, /* Output */
    {0x7040, 0x01, 1}, /* Output */
    {0x7050, 0x01, 1}, /* Output */
    {0x7060, 0x01, 1}, /* Output */
    {0x7070, 0x01, 1}, /* Output */
};

static const ec_pdo_info_t el2008_pdos[] = {
    {0x1600, 1, el2008_pdo_entries + 0}, /* Channel 1 */
    {0x1601, 1, el2008_pdo_entries + 1}, /* Channel 2 */
    {0x1602, 1, el2008_pdo_entries + 2}, /* Channel 3 */
    {0x1603, 1, el2008_pdo_entries + 3}, /* Channel 4 */
    {0x1604, 1, el2008_pdo_entries + 4}, /* Channel 5 */
    {0x1605, 1, el2008_pdo_entries + 5}, /* Channel 6 */
    {0x1606, 1, el2008_pdo_entries + 6}, /* Channel 7 */
    {0x1607, 1, el2008_pdo_entries + 7}, /* Channel 8 */
};

static const ec_sync_info_t el2008_syncs[] = {
    {0, EC_DIR_OUTPUT, 8, el2008_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT},
    {0xff}};
//------------------------

int configure_slave_1(ec_master_t *master_)
{
    if (!(sc_el2008 = ecrt_master_slave_config(master_, el2008_alias_pos, el2008_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_el2008, EC_END, el2008_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    return 1;
}