/*
 * Time.h
 *
 *  Created on: Nov 10, 2021
 *      Author: jorda
 */

#ifndef TIME_H_
#define TIME_H_

class Time {
public:
    Time();
    virtual ~Time();

    void Init(int hours, int minutes, int second);

    void TimeIn12HourFormat();
    void TimeIn24HourFormat();
    int GetHours() const;
    void SetHours(int hours);
    int GetMinutes() const;
    void SetMinutes(int minutes);
    int GetSeconds() const;
    void SetSeconds(int seconds);

private:
    int hours;
    int minutes;
    int seconds;
};

#endif /* TIME_H_ */
