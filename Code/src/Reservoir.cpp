
#include "headers/Reservoir.h"
using namespace std;

Reservoir::Reservoir(const string &id) {}

Reservoir::Reservoir(const string& name, const string& municipality, int id, const string& code, double maxDelivery)
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
