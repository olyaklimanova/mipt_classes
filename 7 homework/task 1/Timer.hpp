#pragma once

#include <iostream>
#include <chrono>
#include <ratio>
#include <exception>

template <typename T = std::chrono::milliseconds>
class Timer
{
private:
    using clock = std::chrono::steady_clock;
    using dur = std::chrono::steady_clock::duration;

public:
    //  Constructors
    Timer(const std::string& new_name = "Timer") :
        m_t_point(clock::now()), m_timers_name(new_name), is_working(true) {}

    //  Return current duration
    dur get_current_duration()
    {
        recalc_duration();
        return m_duration;
    }


    //  Destructor. It prints the final duration
    ~Timer() noexcept
    {
        std::cout << "\n \"" << m_timers_name << "\" worked for " << std::chrono::duration_cast<T>(get_current_duration()).count() << std::endl;
    }

    void pause()
    {
        recalc_duration();
        is_working = false;
    }

    void reset()
    {
        m_t_point = clock::now();
        is_working = true;
    }

private:
    //  To recalculate duration
    void recalc_duration()
    {
        clock::time_point temp = clock::now();
        m_duration += (temp - m_t_point);
        m_t_point = temp;
    }

    //  Shows is timer going or staying in a pause state
    bool is_working;

    clock::time_point m_t_point;
    dur m_duration{ dur::zero() };

    std::string m_timers_name;
};



template <typename T = std::chrono::milliseconds>
class Timer_with_return
{
private:
    using clock = std::chrono::steady_clock;
    using dur = std::chrono::steady_clock::duration;

public:
    //  Constructors
    Timer_with_return(std::size_t& work_time, const std::string& new_name = "Timer") :
        m_work_time(work_time), m_t_point(clock::now()), m_timers_name(new_name), is_working(true) {}

    //  Return current duration
    dur get_current_duration()
    {
        recalc_duration();
        return m_duration;
    }


    //  Destructor. It prints the final duration
    ~Timer_with_return() noexcept
    {
        m_work_time = std::chrono::duration_cast<T>(get_current_duration()).count();
    }

    void pause()
    {
        recalc_duration();
        is_working = false;
    }

    void reset()
    {
        m_t_point = clock::now();
        is_working = true;
    }

private:
    //  To recalculate duration
    void recalc_duration()
    {
        clock::time_point temp = clock::now();
        m_duration += (temp - m_t_point);
        m_t_point = temp;
    }

    //  Shows is timer going or staying in a pause state
    bool is_working;

    std::size_t& m_work_time;

    clock::time_point m_t_point;
    dur m_duration{ dur::zero() };

    std::string m_timers_name;
};
