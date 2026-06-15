#include "Member.h"
#include "Person.h"

Member::Member(){
    this->memberID = -1;
    this->setFirstName("");
    this->setLastName("");
    this->setEmail("");
    this->setPassword("");
    this->setTelephone("");
    Instructor instructor;
    this->setInstructor(instructor);
}

Member::Member(int memberID, std::string firstName, std::string lastName, std::string email, std::string password, std::string telephone)
{
    this->memberID = memberID;
    this->setFirstName(firstName);
    this->setLastName(lastName);
    this->setEmail(email);
    this->setPassword(password);
    this->setTelephone(telephone);
    Instructor instructor;
    this->setInstructor(instructor);
}


int Member::getMemberID() const
{
  return memberID;
}

int Member::getPackageHours() const
{
    return packageHours;
}

void Member::setPackageHours(int hours)
{
    packageHours = hours;
}

std::string Member::getTransmission() const
{
    return transmission;
}

void Member::setTransmission(std::string transm)
{
  transmission = transm;
}
Instructor Member::getInstructor() const
{
  return this->instructor;
}
void Member::setInstructor(Instructor newInstructor)
{
  this->instructor = newInstructor;
}
