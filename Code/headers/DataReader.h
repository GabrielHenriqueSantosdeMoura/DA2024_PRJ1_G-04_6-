#include <vector>
#include "City.h"
#include "PumpingStation.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "WaterInfrastructure.h"

using namespace std;

//I created a namespace that holds the functions needed to read the data from csv files, could be places to the Script.cpp
namespace DataReader{
    vector <WaterInfrastructure> readCities (const string &path);
    vector <WaterInfrastructure> readPumpingStations (const string &path);
    vector <WaterInfrastructure> readPipes (const string &path);
    vector <WaterInfrastructure> readReservoirs (const string &path);
}

