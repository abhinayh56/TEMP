#ifndef ETHERCAT_LAYER_H
#define ETHERCAT_LAYER_H

#include <ecrt.h>
#include <iostream>
#include <string>

class EtherCATLayer {
public:
    EtherCATLayer() : master(nullptr), domain(nullptr) {}

    bool startMaster(int masterIndex) {
        master = ecrt_request_master(masterIndex);
        return master != nullptr;
    }

    bool createDomain() {
        domain = ecrt_master_create_domain(master);
        return domain != nullptr;
    }

    void activateMaster() {
        ecrt_master_activate(master);
    }

protected:
    ec_master_t* master;
    ec_domain_t* domain;
};

#endif // ETHERCAT_LAYER_H
