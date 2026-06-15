/*
    Member.h
    Author: Amir Lorvand
    Created: 10 Mar 2024
    Updated: 10 Mar 2024
*/

#include <iostream>
#include "Person.h"
#include "Date.h"
#include "Instructor.h"
#include <vector>
#pragma once
class Lesson;
class Instructor;
class Member : public Person
{
private:
    int memberID;
    std::string transmission;
    Instructor instructor;
    int packageHours;

public:
    Member();
    Member(int memberID, std::string firstName, std::string lastName, std::string email, std::string password, std::string telephone);
    int getMemberID() const; 
    int getPackageHours() const;
    void setPackageHours(int packageHours);
    std::string getTransmission() const;
    void setTransmission(std::string transm);
    Instructor getInstructor() const;
    void setInstructor(Instructor newInstructor);
};
