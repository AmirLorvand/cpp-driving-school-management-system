/*
    Car.cpp
    Author: RanaSystems
    Created: 7 Mar 2024
    Updated: 7 Mar 2024
*/

#include "Car.h"

Car::Car()
{
    // Default constructor implementation
    this->carMake = "";
    this->carModel = "";
    this->carReg = "";
    this->carTransmission = "";
}

Car::Car(std::string carMake, std::string carModel, std::string carReg, std::string carTransmission)
{
    this->carMake = carMake;
    this->carModel = carModel;
    this->carReg = carReg;
    this->carTransmission = carTransmission;
}
std::string Car::getCarMake() {
    return this->carMake;
}
void Car::setCarMake(std::string carMake) {
    this->carMake = carMake;
}
std::string Car::getCarModel() {
    return this->carModel;
}
void Car::setCarModel(std::string carModel) {
    this->carModel = carModel;
}
std::string Car::getCarReg(){
    return this->carReg;
}
void Car::setCarReg(std::string carReg){
    this->carReg = carReg;
}
std::string Car::getCarTransmission(){
    return this->carTransmission;
}
void Car::setCarTransmission(std::string carTransmission){
    this->carTransmission = carTransmission;
}