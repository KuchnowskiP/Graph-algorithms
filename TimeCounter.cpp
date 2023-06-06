//
// Created by kuchn on 4/13/2023.
//

#include "TimeCounter.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

long long int TimeCounter::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}

void TimeCounter::startTimer(long long int &start) {
    start = read_QPC();
}

void TimeCounter::getTime(long long int start) {
    long long int frequency, elapsed;

    elapsed = read_QPC() - start;

    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    std::cout << "Time [s] = " << std::fixed << std::setprecision(3) << (float)elapsed /
                                                                        frequency << std::endl;
    std::cout << "Time [ms] = " << std::setprecision(0) << (1000.0 * elapsed) /
                                                           frequency << std::endl;
    std::cout << "Time [us] = " << std::setprecision(0) << (1000000.0 * elapsed) /
                                                           frequency << std::endl << std::endl;
    system("PAUSE");
}

long long int TimeCounter::returnTime(long long int start){
    long long int elapsed;

    elapsed = read_QPC() - start;

    return elapsed;
}


