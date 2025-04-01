#include <stdint.h>
#include <iostream>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>     /* clock_gettime() */
#include <sys/mman.h> /* mlockall() */
#include <sched.h>    /* sched_setscheduler() */
#include <ecrt.h>

#define PERIOD_NS (1000000)
#define NSEC_PER_SEC (1000000000)
#define FREQUENCY (NSEC_PER_SEC / PERIOD_NS)
#define MAX_SAFE_STACK (8 * 1024)

static unsigned int counter = 0;
static unsigned int blink = 0;

static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};
static ec_domain_t *domain1 = NULL;
static ec_domain_state_t domain1_state = {};

static uint8_t *domain1_pd = NULL;

static ec_slave_config_t *sc_ek1100;
static ec_slave_config_t *sc_el2008;
static ec_slave_config_t *sc_el1008;
static ec_slave_config_t *sc_rfid;
static ec_slave_config_t *sc_mact_1;

static ec_slave_config_state_t sc_ek1100_state;
static ec_slave_config_state_t sc_el2008_state;
static ec_slave_config_state_t sc_el1008_state;
static ec_slave_config_state_t sc_rfid_state;
static ec_slave_config_state_t sc_mact_1_state;

//Ethercat coupler ------------------------
#define ek1100_alias_pos 0, 0
#define ek1100_vendorid_prod_code 0x00000002, 0x044c2c52

// Digital out ------------------------
/* Master 0, Slave 1, "EL2008"
 * Vendor ID:       0x00000002
 * Product code:    0x07d83052
 * Revision number: 0x00120000
 */

#define el2008_alias_pos 0, 1                    //  alias, position
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
    {0xff}
};
//------------------------

// Digital in ------------------------
/* Master 0, Slave 2, "EL1008"
 * Vendor ID:       0x00000002
 * Product code:    0x03f03052
 * Revision number: 0x00120000
 */

#define el1008_alias_pos 0, 2                    //  alias, position
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
    {0xff}
};
//------------------------
// RFID slave ------------------------
/* Master 0, Slave 7, "RfidSlave"
 * Vendor ID:       0x00006000
 * Product code:    0x00004000
 * Revision number: 0x00000004
 */

#define rfid_alias_pos 0, 7                    //  alias, position
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
    {0x1600, 19, rfid_pdo_entries + 0}, /* Outputs */
    {0x1a00, 21, rfid_pdo_entries + 19}, /* Inputs */
};

ec_sync_info_t rfid_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, rfid_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, rfid_pdos + 1, EC_WD_DISABLE},
    {0xff}
};
//------------------------

//------------------------
/* Master 0, Slave 8, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

#define mact_1_alias_pos 0, 8                    //  alias, position
#define mact_1_vendorid_prod_code 0x00113322, 0x00001022 // vendor id, product code
static unsigned int off_mact_1;

 ec_pdo_entry_info_t mact_1_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
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
    {0xff}
};

//------------------------

static const ec_pdo_entry_reg_t domain1_regs[] = {
    {el2008_alias_pos, el2008_vendorid_prod_code, 0x7000, 1, &off_el2008}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    {el1008_alias_pos, el1008_vendorid_prod_code, 0x6000, 1, &off_el1008}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0005, 1, &off_rfid}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    // {mact_1_alias_pos, mact_1_vendorid_prod_code, 0x607a, 1, &off_mact_1}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    {}};

void stack_prefault()
{
    unsigned char dummy[MAX_SAFE_STACK];

    memset(dummy, 0, MAX_SAFE_STACK);
}

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

void cyclic_task()
{
    // std::cout << "Cyclic task running..." << std::endl;
    // receive process data
    ecrt_master_receive(master);
    ecrt_domain_process(domain1);

    // check process data state
    check_domain1_state();

    if (counter)
    {
        counter--;
    }
    else
    { // do this at 1 Hz
        counter = FREQUENCY;

        // calculate new process data
        blink = !blink;
    }

    // write process data
    EC_WRITE_U8(domain1_pd + off_el2008, blink ? 0xAA : 0x55);

    // std::cout << "----------------------->BLINK: " << blink << std::endl;

    // send process data
    ecrt_domain_queue(domain1);
    ecrt_master_send(master);

    check_master_state();

    std::cout << "---\n";
    check_slave_config_states("ek1100", sc_ek1100, sc_ek1100_state);
    std::cout << "---\n";
    check_slave_config_states("el2008", sc_el2008, sc_el2008_state);
    std::cout << "---\n";
    check_slave_config_states("el1008", sc_el1008, sc_el1008_state);
    std::cout << "---\n";
    check_slave_config_states("rfid", sc_rfid, sc_rfid_state);
    std::cout << "---\n";
    check_slave_config_states("mact_1", sc_mact_1, sc_mact_1_state);
    std::cout << "---\n";
}

int main()
{  
    struct timespec wakeup_time;
    int ret = 0;

    // Start master
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }

    // Create domain
    domain1 = ecrt_master_create_domain(master);
    if (!domain1)
    {
        return -1;
    }

    // Configure PDO
    if (!(sc_ek1100 = ecrt_master_slave_config(master, ek1100_alias_pos, ek1100_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (!(sc_el2008 = ecrt_master_slave_config(master, el2008_alias_pos, el2008_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_el2008, EC_END, el2008_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    if (!(sc_el1008 = ecrt_master_slave_config(master, el1008_alias_pos, el1008_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_el1008, EC_END, el1008_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }


    if (!(sc_rfid = ecrt_master_slave_config(master, rfid_alias_pos, rfid_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_rfid, EC_END, rfid_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    if (!(sc_mact_1 = ecrt_master_slave_config(master, mact_1_alias_pos, mact_1_vendorid_prod_code)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_mact_1, EC_END, mact_1_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
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

    struct sched_param param = {};
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    std::cout << "using priority: " << param.sched_priority << std::endl;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler failed");
    }
    else
    {
        std::cout << "sched_setscheduler successful" << std::endl;
    }

    if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1)
    {
        fprintf(stderr, "Warning: Failed to lock memory: %s\n", strerror(errno));
    }
    else
    {
        std::cout << "memory locked" << std::endl;
    }

    stack_prefault();
    std::cout << "stack_prefault done" << std::endl;

    printf("starting RT task with dt=%u ns.\n", PERIOD_NS);

    clock_gettime(CLOCK_MONOTONIC, &wakeup_time);
    wakeup_time.tv_sec += 1;
    wakeup_time.tv_nsec = 0;

    while (true)
    {
        ret = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &wakeup_time, NULL);
        if (ret)
        {
            fprintf(stderr, "clock_nanosleep(): %s\n", strerror(ret));
            break;
        }

        cyclic_task();

        wakeup_time.tv_nsec += PERIOD_NS;
        while (wakeup_time.tv_nsec >= NSEC_PER_SEC)
        {
            wakeup_time.tv_nsec -= NSEC_PER_SEC;
            wakeup_time.tv_sec++;
        }
    }

    return 0;
}
