#include "headers/PumpingStation.h"
using namespace std;

PumpingStation::PumpingStation(int id) : id(id) {}

PumpingStation::PumpingStation(int id, const string& code) : id(id), code(code) {}

int PumpingStation::getId() const {
    return id;
}

string PumpingStation::getCode() const {
    return code;
}
