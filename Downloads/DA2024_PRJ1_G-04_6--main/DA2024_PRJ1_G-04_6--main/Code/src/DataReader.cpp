#include <string>
#include <fstream>
#include <sstream>
#include "headers/DataReader.h"
#include "headers/City.h"
#include "headers/WaterInfrastructure.h"

using namespace std;

//definition of a DataReader namespace;
vector<WaterInfrastructure> DataReader::readCities(const string &path) {
    //stream to read the Cities file

    ifstream citiesMadeira_file(path);

    //check if the file exists

    if (!citiesMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    //vector to store cities
    vector <WaterInfrastructure> cities;

    //to skip the first line of the csv files
    getline(citiesMadeira_file,line);

    while(getline(citiesMadeira_file,line)){
        istringstream iss(line);
        string name, id, code, demand, population;
        getline(getline(getline(getline(getline(iss, name, ','), id, ','), code, ','), demand, ','), population, '\r');

        double demandValue = stod(demand);
        int idValue = stoi (id);

        WaterInfrastructure city(name, idValue, code, demandValue, population);
        cities.push_back(city);
    }
    return cities;
}

vector<WaterInfrastructure> DataReader:: readPumpingStations (const string &path){
        //stream to read the Stations file
        ifstream stationMadeira_file(path);

        //check if the file exists
        if (!stationMadeira_file.is_open()) {
            throw runtime_error("Pumping Stations Madeira file does not exist");
        }

        string line;

        //vector to store the pumping stations
        vector <WaterInfrastructure> stations;

        getline(stationMadeira_file,line);
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
vector<WaterInfrastructure> DataReader::readReservoirs (const string &path){
        //stream to read the Reservoirs file
        ifstream reservoirsMadeira_file(path);

        //check if the file exists
        if (!reservoirsMadeira_file.is_open()) {
            throw runtime_error("Reservoirs Madeira file does not exist");
        }

        string line;

        //vector to store reservoirs
        vector <WaterInfrastructure> reservoirs;

        getline(reservoirsMadeira_file,line);
        while (getline(reservoirsMadeira_file, line)) {
            istringstream iss(line);
            string name, municipality, id, code, maxDelivery;
            getline(getline(getline(getline(getline(iss, name, ','), municipality, ','), id, ','), code, ','), maxDelivery,'\r');
            int idValue = stoi(id);
            double maxDeliveryValue = stod(maxDelivery);

            WaterInfrastructure reservoir(name, municipality, idValue, code, maxDeliveryValue);
            reservoirs.push_back(reservoir);
        }
    return reservoirs;
    }

vector<WaterInfrastructure> DataReader::readPipes (const string &path) {
    //stream to read the Pipes file
    ifstream pipesMadeira_file(path);

    //check if the file exists
    if (!pipesMadeira_file.is_open()) {
        throw runtime_error("PipesMadeira file does not exist");
    }

    string line;

    //vector to store the pipes
    vector<WaterInfrastructure> pipes;

    getline(pipesMadeira_file,line);
    while (getline(pipesMadeira_file, line)) {
        istringstream iss(line);
        string sourceService, targetService, capacity, direction;
        getline(getline(getline(getline(iss, sourceService, ','), targetService, ','), capacity, ','), direction, '\r');
        // Convert capacity to double
        double capacityValue = stod(capacity);
        if (direction[0] == '1'){
            WaterInfrastructure pipe(sourceService,targetService,capacityValue);
            pipes.push_back(pipe);
        }
        else{
            WaterInfrastructure pipe1(sourceService,targetService,capacityValue);
            WaterInfrastructure pipe2(targetService,sourceService,capacityValue);
            pipes.push_back(pipe1);
            pipes.push_back(pipe2);
        }

    }
    return pipes;
}






