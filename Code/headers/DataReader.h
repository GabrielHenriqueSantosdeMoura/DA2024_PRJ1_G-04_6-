#include <vector>
#include "City.h"
#include "PumpingStation.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "WaterInfrastructure.h"

using namespace std;

namespace DataReader{
    vector <WaterInfrastructure> readCities (const string &path);
    vector <WaterInfrastructure> readPumpingStations (const string &path);
    vector <WaterInfrastructure> readPipes (const string &path);
    vector <WaterInfrastructure> readReservoirs (const string &path);
}

