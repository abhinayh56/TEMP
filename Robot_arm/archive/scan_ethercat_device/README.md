# EtherCAT Device Control Base Class

This README provides a base class in C++ for controlling EtherCAT devices. The base class includes functions for starting the EtherCAT master, changing states, configuring slaves, setting up Process Data Objects (PDOs), and handling distributed clocks (DC).

## Base Class: EtherCATController

```cpp
#include <ecrt.h>
#include <iostream>
#include <string>

class EtherCATController {
public:
    EtherCATController() : master(nullptr), domain(nullptr) {}

    bool startMaster(int masterIndex) {
        master = ecrt_request_master(masterIndex);
        return master != nullptr;
    }

    bool createDomain() {
        domain = ecrt_master_create_domain(master);
        return domain != nullptr;
    }

    bool configureSlave(int alias, int vendorId, int productCode) {
        ec_slave_config_t* slaveConfig = ecrt_master_slave_config(master, alias, vendorId, productCode);
        return slaveConfig != nullptr;
    }

    bool configurePDO(ec_slave_config_t* slaveConfig, const ec_sync_info_t* syncs) {
        return ecrt_slave_config_pdos(slaveConfig, EC_END, syncs) == 0;
    }

    void checkMasterState() {
        ec_master_state_t ms;
        ecrt_master_state(master, &ms);
        std::cout << "Slaves responding: " << ms.slaves_responding << std::endl;
    }

    void checkDomainState() {
        ec_domain_state_t ds;
        ecrt_domain_state(domain, &ds);
        std::cout << "Domain working counter: " << ds.working_counter << std::endl;
    }

    void activateMaster() {
        ecrt_master_activate(master);
    }

    uint8_t* getDomainData() {
        return ecrt_domain_data(domain);
    }

private:
    ec_master_t* master;
    ec_domain_t* domain;
};
```

## Usage

1. **Instantiate the Base Class**:
   ```cpp
   EtherCATController controller;
   ```

2. **Start the EtherCAT Master**:
   ```cpp
   if (!controller.startMaster(0)) {
       std::cerr << "Failed to start master." << std::endl;
   }
   ```

3. **Create a Domain**:
   ```cpp
   if (!controller.createDomain()) {
       std::cerr << "Failed to create domain." << std::endl;
   }
   ```

4. **Configure Slaves**:
   ```cpp
   if (!controller.configureSlave(0, 0x00000002, 0x044c2c52)) {
       std::cerr << "Failed to configure slave." << std::endl;
   }
   ```

5. **Activate the Master**:
   ```cpp
   controller.activateMaster();
   ```

6. **Check States**:
   ```cpp
   controller.checkMasterState();
   controller.checkDomainState();
   ```

This base class can be extended to implement specific functionalities for different EtherCAT applications.
