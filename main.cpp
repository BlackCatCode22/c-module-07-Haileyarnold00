#include "Animal.h"
#include "Hyena.h"
#include "Lion.h"
#include "Tiger.h"
#include "Bear.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

// Function to read and parse animal data from file
std::vector<std::unique_ptr<Animal>> readAnimalData(const std::string& filename) {
    std::vector<std::unique_ptr<Animal>> animals;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line1, line2;
    while (std::getline(file, line1) && std::getline(file, line2)) {
        // Parse first line: age gender species
        std::istringstream iss1(line1);
        int age;
        std::string gender, species;
        iss1 >> age >> gender >> species;

        // Parse second line: birth_season color weight origin
        std::istringstream iss2(line2);
        std::string birthSeason, color, origin;
        double weight;
        iss2 >> birthSeason >> color >> weight >> origin;

        // Create appropriate animal object based on species
        if (species == "hyena") {
            animals.push_back(std::make_unique<Hyena>(age, gender, birthSeason, 
                                                    color, weight, origin));
        } else if (species == "lion") {
            animals.push_back(std::make_unique<Lion>(age, gender, birthSeason,
                                                   color, weight, origin));
        } else if (species == "tiger") {
            animals.push_back(std::make_unique<Tiger>(age, gender, birthSeason,
                                                    color, weight, origin));
        } else if (species == "bear") {
            animals.push_back(std::make_unique<Bear>(age, gender, birthSeason,
                                                   color, weight, origin));
        } else {
            throw std::runtime_error("Unknown species: " + species);
        }
    }

    return animals;
}

// Function to assign names from file
void assignNames(const std::string& filename, std::vector<std::unique_ptr<Animal>>& animals) {
    std::map<std::string, std::vector<std::string>> speciesNames;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string species, name;
        iss >> species >> name;
        speciesNames[species].push_back(name);
    }

    // Assign names to animals
    std::map<std::string, size_t> nameIndex;
    for (auto& animal : animals) {
        std::string species = animal->getSpecies();
        if (speciesNames.find(species) != speciesNames.end() && 
            nameIndex[species] < speciesNames[species].size()) {
            animal->setName(speciesNames[species][nameIndex[species]++]);
        }
    }
}

// Function to write zoo population report
void writeZooReport(const std::string& filename, 
                   const std::vector<std::unique_ptr<Animal>>& animals) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    // Group animals by species
    std::map<std::string, std::vector<std::string>> habitatDescriptions;
    for (const auto& animal : animals) {
        habitatDescriptions[animal->getSpecies()].push_back(animal->getDescription());
    }

    // Write report
    for (const auto& [species, descriptions] : habitatDescriptions) {
        file << species << " Habitat:\n";
        for (const auto& desc : descriptions) {
            file << "    " << desc << "\n";
        }
        file << "\n";
    }
}

int main() {
    try {
        // For testing in CLion
        auto animals = readAnimalData("test_input/arrivingAnimals.txt");
        
        // Assign names
        assignNames("test_input/animalNames.txt", animals);
        
        // Write population report
        writeZooReport("test_input/zooPopulation.txt", animals);
        
        // TODO: Change paths back to C:/cpptxtfiles/ before final submission
        // auto animals = readAnimalData("C:/cpptxtfiles/arrivingAnimals.txt");
        // assignNames("C:/cpptxtfiles/animalNames.txt", animals);
        // writeZooReport("C:/cpptxtfiles/zooPopulation.txt", animals);
        
        std::cout << "Zoo population report generated successfully!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
