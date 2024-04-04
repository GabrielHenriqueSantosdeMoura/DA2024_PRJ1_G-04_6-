#include <string>
#include <fstream>
#include <sstream>
#include "headers/DataReader.h"
#include "headers/City.h"
#include "headers/WaterInfrastructure.h"

using namespace std;

vector<WaterInfrastructure> DataReader::readCities(const string &path) {
    ifstream citiesMadeira_file(path);
    if (!citiesMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;
    vector<WaterInfrastructure> cities;

    getline(citiesMadeira_file, line); // Skip header line
    while(getline(citiesMadeira_file, line)){
        istringstream iss(line);
        string name, id, code, demand, population;
        getline(getline(getline(getline(getline(iss, name, ','), id, ','), code, ','), demand, ','), population, '\r');

        double demandValue = stod(demand);
        int idValue = stoi(id);

        WaterInfrastructure city(name, idValue, code, demandValue, population);
        cities.push_back(city);
    }
    return cities;
}

vector<WaterInfrastructure> DataReader::readPumpingStations(const string &path) {
    ifstream stationMadeira_file(path);
    if (!stationMadeira_file.is_open()) {
        throw runtime_error("Pumping Stations Madeira file does not exist");
    }

    string line;
    vector<WaterInfrastructure> stations;

    getline(stationMadeira_file, line); // Skip header line
    while (getline(stationMadeira_file, line)) {
        istringstream iss(line);
        string id, code;
        getline(getline(iss, id, ','), code, '\r');

        int idValue = stoi(id);

        WaterInfrastructure pumpingStation(idValue, code);
        stations.push_back(pumpingStation);
    }
    return stations;
}

vector<WaterInfrastructure> DataReader::readReservoirs(const string &path) {
    ifstream reservoirsMadeira_file(path);
    if (!reservoirsMadeira_file.is_open()) {
        throw runtime_error("Reservoirs Madeira file does not exist");
    }

    string line;
    vector<WaterInfrastructure> reservoirs;

    getline(reservoirsMadeira_file, line); // Skip header line
    while (getline(reservoirsMadeira_file, line)) {
        istringstream iss(line);
        string name, municipality, id, code, maxDelivery;
        getline(getline(getline(getline(getline(iss, name, ','), municipality, ','), id, ','), code, ','), maxDelivery, '\r');
        int idValue = stoi(id);
        double maxDeliveryValue = stod(maxDelivery);

        WaterInfrastructure reservoir(name, municipality, idValue, code, maxDeliveryValue);
        reservoirs.push_back(reservoir);
    }
    return reservoirs;
}

vector<WaterInfrastructure> DataReader::readPipes(const string &path) {
    ifstream pipesMadeira_file(path);
    if (!pipesMadeira_file.is_open()) {
        throw runtime_error("PipesMadeira file does not exist");
    }

    string line;
    vector<WaterInfrastructure> pipes;

    getline(pipesMadeira_file, line); // Skip header line
    while (getline(pipesMadeira_file, line)) {
        istringstream iss(line);
        string sourceService, targetService, capacity, direction;
        getline(getline(getline(getline(iss, sourceService, ','), targetService, ','), capacity, ','), direction, '\r');

        double capacityValue = stod(capacity);
        bool unidirectional = (direction[0] == '1');

        WaterInfrastructure pipe(sourceService, targetService, capacityValue, unidirectional);
        pipes.push_back(pipe);

    }
    return pipes;
}
