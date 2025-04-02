#ifndef ETHERCAT_MASTER_H
#define ETHERCAT_MASTER_H

#include "ethercat_layer.h"

class EtherCATMaster : public EtherCATLayer {
public:
    void checkMasterState() {
        ec_master_state_t ms;
        ecrt_master_state(master, &ms);
        std::cout << "Slaves responding: " << ms.slaves_responding << std::endl;
    }
};

#endif // ETHERCAT_MASTER_H
