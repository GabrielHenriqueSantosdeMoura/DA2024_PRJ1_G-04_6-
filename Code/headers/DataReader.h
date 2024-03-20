//
// Created by Gabriel on 19/03/2024.
//

#ifndef DA2024_PRJ1_G_04_6_READDATA_H
#define DA2024_PRJ1_G_04_6_READDATA_H

#include <string>
#include "headers/Graph.h"
#include "WaterSystem.h"

using namespace std;

class DataReader{
    //Graph of a watter supply system
    Graph <WaterSystem> supplySystem;

public:

    DataReader(const string &citiesMadeira, const string &pipesMadeira, const string &reservoirsMadeira ,const string & stationsMadeira);

    void readCities(const string& citiesMadeira, WaterSystem& waterSystem);

    void readPipes(const string& pipesMadeira, WaterSystem& waterSystem);

    void readReservoirs(const string& reservoirsMadeira, WaterSystem& waterSystem);


    void readPumpingStations(const string& stationsMadeira, WaterSystem& waterSystem);
};

#endif //DA2024_PRJ1_G_04_6_READDATA_H
