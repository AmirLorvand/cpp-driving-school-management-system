/*
    Date.cpp
    Author: Amir Lorvand
    Created: 12 Mar 2024
    Updated: 12 Mar 2024
*/

#include "Date.h"
#include <ctime>

Date::Date(){
  // this constructor sets the date object to todays date
    time_t now = time(0);
    tm* localTime = localtime(&now);

    this->day = localTime->tm_mday;
    this->month = localTime->tm_mon + 1;  // tm_mon is zero-based (january = 0)
    this->year = localTime->tm_year + 1900;  // tm_year is years since 1900
    this->timeSlot = 0;
}

Date::Date(int timeSlot, int day, int month, int year)
{
    this->timeSlot = timeSlot;
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getTimeSlot()
{
    return this->timeSlot;
}

void Date::setTimeSlot(int timeSlot)
{
    this->timeSlot = timeSlot;
}

int Date::getDay()
{
    return this->day;
}

void Date::setDay(int day)
{
    this->day = day;
}

int Date::getMonth()
{
    return this->month;
}

void Date::setMonth(int month)
{
    this->month = month;
}

int Date::getYear()
{
    return this->year;
}

void Date::setYear(int year)
{
    this->year = year;
}

std::string Date::displayDate()
{
    return std::to_string(getDay()) + " / " + std::to_string(getMonth()) + " / " + std::to_string(getYear());
}

void Date::displayTimeSlot(int timeSlot)
{
    switch (timeSlot)
    {
    case 1:
        std::cout << "07:00 - 09:00";
        break;
    case 2:
        std::cout << "09:00 - 11:00";
        break;
    case 3:
        std::cout << "11:00 - 13:00";
        break;
    case 4:
        std::cout << "13:00 - 15:00";
        break;
    case 5:
        std::cout << "15:00 - 17:00";
        break;
    default:
        std::cout << "Invalid time slot";
        break;
    }
}

// Calculate the difference in days between two dates
int Date::calculateDaysDifference(const Date& otherDate) const {
    // Convert both dates to days since some fixed date (e.g., January 1, 1970)
    // For simplicity, let's assume each month has 30 days and each year has 360 days
    int thisDays = this->year * 360 + this->month * 30 + this->day;
    int otherDays = otherDate.year * 360 + otherDate.month * 30 + otherDate.day;

    // Calculate the difference in days
    int difference = thisDays - otherDays;

    // Return the absolute difference
    return abs(difference);
}
