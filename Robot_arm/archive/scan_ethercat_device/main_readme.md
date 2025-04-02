# EtherCAT Control System

This README provides an overview of the EtherCAT control system, including base classes for managing the EtherCAT master, slaves, and the EtherCAT layer.

## EtherCAT Layer

The `EtherCATLayer` class provides basic functionalities for starting the EtherCAT master and creating a domain.

### Usage
```cpp
EtherCATLayer layer;
layer.startMaster(0);
layer.createDomain();
layer.activateMaster();
```

## EtherCAT Master

The `EtherCATMaster` class extends `EtherCATLayer` and adds functionality to check the state of the EtherCAT master.

### Usage
```cpp
EtherCATMaster master;
master.startMaster(0);
master.checkMasterState();
```

## EtherCAT Slaves

The `EtherCATSlaves` class extends `EtherCATLayer` and provides methods for configuring slaves and their PDOs.

### Configuration of Slaves

### PDO Configuration for All Slaves
The `configureAllPDOs` method allows for the configuration of PDOs for multiple slaves in a single call.

#### Usage
```cpp
EtherCATSlaves slaves;
ec_slave_config_t* slaveConfigs[] = { /* array of slave configurations */ };
const ec_sync_info_t* syncs = /* sync information */;
int numSlaves = sizeof(slaveConfigs) / sizeof(slaveConfigs[0]);

if (slaves.configureAllPDOs(slaveConfigs, syncs, numSlaves)) {
    // PDOs configured successfully
} else {
    // Failed to configure PDOs
}
```
The following configuration is for 5 EtherCAT slaves:

1. **Slave 1**: 
   - Alias: 0
   - Vendor ID: 0x00000002
   - Product Code: 0x044c2c52
   - PDOs: 
     - Output: 0x7000
     - Input: 0x6000

2. **Slave 2**: 
   - Alias: 1
   - Vendor ID: 0x00000002
   - Product Code: 0x07d83052
   - PDOs: 
     - Output: 0x7001
     - Input: 0x6001

3. **Slave 3**: 
   - Alias: 2
   - Vendor ID: 0x00000002
   - Product Code: 0x03f03052
   - PDOs: 
     - Output: 0x7002
     - Input: 0x6002

4. **Slave 4**: 
   - Alias: 3
   - Vendor ID: 0x00006000
   - Product Code: 0x00004000
   - PDOs: 
     - Output: 0x7003
     - Input: 0x6003

5. **Slave 5**: 
   - Alias: 4
   - Vendor ID: 0x00113322
   - Product Code: 0x00001022
   - PDOs: 
     - Output: 0x7004
     - Input: 0x6004

### Usage
```cpp
EtherCATSlaves slaves;
slaves.startMaster(0);
slaves.configureSlave(0, 0x00000002, 0x044c2c52);
slaves.configureSlave(1, 0x00000002, 0x07d83052);
slaves.configureSlave(2, 0x00000002, 0x03f03052);
slaves.configureSlave(3, 0x00006000, 0x00004000);
slaves.configureSlave(4, 0x00113322, 0x00001022);
```

This structure allows for modular and organized management of EtherCAT devices, making it easier to implement specific functionalities for different applications.
