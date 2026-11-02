/*
 * StopWatch.cpp
 *
 *  Created on: 10.12.2016
 *      Author: radek
 */

#include "StopWatch.hpp"

namespace cho = std::chrono;

StopWatch::StopWatch(const std::string &message):
    mMessage(message) {
    mTimeStart = Clock::now();
}

StopWatch::~StopWatch() {
    TimePoint timeEnd = Clock::now();
    auto elapsed = cho::duration_cast<cho::milliseconds>(timeEnd - mTimeStart);
    std::cout << "StopWatch, task: " << mMessage
            << ", millisec: " << elapsed.count() << std::endl;
}
