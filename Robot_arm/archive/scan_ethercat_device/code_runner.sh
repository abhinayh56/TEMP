#!/bin/bash

sudo /etc/init.d/ethercat start
expect "Password"
send "Ssi@113322\n"

pwd
mkdir ~/Abhinay/Ethercat_IGH/scan_ethercat_device/build
cd ~/Abhinay/Ethercat_IGH/scan_ethercat_device/build
sleep 0.5s
pwd

echo "INFO: Detecting bus topology"
rm ethercat_bus_graph.png
ethercat graph > "ethercat_bus_graph.dot"
dot -Tpng ethercat_bus_graph.dot -o ethercat_bus_graph.png
xdg-open ethercat_bus_graph.png

sleep 1s

echo ""
echo "INFO: Compiling the code ..."
make clean
cmake ..
make
echo "INFO: Executable generated ..."
echo "INFO: Executing code ..."
echo "=============================================================="
echo "                             START                            "
echo "=============================================================="
./scan_ethercat_device
echo "=============================================================="
echo "INFO: Execution completed."
