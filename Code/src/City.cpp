#include "headers/City.h"
using namespace std;

City::City(const string& name,int id,  const string& code, double demand, const string & population)
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

string City::getPopulation() const {
    return population;
}