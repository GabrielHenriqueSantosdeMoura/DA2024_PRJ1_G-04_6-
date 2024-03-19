//
// Created by CTW02617-admin on 3/19/2024.
//

#include "Reservoir.h"

using namespace std;

Reservoir::Reservoir(const std::string &id) {}

Reservoir::Reservoir(const std::string& name, const std::string& municipality, int id, const std::string& code, double maxDelivery)
        : name(name), municipality(municipality), id(id), code(code), maxDelivery(maxDelivery) {}

string Reservoir::getName() const {
    return name;
}

 string Reservoir::getMunicipality() const {
    return municipality;
}

int Reservoir::getId() const {
    return id;
}

string Reservoir::getCode() const {
    return code;
}

double Reservoir::getMaxDelivery() const {
    return maxDelivery;
}
