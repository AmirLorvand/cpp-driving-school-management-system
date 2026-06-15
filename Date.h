/*
    Date.h
    Author: RanaSystems
    Created: 10 Mar 2024
    Updated: 10 Mar 2024
*/

#include <iostream>
#pragma once
class Date {
    private:
        int day;
        int month;
        int year;
        int timeSlot;

    public:
        Date();
        Date(int timeSlot, int day, int month, int year);
        int getTimeSlot();
        void setTimeSlot(int timeSlot);
        int getDay();
        void setDay(int day);
        int getMonth();
        void setMonth(int month);
        int getYear();
        void setYear(int year);
        std::string displayDate();
        void displayTimeSlot(int timeSlot);
        // Calculate the difference in days between two dates
        int calculateDaysDifference(const Date& otherDate) const;
};
