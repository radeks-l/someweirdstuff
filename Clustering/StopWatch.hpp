/*
 * StopWatch.hpp
 *
 *  Created on: 10.12.2016
 *      Author: radek
 */

#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#include <chrono>
#include <iostream>
#include <string>

class StopWatch {
public:
    typedef std::chrono::steady_clock     Clock;
    typedef Clock::time_point             TimePoint;

    StopWatch(const std::string &message);
    ~StopWatch();
private:
    TimePoint mTimeStart;
    std::string mMessage;
};

#endif /* STOPWATCH_HPP_ */
