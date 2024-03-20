#ifndef DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#define DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#include <vector>
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include "Pipe.h"
using namespace std;

//the class will hold the instances of entity classes
//we can change to store in another data structure container
class WaterSystem {
private:
    vector<Reservoir> reservoirs;

    vector<PumpingStation> pumpingStations;

    vector<City> cities;

    vector<Pipe> pipes;
public:

    // Constructor
    WaterSystem(){}
    WaterSystem(const vector<Reservoir>& reservoirs,const vector<PumpingStation>& pumpingStations,const vector<City>& cities,const vector<Pipe>& pipes);

    // Getters
    vector<Reservoir> getReservoirs() const;

    vector<PumpingStation> getPumpingStations() const;

    vector<City> getCities() const;

    vector<Pipe> getPipes() const;

    void addCity(const City& city);

    void addReservoir(const Reservoir& reservoir);

    void addPumpingStation(const PumpingStation& pumpingStation);

    void addPipe(const Pipe& pipe);

};


#endif //DA2024_PRJ1_G_04_6__WATERSYSTEM_H
