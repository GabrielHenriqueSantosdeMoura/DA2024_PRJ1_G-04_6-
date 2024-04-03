#include <iostream>
#include <vector>
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"
#include "headers/WaterInfrastructure.h"
#include "headers/Script.h"

int main() {

//    vector<WaterInfrastructure> cities = DataReader::readCities("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Cities.csv");
//    vector<WaterInfrastructure> stations = DataReader::readPumpingStations("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Stations.csv");
//    vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Reservoirs.csv");
//    vector<WaterInfrastructure> pipes = DataReader::readPipes("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1LargeDataSet/Pipes.csv");

    vector<WaterInfrastructure> cities = DataReader::readCities("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Cities_Madeira.csv");
    vector<WaterInfrastructure> stations = DataReader::readPumpingStations("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Stations_Madeira.csv");
    vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Reservoirs_Madeira.csv");
    vector<WaterInfrastructure> pipes = DataReader::readPipes("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Pipes_Madeira.csv");

    vector<WaterInfrastructure> infrastructures;
    infrastructures.insert(infrastructures.end(), cities.begin(), cities.end());
    infrastructures.insert(infrastructures.end(), stations.begin(), stations.end());
    infrastructures.insert(infrastructures.end(), reservoirs.begin(), reservoirs.end());
    infrastructures.insert(infrastructures.end(), pipes.begin(), pipes.end());

    calculateMaxFlowAllCities(infrastructures);

    cout << calculateMaxFlowForCity(infrastructures,"C_5");

    string stationCodeToRemove = "PS_1";
    map<string, double> affectedCitiesStation = checkStationImpact(stationCodeToRemove, infrastructures);

    cout << "Cities affected by removing pumping station " << stationCodeToRemove << ":" << endl;
    for (const auto &city : affectedCitiesStation) {
        cout << "City: " << city.first << ", Deficit: " << city.second << endl;
    }

    string sourceServiceToTest = "PS_9";
    string targetServiceToTest = "PS_10";
    map<string, double> affectedCitiesPipe = checkPipelineImpact(sourceServiceToTest, targetServiceToTest, infrastructures);

    // Output affected cities and their deficit
    cout << "Cities affected by pipeline failure from " << sourceServiceToTest << " to " << targetServiceToTest << ":" << endl;
    for (const auto &city : affectedCitiesPipe) {
        cout << "City: " << city.first << ", Deficit: " << city.second << endl;
    }


    return 0;
}
