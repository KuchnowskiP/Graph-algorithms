//
// Created by kuchn on 4/13/2023.
//

#ifndef UNTITLED_TIMECOUNTER_H
#define UNTITLED_TIMECOUNTER_H

class TimeCounter {
    long long int read_QPC();               //pobranie momentu startu
public:
    void startTimer(long long int &start);  //funkcja startujaca timer, zwracajaca moment startu
    void getTime(long long int start);      //funkcja stopujaca timer, obliczajaca ile czasu uplynelo od startu
    long long int returnTime(long long int start);      //funkcja stopujaca timer, obliczajaca ile czasu uplynelo od startu
};


#endif //UNTITLED_TIMECOUNTER_H
