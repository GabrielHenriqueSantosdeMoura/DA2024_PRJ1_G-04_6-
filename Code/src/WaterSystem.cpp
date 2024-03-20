#include "headers/WaterSystem.h"
WaterSystem::WaterSystem(const vector<Reservoir>& reservoirs, const vector<PumpingStation>& pumpingStations,const vector<City>& cities, const vector<Pipe>& pipes)
        : reservoirs(reservoirs), pumpingStations(pumpingStations), cities(cities), pipes(pipes) {}

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

void WaterSystem::addCity(const City &city) {
    cities.push_back(city);
}
void WaterSystem::addPipe(const Pipe &pipe) {
    pipes.push_back(pipe);
}
void WaterSystem::addPumpingStation(const PumpingStation &pumpingStation) {
    pumpingStations.push_back(pumpingStation);
}
void WaterSystem::addReservoir(const Reservoir &reservoir) {
    reservoirs.push_back(reservoir);
}
