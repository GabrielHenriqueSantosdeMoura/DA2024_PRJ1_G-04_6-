#include <string>
#include <fstream>
#include <sstream>
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"
#include "headers/City.h"

using namespace std;

//the class will add the Vertices of a Graph
DataReader::DataReader(const string &citiesMadeira, const string &pipesMadeira,const string &reservoirsMadeira, const string &stationsMadeira)
{
    /// Create an instance of WaterSystem class
    WaterSystem waterSystem;

    readCities(citiesMadeira, waterSystem);

    readPipes(pipesMadeira, waterSystem);

    readReservoirs(reservoirsMadeira, waterSystem);

    readPumpingStations(stationsMadeira, waterSystem);

}

void DataReader::readCities(const string& citiesMadeira, WaterSystem& waterSystem) {
    //stream to read the Cities_Madeira file and represent as a graph
    ifstream citiesMadeira_file(citiesMadeira);

    //check if the file exists
    if (!citiesMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    while(getline(citiesMadeira_file,line)){
        istringstream iss(line);
        string name, id, code, demand, population;
        getline(getline(getline(getline(getline(iss, name, ','), id, ','), code, ','), demand, ','), population, '\r');
        double demandValue = stoi(demand);
        int idValue = stoi (id);

        City city(name,idValue,code,demandValue,population);
        waterSystem.addCity(city);
    }
}

void DataReader::readPipes(const string& pipesMadeira, WaterSystem& waterSystem) {
    //stream to read the Cities_Madeira file and represent as a graph
    ifstream pipesMadeira_file(pipesMadeira);

    //check if the file exists
    if (!pipesMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    while(getline(pipesMadeira_file,line)){
        istringstream iss(line);
        string sourceService,targetService,capacity,direction;
        getline(getline(getline(getline(iss, sourceService, ','), targetService, ','), capacity, ','), direction,'\r');
        double capacityValue = stoi(capacity);
        bool directionValue = stoi (direction);

        Pipe pipe(sourceService,targetService,capacityValue,directionValue);
        waterSystem.addPipe(pipe);
    }
}

void DataReader::readReservoirs(const string& reservoirsMadeira, WaterSystem &waterSystem) {
    //stream to read the Cities_Madeira file and represent as a graph
    ifstream reservoirsMadeira_file(reservoirsMadeira);

    //check if the file exists
    if (!reservoirsMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    while(getline(reservoirsMadeira_file,line)){
        istringstream iss(line);
        string name,municipality,id,code,maxDelivery;
        getline(getline(getline(getline(getline(iss, name, ','), municipality, ','), id, ','), code, ','), maxDelivery, '\r');
        int idValue = stoi(id);
        double maxDeliveryValue = stoi (maxDelivery);

        Reservoir reservoir(name,municipality,idValue,code,maxDeliveryValue);
        waterSystem.addReservoir(reservoir);
    }
}

void DataReader::readPumpingStations(const std::string &stationsMadeira, WaterSystem &waterSystem) {
    //stream to read the Cities_Madeira file and represent as a graph
    ifstream stationMadeira_file(stationsMadeira);

    //check if the file exists
    if (!stationMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    while(getline(stationMadeira_file, line)){
        istringstream iss(line);
        string id, code;
        getline(getline(iss, id, ','), code, '\r');
        int idValue = stoi(id);
        PumpingStation pumpingStation(idValue, code);
        waterSystem.addPumpingStation(pumpingStation);
    }
}