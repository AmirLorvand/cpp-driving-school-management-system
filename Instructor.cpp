#include "Instructor.h"

// Constructor implementation
//Default constructor
Instructor::Instructor(){
    this->instructorID = -1;
    this->setFirstName("");
    this->setLastName("");
    this->setEmail("");
    this->setPassword("");
    this->setTelephone("");
    Car car;
    this->car = car;
    this->setDaysAvailable(std::vector<std::string>{"","","","","","",""});
}

Instructor::Instructor(int instructorID, std::string firstname, std::string lastname,
		       std::string email, std::string password, std::string telephone, Car car, std::vector<std::string> daysAvailable)
{
    this->instructorID = instructorID;
    this->setFirstName(firstname);
    this->setLastName(lastname);
    this->setEmail(email);
    this->setPassword(password);
    this->setTelephone(telephone);
    this->car = car;
    this->setDaysAvailable(daysAvailable);;
}
// Getter and setter implementations
int Instructor::getInstructorID() const{
    return this->instructorID;
}
    
Car Instructor::getCar() const{
    return this->car;
}

void Instructor::setCar(Car car) {
    this->car = car;
}
std::vector<std::string> Instructor::getDaysAvailable() const{
    return this->daysAvailable;
}

void Instructor::setDaysAvailable(std::vector<std::string> newDaysAvailable){
    this->daysAvailable = newDaysAvailable;
}
