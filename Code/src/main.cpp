//
// Created by CTW02617-admin on 3/19/2024.
//
#include "iostream"
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"
#include "headers/WaterInfrastructure.h"

int main () {
    //read the data
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

};