#include "../include/Animal.h"
#include <chrono>
#include <iomanip>
#include <sstream>

Animal::Animal(int age, std::string gender, std::string birthSeason, 
               std::string color, double weight, std::string origin, std::string species)
    : age(age), gender(std::move(gender)), birthSeason(std::move(birthSeason)),
      color(std::move(color)), weight(weight), origin(std::move(origin)),
      species(std::move(species)) {
    
    // Set arrival date to current date in ISO 8601 format
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    arrivalDate = ss.str();
}
