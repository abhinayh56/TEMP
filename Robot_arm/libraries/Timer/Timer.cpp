#include "Timer.h"

Timer::Timer() {}

void Timer::start()
{
    reset();
}

void Timer::pause()
{
    if (is_pause == Ec_false)
    {
        t_pause_sec += std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        t_pause_milli += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        t_pause_micro += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        t_pause_nano += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        
        is_pause = Ec_true;
    }
}

void Timer::resume()
{
    if (is_pause == Ec_true)
    {
        t_resume_sec += std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        t_resume_milli += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        t_resume_micro += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        t_resume_nano += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        is_pause = Ec_false;
    }
}

void Timer::reset()
{
    t0_sec = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    t0_milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    t0_micro = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    t0_nano = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Ec_uint64 Timer::get_time_sec()
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - t0_sec - t_resume_sec + t_pause_sec;
}

Ec_uint64 Timer::get_time_milli()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t0_milli - t_resume_milli + t_pause_milli;
}

Ec_uint64 Timer::get_time_micro()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t0_micro - t_resume_micro + t_pause_micro;
}

Ec_uint64 Timer::get_time_nano()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t0_nano - t_resume_nano + t_pause_nano;
}
