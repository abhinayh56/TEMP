#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ctime>
#include "../../utility/Data_type.h"
#include "../../utility/Constants.h"

class Timer
{
public:
    Timer();
    void start();
    void pause();
    void resume();
    void reset();
    Ec_uint64 get_time_sec();
    Ec_uint64 get_time_milli();
    Ec_uint64 get_time_micro();
    Ec_uint64 get_time_nano();

private:
    Ec_uint64 t0_sec = 0;
    Ec_uint64 t0_milli = 0;
    Ec_uint64 t0_micro = 0;
    Ec_uint64 t0_nano = 0;

    Ec_uint64 t_pause_sec = 0;
    Ec_uint64 t_pause_milli = 0;
    Ec_uint64 t_pause_micro = 0;
    Ec_uint64 t_pause_nano = 0;

    Ec_uint64 t_resume_sec = 0;
    Ec_uint64 t_resume_milli = 0;
    Ec_uint64 t_resume_micro = 0;
    Ec_uint64 t_resume_nano = 0;

    Ec_boolean is_pause = Ec_false;
};

#endif // TIMER_H
