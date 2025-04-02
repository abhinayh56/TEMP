#ifndef ETHERCAT_SLAVES_H
#define ETHERCAT_SLAVES_H

#include "ethercat_layer.h"

class EtherCATSlaves : public EtherCATLayer {
public:
    bool configureSlave(int alias, int vendorId, int productCode) {
        ec_slave_config_t* slaveConfig = ecrt_master_slave_config(master, alias, vendorId, productCode);
        return slaveConfig != nullptr;
    }

    bool configurePDO(ec_slave_config_t* slaveConfig, const ec_sync_info_t* syncs) {
        return ecrt_slave_config_pdos(slaveConfig, EC_END, syncs) == 0;
    }

    bool configureAllPDOs(ec_slave_config_t* slaveConfigs[], const ec_sync_info_t* syncs, int numSlaves) {
        for (int i = 0; i < numSlaves; ++i) {
            if (!configurePDO(slaveConfigs[i], syncs)) {
                return false; // Return false if any configuration fails
            }
        }
        return true; // Return true if all configurations succeed
    }
};

#endif // ETHERCAT_SLAVES_H
