cmake_minimum_required(VERSION 3.5)
project(EtherCAT_Master)

set(CMAKE_CXX_STANDARD 17)

# Set include directories for EtherCAT headers
include_directories(
    /usr/local/etherlab/include  # Path to the ecrt.h header
)

# Set the path to the EtherCAT library and specify the library
set(EtherCAT_LIB_PATH /usr/local/etherlab/lib/libethercat.so)

# Include paths
include_directories(.)

# Link EtherCAT library
find_library(ETHERCAT_LIB ethercat)

add_executable(ethercat_master
    main.cpp
    Ec_master.cpp
    Ec_master_base.cpp
)

target_link_libraries(ethercat_master ${EtherCAT_LIB_PATH})