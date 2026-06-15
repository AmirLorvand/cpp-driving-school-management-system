/*
    Person.cpp
    Author: Amir Lorvand
    Created: 7 Mar 2024
    Updated: 7 Mar 2024
*/

#include "Person.h"

std::string Person::getFirstName() const
{
    return this->firstName;
}

void Person::setFirstName(std::string firstName)
{
    this->firstName = firstName;
}

std::string Person::getLastName() const
{
    return this->lastName;
}

void Person::setLastName(std::string lastName)
{
    this->lastName = lastName;
}

std::string Person::getEmail() const
{
    return this->email;
}

void Person::setEmail(std::string email)
{
    this->email = email;
}

std::string Person::getTelephone() const
{
    return this->telephone;
}

void Person::setTelephone(std::string telephone)
{
    this->telephone = telephone;
}

std::string Person::getPassword() const
{
    return this->password;
}

void Person::setPassword(std::string password)
{
    this->password = password;
}
