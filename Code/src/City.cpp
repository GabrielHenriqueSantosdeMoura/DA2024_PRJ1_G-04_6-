
#include "headers/City.h"
using namespace std;

City::City(int id) : id(id) {}

City::City(int id, const string& name, const string& code, double demand, int population)
        : name(name), id(id), code(code), demand(demand), population(population) {}

string City::getName() const {
    return name;
}

int City::getId() const {
    return id;
}

string City::getCode() const {
    return code;
}

double City::getDemand() const {
    return demand;
}

int City::getPopulation() const {
    return population;
}