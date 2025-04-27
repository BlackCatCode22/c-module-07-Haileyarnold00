#include "Animal.h"
#include "Hyena.h"
#include "Lion.h"
#include "Tiger.h"
#include "Bear.h"
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

int main() {
    try {
        // Test one animal of each type
        std::vector<std::unique_ptr<Animal>> animals;

        // Create test animals
        animals.push_back(std::make_unique<Hyena>(4, "female", "spring", "tan", 70, "Friguia_Park_Tunisia"));
        animals.push_back(std::make_unique<Lion>(6, "male", "summer", "golden", 400, "Zanzibar_Tanzania"));
        animals.push_back(std::make_unique<Tiger>(3, "female", "fall", "orange", 290, "Bengal_India"));
        animals.push_back(std::make_unique<Bear>(8, "male", "winter", "brown", 850, "Alaska_USA"));

        // Set test names
        animals[0]->setName("Kamari");
        animals[1]->setName("Mufasa");
        animals[2]->setName("Rajah");
        animals[3]->setName("Baloo");

        // Print descriptions to verify format
        std::cout << "\nTesting animal descriptions:\n\n";
        
        std::map<std::string, std::vector<std::string>> habitatDescriptions;
        for (const auto& animal : animals) {
            habitatDescriptions[animal->getSpecies()].push_back(animal->getDescription());
        }

        // Print organized by habitat
        for (const auto& [species, descriptions] : habitatDescriptions) {
            std::cout << species << " Habitat:\n";
            for (const auto& desc : descriptions) {
                std::cout << "    " << desc << "\n";
            }
            std::cout << "\n";
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
