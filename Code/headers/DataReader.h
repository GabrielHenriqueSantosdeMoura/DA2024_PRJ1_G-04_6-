#include <vector>
#include "City.h"
#include "PumpingStation.h"
#include "Pipe.h"
#include "Reservoir.h"

using namespace std;

class DataReader{
public:
    DataReader(const string& reservoirsMadeira,const string& pipesMadeira,const string& citiesMadeira, const string& stationsMadeira);
    vector <City> readCities (const string &path);
    vector <PumpingStation> readPumpingStations (const string &path);
    vector <Pipe> readPipes (const string &path);
    vector <Reservoir> readReservoirs (const string &path);
}

