/*
    Instructor.h
    Author: Amir Lorvand
    Created: 9 Mar 2024
    Updated: 12 Mar 2024
*/

#include <iostream>
#include <vector>
#include "Car.h"
#include "Person.h"
#include "Date.h"
#include "Lesson.h"
#pragma once
class Lesson;
class Member;
class Instructor : public Person
{
private:
    int instructorID;
    std::vector<std::string> daysAvailable;
    Car car;

public:
    Instructor();
    Instructor(int instructorID, std::string firstName, std::string lastName,
               std::string email, std::string password, std::string telephone, Car car, std::vector<std::string> daysAvailable);
    int getInstructorID() const;
    Car getCar() const;
    void setCar(Car car);
    std::vector<std::string> getDaysAvailable() const; 
    void setDaysAvailable(std::vector<std::string> newDaysAvailable);
};
