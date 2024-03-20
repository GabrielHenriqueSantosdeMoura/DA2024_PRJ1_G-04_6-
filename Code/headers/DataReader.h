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

}

#endif //DA2024_PRJ1_G_04_6_READDATA_H
