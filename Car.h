/*
    Car.h
    Author: RanaSystems
    Created: 7 Mar 2024
    Updated: 13 Mar 2024
*/

#include <iostream>
#pragma once
class Car
{
private:
    std::string carMake;
    std::string carModel;
    std::string carReg;
    std::string carTransmission;

public:
    Car();
    Car(std::string carMake, std::string carModel, std::string carReg, std::string carTransmission);
    std::string getCarMake();
    void setCarMake(std::string carMake);
    std::string getCarModel();
    void setCarModel(std::string carModel);
    std::string getCarReg();
    void setCarReg(std::string carReg);
    std::string getCarTransmission();
    void setCarTransmission(std::string carTransmission);
};