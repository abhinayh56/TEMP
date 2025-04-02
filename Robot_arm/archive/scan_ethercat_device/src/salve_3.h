#include <ecrt.h>

static ec_slave_config_t *sc_rfid;

static ec_slave_config_state_t sc_rfid_state;

//------------------------
// RFID slave ------------------------
/* Master 0, Slave 7, "RfidSlave"
 * Vendor ID:       0x00006000
 * Product code:    0x00004000
 * Revision number: 0x00000004
 */

#define rfid_alias_pos 0, 7                            //  alias, position
#define rfid_vendorid_prod_code 0x00006000, 0x00004000 // vendor id, product code
static unsigned int off_rfid;

ec_pdo_entry_info_t rfid_pdo_entries[] = {
    {0x0005, 0x01, 16}, /* Acknowledge */
    {0x0005, 0x02, 16}, /* Second */
    {0x0005, 0x03, 16}, /* Minute */
    {0x0005, 0x04, 16}, /* Hour */
    {0x0005, 0x05, 16}, /* Day */
    {0x0005, 0x06, 16}, /* Month */
    {0x0005, 0x07, 16}, /* Year */
    {0x0005, 0x08, 16}, /* No_of_Usages */
    {0x0005, 0x09, 16}, /* Digital_Outputs */
    {0x0005, 0x0a, 16}, /* Grip_Counts */
    {0x0005, 0x0b, 16}, /* System_Number */
    {0x0005, 0x0c, 16}, /* Led_Red */
    {0x0005, 0x0d, 16}, /* Led_Green */
    {0x0005, 0x0e, 16}, /* Led_Blue */
    {0x0005, 0x0f, 16}, /* Spare_Bytes */
    {0x0005, 0x10, 16}, /* Roll_Offset */
    {0x0005, 0x11, 16}, /* Pitch_Offset */
    {0x0005, 0x12, 16}, /* Yaw_Offset */
    {0x0005, 0x13, 16}, /* Grip_Offset */
    {0x0006, 0x01, 16}, /* Device_ID */
    {0x0006, 0x02, 16}, /* Second */
    {0x0006, 0x03, 16}, /* Minute */
    {0x0006, 0x04, 16}, /* Hour */
    {0x0006, 0x05, 16}, /* Day */
    {0x0006, 0x06, 16}, /* Month */
    {0x0006, 0x07, 16}, /* Year */
    {0x0006, 0x08, 16}, /* Roll_Offset */
    {0x0006, 0x09, 16}, /* Pitch_Offset */
    {0x0006, 0x0a, 16}, /* Yaw_Offset */
    {0x0006, 0x0b, 16}, /* Grip_Offset */
    {0x0006, 0x0c, 16}, /* No_of_Usages */
    {0x0006, 0x0d, 16}, /* Max_Usages */
    {0x0006, 0x0e, 16}, /* Digital_Inputs */
    {0x0006, 0x0f, 16}, /* Grip_Counts */
    {0x0006, 0x10, 16}, /* System_Number */
    {0x0006, 0x11, 16}, /* Device_UID */
    {0x0006, 0x12, 16}, /* Spare_Bytes */
    {0x0006, 0x13, 16}, /* MFG_Day */
    {0x0006, 0x14, 16}, /* MFG_Month */
    {0x0006, 0x15, 16}, /* MFG_Year */
};

ec_pdo_info_t rfid_pdos[] = {
    {0x1600, 19, rfid_pdo_entries + 0},  /* Outputs */
    {0x1a00, 21, rfid_pdo_entries + 19}, /* Inputs */
};

ec_sync_info_t rfid_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, rfid_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, rfid_pdos + 1, EC_WD_DISABLE},
    {0xff}};
//------------------------

int configure_slave_3(ec_master_t *master_)
{
    // 3.1. create slave configuration pointer
    if (!(sc_rfid = ecrt_master_slave_config(master_, rfid_alias_pos, rfid_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    // 3.2. create PDO configuration
    if (ecrt_slave_config_pdos(sc_rfid, EC_END, rfid_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    return 1;
}