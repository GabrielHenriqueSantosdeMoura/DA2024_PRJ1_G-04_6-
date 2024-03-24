#include <iostream>
#include <vector>
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"
#include "headers/WaterInfrastructure.h"
#include "headers/Script.h"

int main() {
    // Read the data
    vector<WaterInfrastructure> cities = DataReader::readCities("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Cities.csv");
    vector<WaterInfrastructure> stations = DataReader::readPumpingStations("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Stations.csv");
    vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Reservoirs.csv");
    vector<WaterInfrastructure> pipes = DataReader::readPipes("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Pipes.csv");

    vector<WaterInfrastructure> infrastructures;
    infrastructures.insert(infrastructures.end(), cities.begin(), cities.end());
    infrastructures.insert(infrastructures.end(), stations.begin(), stations.end());
    infrastructures.insert(infrastructures.end(), reservoirs.begin(), reservoirs.end());
    infrastructures.insert(infrastructures.end(), pipes.begin(), pipes.end());

    calculateMaxFlow(infrastructures);



    return 0;
}
