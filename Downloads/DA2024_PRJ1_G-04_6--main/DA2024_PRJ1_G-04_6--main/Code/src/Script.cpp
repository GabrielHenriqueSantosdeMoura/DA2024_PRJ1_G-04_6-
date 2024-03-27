

#include <vector>
#include "headers/Script.h"
#include "headers/WaterInfrastructure.h"
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"

void Script:: run(){
    WaterSystem<WaterInfrastructure> waterSystem;

    vector<WaterInfrastructure> cities = DataReader::readCities("Docs/Project1LargeDataSet/Cities.csv");
    vector<WaterInfrastructure> stations = DataReader::readPumpingStations("Docs/Project1LargeDataSet/Stations.csv");
    vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("Docs/Project1LargeDataSet/Reservoirs.csv");
    vector<WaterInfrastructure> pipes = DataReader::readPipes("Docs/Project1LargeDataSet/Pipes.csv");

    waterSystem.addVertexFromVector(cities);
    waterSystem.addVertexFromVector(reservoirs);
    waterSystem.addVertexFromVector(stations);
    waterSystem.addEdgeFromVector(pipes);

    waterSystem.print();
}