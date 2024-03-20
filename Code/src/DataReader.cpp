#include <string>
#include <fstream>
#include <sstream>
#include "headers/DataReader.h"
#include "headers/City.h"
using namespace std;

//DataReader::DataReader(const std::string &reservoirsMadeira, const std::string &pipesMadeira,
//                       const std::string &citiesMadeira, const std::string &stationsMadeira) {}

vector<City> DataReader::readCities(const string &path) {
    //stream to read the Cities_Madeira file and represent as a graph
    ifstream citiesMadeira_file(path);

    //check if the file exists
    if (!citiesMadeira_file.is_open()){
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    vector <City> cities;

    while(getline(citiesMadeira_file,line)){
        istringstream iss(line);
        string name, id, code, demand, population;
        getline(getline(getline(getline(getline(iss, name, ','), id, ','), code, ','), demand, ','), population, '\r');
        double demandValue = stod(demand);
        int idValue = stoi (id);
        //Add a vertex to the supplySystem
        City city(name,idValue,code,demandValue,population);
        cities.push_back(city);
    }
    return cities;
}

vector<PumpingStation> DataReader:: readPumpingStations (const string &path){
        //stream to read the Cities_Madeira file and represent as a graph
        ifstream stationMadeira_file(path);

        //check if the file exists
        if (!stationMadeira_file.is_open()) {
            throw runtime_error("Cities Madeira file does not exist");
        }

        string line;

        vector <PumpingStation> stations;

        while (getline(stationMadeira_file, line)) {
            istringstream iss(line);
            string id, code;
            getline(getline(iss, id, ','), code, '\r');
            int idValue = stoi(id);
            PumpingStation pumpingStation(idValue, code);
            stations.push_back(pumpingStation);
        }
        return stations;
    }
vector<Reservoir> DataReader::readReservoirs (const string &path){
        //stream to read the Cities_Madeira file and represent as a graph
        ifstream reservoirsMadeira_file(path);

        //check if the file exists
        if (!reservoirsMadeira_file.is_open()) {
            throw runtime_error("Cities Madeira file does not exist");
        }

        string line;

        vector <Reservoir> reservoirs;

        while (getline(reservoirsMadeira_file, line)) {
            istringstream iss(line);
            string name, municipality, id, code, maxDelivery;
            getline(getline(getline(getline(getline(iss, name, ','), municipality, ','), id, ','), code, ','), maxDelivery,
                    '\r');
            int idValue = stoi(id);
            double maxDeliveryValue = stod(maxDelivery);

            Reservoir reservoir(name, municipality, idValue, code, maxDeliveryValue);
            reservoirs.push_back(reservoir);
        }
    return reservoirs;
    }

vector<Pipe> DataReader::readPipes (const string &path) {
    //Adding an edge to the reservoir vertex
    //stream to read the Cities_Madeira file and represent as a graph
    ifstream pipesMadeira_file(path);

    //check if the file exists
    if (!pipesMadeira_file.is_open()) {
        throw runtime_error("Cities Madeira file does not exist");
    }

    string line;

    vector<Pipe> pipes;

    while (getline(pipesMadeira_file, line)) {
        istringstream iss(line);
        string sourceService, targetService, capacity, direction;
        getline(getline(getline(getline(iss, sourceService, ','), targetService, ','), capacity, ','), direction, '\r');
        // Convert capacity to double
        double capacityValue = stod(capacity);

        Pipe pipe(sourceService,targetService,capacityValue,direction);
        pipes.push_back(pipe);

    }

}






