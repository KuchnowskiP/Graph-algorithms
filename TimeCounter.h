//
// Created by Piotr Kuchnowski on 4/13/2023.
//

#ifndef UNTITLED_TIMECOUNTER_H
#define UNTITLED_TIMECOUNTER_H

class TimeCounter {
    long long int read_QPC();               //getting current clock
public:
    void startTimer(long long int &start);  //function that starts the timer
    void getTime(long long int start);      //function that stops the timer and just displays passed time
    long long int returnTime(long long int start);      //function that stops the timer and returns passed time as a long long int value
};


#endif //UNTITLED_TIMECOUNTER_H
