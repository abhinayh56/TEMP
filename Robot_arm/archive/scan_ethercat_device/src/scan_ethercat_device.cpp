#include <ecrt.h>
#include <iostream>
#include <unistd.h>

#include "master.h"
#include "salve_0.h"
#include "salve_1.h"
#include "salve_2.h"
#include "salve_3.h"
#include "salve_4.h"

#define PERIOD_NS (1000000)
#define NSEC_PER_SEC (1000000000)
#define FREQUENCY (NSEC_PER_SEC / PERIOD_NS)

static unsigned int counter = 0;
static unsigned int blink = 0;

static unsigned int off_1;
static unsigned int off_2;
static unsigned int off_3;
static unsigned int off_4;
static unsigned int off_5;
static unsigned int off_6;
static unsigned int off_7;
static unsigned int off_8;
static unsigned int off_9;
static unsigned int off_10;
static unsigned int off_11;
static unsigned int off_12;
static unsigned int off_13;
static unsigned int off_14;
static unsigned int off_15;
static unsigned int off_16;
static unsigned int off_17;
static unsigned int off_18;
static unsigned int off_19;
static unsigned int off_20;
static unsigned int off_21;

static const ec_pdo_entry_reg_t domain1_regs[] = {
    {el2008_alias_pos, el2008_vendorid_prod_code, 0x7000, 1, &off_el2008}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    {el1008_alias_pos, el1008_vendorid_prod_code, 0x6000, 1, &off_el1008}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x01, &off_1},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x02, &off_2},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x03, &off_3},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x04, &off_4},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x05, &off_5},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x06, &off_6},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x07, &off_7},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x08, &off_8},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x09, &off_9},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x0a, &off_10},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x0b, &off_11},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x0c, &off_12},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x0d, &off_13},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x0e, &off_14},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x0f, &off_15},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x10, &off_16},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x11, &off_17},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x12, &off_18},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x13, &off_19},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x14, &off_20},
    {rfid_alias_pos, rfid_vendorid_prod_code, 0x0006, 0x15, &off_21},
    {mact_1_alias_pos, mact_1_vendorid_prod_code, 0x6064, 0x00, &off_mact_1}, // alias, position, vendor id, product code, index, subindex, offset, bit_position
    {}};

void cyclic_task()
{
    // 7.1. receive process data
    // Fetches received frames from the hardware and processes the datagrams
    ecrt_master_receive(master);
    // Determines the states of the domain's datagrams
    ecrt_domain_process(domain1);

    // 7.2. Reads the state of a domain
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

    // 7.3. read process data
    uint16_t dig_input = EC_READ_U16(domain1_pd + off_el1008);
    
    uint16_t Device_ID      = EC_READ_U16(domain1_pd + off_1);
    uint16_t Second         = EC_READ_U16(domain1_pd + off_2);
    uint16_t Minute         = EC_READ_U16(domain1_pd + off_3);
    uint16_t Hour           = EC_READ_U16(domain1_pd + off_4);
    uint16_t Day            = EC_READ_U16(domain1_pd + off_5);
    uint16_t Month          = EC_READ_U16(domain1_pd + off_6);
    uint16_t Year           = EC_READ_U16(domain1_pd + off_7);
    uint16_t Roll_Offset    = EC_READ_U16(domain1_pd + off_8);
    uint16_t Pitch_Offset   = EC_READ_U16(domain1_pd + off_9);
    uint16_t Yaw_Offset     = EC_READ_U16(domain1_pd + off_10);
    uint16_t Grip_Offset    = EC_READ_U16(domain1_pd + off_11);
    uint16_t No_of_Usages   = EC_READ_U16(domain1_pd + off_12);
    uint16_t Max_Usages     = EC_READ_U16(domain1_pd + off_13);
    uint16_t Digital_Inputs = EC_READ_U16(domain1_pd + off_14);
    uint16_t Grip_Counts    = EC_READ_U16(domain1_pd + off_15);
    uint16_t System_Number  = EC_READ_U16(domain1_pd + off_16);
    uint16_t Device_UID     = EC_READ_U16(domain1_pd + off_17);
    uint16_t Spare_Bytes    = EC_READ_U16(domain1_pd + off_18);
    uint16_t MFG_Day        = EC_READ_U16(domain1_pd + off_19);
    uint16_t MFG_Month      = EC_READ_U16(domain1_pd + off_20);
    uint16_t MFG_Year       = EC_READ_U16(domain1_pd + off_21);

    int32_t act_pos = EC_READ_S32(domain1_pd + off_mact_1);

    std::cout << "act_pos: " << act_pos << ", dig_input: " << dig_input << ", TXPDO: " << ", " << Device_ID << ", " << Second << ", " << Minute << ", " << Hour << ", " << Day << ", " << Month << ", " << Year << ", " << Roll_Offset << ", " << Pitch_Offset << ", " << Yaw_Offset << ", " << Grip_Offset << ", " << No_of_Usages << ", " << Max_Usages << ", " << Digital_Inputs << ", " << Grip_Counts << ", " << System_Number << ", " << Device_UID << ", " << Spare_Bytes << ", " << MFG_Day << ", " << MFG_Month << ", " << MFG_Year << std::endl;

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

    // 7.4. write process data
    EC_WRITE_U8(domain1_pd + off_el2008, blink ? 0xAA : 0x55);

    // 7.5. send process data
    ecrt_domain_queue(domain1);
    ecrt_master_send(master);

    // 7.6. check master state
    // check_master_state();

    // 7.7. check slave(s) state
    // std::cout << "---\n";
    // check_slave_config_states("ek1100", sc_ek1100, sc_ek1100_state);
    // std::cout << "---\n";
    // check_slave_config_states("el2008", sc_el2008, sc_el2008_state);
    // std::cout << "---\n";
    // check_slave_config_states("el1008", sc_el1008, sc_el1008_state);
    // std::cout << "---\n";
    // check_slave_config_states("rfid", sc_rfid, sc_rfid_state);
    // std::cout << "---\n";
    check_slave_config_states("mact_1", sc_mact_1, sc_mact_1_state);
    // std::cout << "---\n";
}

int main()
{
    // 1. Start master
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }

    // 2. Create domain
    domain1 = ecrt_master_create_domain(master);
    if (!domain1)
    {
        return -1;
    }

    // 3. Configure PDO
    configure_slave_0(master);
    configure_slave_1(master);
    configure_slave_2(master);
    configure_slave_3(master);
    configure_slave_4(master);

    // 4. registers a group of PDOs to a domain
    if (ecrt_domain_reg_pdo_entry_list(domain1, domain1_regs))
    {
        fprintf(stderr, "PDO entry registration failed!\n");
        return -1;
    }

    // 5. finnishes configuration and activates master
    if (ecrt_master_activate(master))
    {
        return -1;
    }

    // 6. returns the pointer to domain process data
    if (!(domain1_pd = ecrt_domain_data(domain1)))
    {
        // return -1;
    }

    // 7. start continuous loop
    while (true)
    {
        cyclic_task();

        usleep(PERIOD_NS/1000);
    }

    return 0;
}
