/*
    Person.h
    Author: Amir Lorvand
    Created: 7 Mar 2024
    Updated: 7 Mar 2024
*/

#include <iostream>
#pragma once
class Person
{
private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string telephone;
    std::string password;

public:
    std::string getFirstName() const;
    void setFirstName(std::string firstName);
    std::string getLastName() const;
    void setLastName(std::string lastName);
    std::string getEmail() const;
    void setEmail(std::string email);
    std::string getTelephone() const;
    void setTelephone(std::string telephone);
    std::string getPassword() const;
    void setPassword(std::string password);
};
