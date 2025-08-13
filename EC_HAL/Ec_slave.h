#ifndef EC_SLAVE_H
#define EC_SLAVE_H

template <typename T_info>
class Ec_slave
{
public:
    Ec_slave(T_info info_) : info(info_) {}
    ~Ec_slave() {}

protected:
    T_info info;

private:
};

#endif // EC_SLAVE_H
