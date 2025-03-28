#ifndef EC_SLAVE_BASE
#define EC_SLAVE_BASE

#include "../../utility/Data_type.h"
#include "../../utility/Constants.h"

namespace Ec_slave
{
    enum State
    {
        UNKNOWN = 0,
        BOOTSTRAP = 1,
        ERROR = 2,
        INIT = 3,
        PREOP = 4,
        SAFE_OP = 5,
        OP = 6
    };
}

class Ec_slave_base
{
public:
    Ec_slave_base();
    ~Ec_slave_base();
    virtual void config() = 0;
    virtual void config_publisher() = 0;
    virtual void config_subscriber() = 0;
    virtual void config_rx_pdo() = 0;
    virtual void config_tx_pdo() = 0;
    virtual void read_tx_pdo() = 0;
    virtual void write_rx_pdo() = 0;
    virtual void transfer_tx_pdo() = 0;
    virtual void transfer_rx_pdo() = 0;
    virtual void check_status() = 0;

protected:
    Ec_int16 num_slaves_in_eni = 0;
    Ec_int16 num_slaves_connected = 0;
    Ec_int16 num_slaves_configured = 0;

private:
}

#endif // EC_SLAVE_BASE


#ifndef EC_SLAVE_BASE_H
#define EC_SLAVE_BASE_H

class Ec_slave_base
{
public:
    virtual ~Ec_slave_base() = default;

    virtual void config_slave() = 0;
    virtual void config_publisher() = 0;
    virtual void config_subscriber() = 0;
    virtual void config_rx_pdo() = 0;
    virtual void config_tx_pdo() = 0;
    virtual void read_tx_pdo() = 0;
    virtual void write_rx_pdo() = 0;
    virtual void transfer_tx_pdo() = 0;
    virtual void transfer_rx_pdo() = 0;
    virtual void check_slave_status() = 0;
};

#endif // EC_SLAVE_BASE_H
