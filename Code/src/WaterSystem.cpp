#include "headers/WaterSystem.h"
WaterSystem::WaterSystem(const vector<Reservoir>& reservoirs, const vector<PumpingStation>& pumpingStations,const vector<City>& cities, const vector<Pipe>& pipes)
        : reservoirs(reservoirs), pumpingStations(pumpingStations), cities(cities), pipes(pipes) {}

// Getter method definitions
vector<Reservoir> WaterSystem::getReservoirs() const {
    return reservoirs;
}

vector<PumpingStation> WaterSystem::getPumpingStations() const {
    return pumpingStations;
}

vector<City> WaterSystem::getCities() const {
    return cities;
}

vector<Pipe> WaterSystem::getPipes() const {
    return pipes;
}