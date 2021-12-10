/*
 * Time.cpp
 *
 *  Created on: Nov 10, 2021
 *      Author: jorda
 */

#include <iostream>

#include "Time.h"

Time::Time() {
}

Time::~Time() {
}

void Time::Init(int hours, int minutes, int second) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = minutes;
}

void Time::TimeIn24HourFormat() {
    std::cout << this->hours << ":" << this->minutes << ":" << this->seconds
            << std::endl;
}

void Time::TimeIn12HourFormat() {
    int hours = this->hours;
    if (hours > 12) {
        hours -= 12;
    }
    std::cout << hours << ":" << this->minutes << ":" << this->seconds
            << std::endl;
}

int Time::GetHours() const {
    return hours;
}

void Time::SetHours(int hours) {
    this->hours = hours;
}

int Time::GetMinutes() const {
    return minutes;
}

void Time::SetMinutes(int minutes) {
    this->minutes = minutes;
}

int Time::GetSeconds() const {
    return seconds;
}

void Time::SetSeconds(int seconds) {
    this->seconds = seconds;
}
