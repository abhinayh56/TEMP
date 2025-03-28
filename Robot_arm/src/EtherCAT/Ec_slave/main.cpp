#include <iostream>
#include "Ec_slave_1.h"
#include "Ec_slave_2.h"
#include "Ec_slave_3.h"
#include "Ec_slave_4.h"
#include "Ec_slave_5.h"
#include "Slave_manager.h"
#include "pugixml.hpp"


bool loadXMLToStruct(const std::string &filename, Slave_1::Param &param)
{
    pugi::xml_document doc;

    // Load the XML file
    pugi::xml_parse_result result = doc.load_file(filename.c_str());
    if (!result)
    {
        std::cerr << "Failed to load XML file: " << result.description() << std::endl;
        return false;
    }

    // Access the <param_node> node
    pugi::xml_node paramNode = doc.child("param_node");

    if (!paramNode)
    {
        std::cerr << "Invalid XML format or missing <param_node> node." << std::endl;
        return false;
    }

    // Read and assign values to the struct
    param.a1 = paramNode.child("a1").text().as_int();
    param.a2 = paramNode.child("a2").text().as_int();
    param.a3 = paramNode.child("a3").text().as_int();
    param.a4 = paramNode.child("a4").text().as_int();
    param.a5 = paramNode.child("a5").text().as_int();

    return true;
}

int main()
{
    std::cout << "===" << std::endl;

    Slave_manager slave_manager;

    Slave_1::Param param_1_1;
    Slave_1::Param param_1_2;
    Slave_1::Param param_1_3;
    Slave_2::Param param_2;
    Slave_3::Param param_3;
    Slave_4::Param param_4;
    Slave_5::Param param_5;

    loadXMLToStruct("parameter_1_1.xml", param_1_1);
    loadXMLToStruct("parameter_1_2.xml", param_1_2);
    loadXMLToStruct("parameter_1_3.xml", param_1_3);

    Ec_slave_1 slave_1_1(&param_1_1);
    Ec_slave_1 slave_1_2(&param_1_2);
    Ec_slave_1 slave_1_3(&param_1_3);
    Ec_slave_2 slave_2(&param_2);
    Ec_slave_3 slave_3(&param_3);
    Ec_slave_4 slave_4(&param_4);
    Ec_slave_5 slave_5(&param_5);

    slave_manager.add_slave(&slave_1_1);
    slave_manager.add_slave(&slave_1_2);
    slave_manager.add_slave(&slave_1_3);
    slave_manager.add_slave(&slave_2);
    slave_manager.add_slave(&slave_3);
    slave_manager.add_slave(&slave_4);
    slave_manager.add_slave(&slave_5);

    slave_manager.run();

    std::cout << "===" << std::endl;

    return 0;
}
