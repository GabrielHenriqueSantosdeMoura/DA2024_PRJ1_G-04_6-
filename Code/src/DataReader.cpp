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
    //Create an instance of Water System class
    WaterSystem waterSystem;
    //class to read the data and represent as a graph
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
