#include "../include/Lion.h"
#include <sstream>
#include <iomanip>
#include <chrono>

int Lion::nextId = 1;

Lion::Lion(int age, std::string gender, std::string birthSeason,
           std::string color, double weight, std::string origin)
    : Animal(age, std::move(gender), std::move(birthSeason),
            std::move(color), weight, std::move(origin), "Lion") {
    id = genUniqueID();
}

std::string Lion::genBirthDay() const {
    // Get current year from system clock
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time);
    int birthYear = tm.tm_year + 1900 - age;
    
    // Convert birth season to corresponding month number
    int month;
    if (birthSeason == "spring") month = 3;
    else if (birthSeason == "summer") month = 6;
    else if (birthSeason == "fall") month = 9;
    else month = 12;
    
    // Format the date in ISO 8601 format (YYYY-MM-DD)
    std::stringstream ss;
    // Use the 15th of the month as a default day
    ss << birthYear << "-" << std::setw(2) << std::setfill('0') << month 
       << "-" << std::setw(2) << std::setfill('0') << 15;
    return ss.str();
}

std::string Lion::genUniqueID() {
    std::stringstream ss;
    ss << "LI" << std::setw(2) << std::setfill('0') << nextId++;
    return ss.str();
}

std::string Lion::getDescription() const {
    std::stringstream ss;
    ss << id << "; " << name << "; birth date " << genBirthDay() 
       << "; " << color << " color; " << gender << "; " 
       << weight << " pounds; from " << origin 
       << "; arrived " << arrivalDate;
    return ss.str();
}
