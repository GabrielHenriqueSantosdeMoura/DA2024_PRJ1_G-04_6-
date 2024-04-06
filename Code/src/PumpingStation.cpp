#include "headers/PumpingStation.h"
using namespace std;


PumpingStation::PumpingStation(int id, const string &code):id(id), code(code) {}

string PumpingStation::getCode() const {
    return code;
}
