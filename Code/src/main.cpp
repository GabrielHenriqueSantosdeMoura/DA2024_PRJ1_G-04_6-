#include <iostream>
#include <vector>
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"
#include "headers/WaterInfrastructure.h"
#include "headers/Script.h"
#include <string>

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

    cout << calculateMaxFlowForCity(infrastructures,"C_6") << endl;

    string stationCodeToRemove = "PS_1";
    map<string, pair<double, double>> affectedCitiesStation = checkStationImpact(stationCodeToRemove, infrastructures);
    cout << "Cities affected by removing station " << stationCodeToRemove << ":" << endl;
    cout << "City  Old Flow\tNew Flow" << endl;
    for (const auto &city : affectedCitiesStation) {
        cout << city.first << ":\t" << city.second.first << "\t\t" << city.second.second << endl;
    }

    string sourceServiceToRemove = "PS_9";
    string targetServiceToRemove = "PS_10";

    map<string, pair<double, double>> affectedCitiesPipe = checkPipelineImpact(sourceServiceToRemove, targetServiceToRemove, infrastructures);

    cout << "Cities affected by removing pipeline from " << sourceServiceToRemove << " to " << targetServiceToRemove << ":" << endl;
    cout << "City  Old Flow\tNew Flow" << endl;
    for (const auto &city : affectedCitiesPipe) {
        cout << city.first << ":\t" << city.second.first << "\t\t" << city.second.second << endl;
    }


    string reservoirCodeToRemove = "R_4";
    map<string, pair<double, double>> affectedCitiesReservoir = checkReservoirImpact(reservoirCodeToRemove, infrastructures);
    cout << "Cities affected by removing reservoir " << reservoirCodeToRemove << ":" << endl;
    cout << "City  Old Flow\tNew Flow" << endl;
    for (const auto &city : affectedCitiesReservoir) {
        cout << city.first << ":\t" << city.second.first << "\t\t" << city.second.second << endl;
    }



    return 0;
}
