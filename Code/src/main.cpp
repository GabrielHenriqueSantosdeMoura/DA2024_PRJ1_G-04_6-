//
// Created by CTW02617-admin on 3/19/2024.
//
#include "iostream"
#include "headers/Menu.h"
#include "headers/DataReader.h"
#include "headers/GraphFactory.h"

int main () {
    //read the data
    /*
    vector<City> cities = DataReader::readCities("../Docs/Project1DataSetSmall/Cities_Madeira.csv");
    vector<Pipe> pipes = DataReader::readPipes("../Docs/Project1DataSetSmall/Pipes_madeira");
    vector<PumpingStation> stations = DataReader::readPumpingStations("../Docs/Project1DataSetSmall/StationsMadeira");
    vector<Reservoir> reservoirs = DataReader::readReservoirs("../Docs/Project1DataSetSmall/Reservoirs_Madeira");

    //Initialise graph
    GraphFactory<City> cityVertexes;
    cityVertexes.addVerticesFromVector(cities);

    //GraphFactory<PumpingStation> stationVertexes;
    //stationVertexes.addVerticesFromVector(stations);

*/
    DataReader dataReaderCity();
    DataReader dataReaderStation();

    GraphFactory<City> cityVertexes;
    cityVertexes.addVerticesFromVector(dataReaderCity().readCities("../Docs/Project1DataSetSmall/Cities_Madeira.csv"));

    GraphFactory<Pipe> pipesEdges;
    pipesEdges.addEdgeFromVector(dataReaderStation().readPipes("../Docs/Project1DataSetSmall/Pipes_madeira"));



};