//
// Created by Gabriel on 19/03/2024.
//

#include <iostream>
#include <vector>
#include "headers/DataReader.h"
#include "headers/WaterSystem.h"
#include "headers/Menu.h"
#include "headers/WaterInfrastructure.h"
#include "headers/Script.h"
#include <string>


void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

vector<WaterInfrastructure> Menu::getInfrastructure(){
    if (isPortugal) { //Searching in all Portugal Cities
        vector<WaterInfrastructure> cities = DataReader::readCities("Docs/Project1LargeDataSet/Cities.csv");
        vector<WaterInfrastructure> stations = DataReader::readPumpingStations("Docs/Project1LargeDataSet/Stations.csv");
        vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("Docs/Project1LargeDataSet/Reservoirs.csv");
        vector<WaterInfrastructure> pipes = DataReader::readPipes("Docs/Project1LargeDataSet/Pipes.csv");
        vector<WaterInfrastructure> infrastructures;
        infrastructures.insert(infrastructures.end(), cities.begin(), cities.end());
        infrastructures.insert(infrastructures.end(), stations.begin(), stations.end());
        infrastructures.insert(infrastructures.end(), reservoirs.begin(), reservoirs.end());
        infrastructures.insert(infrastructures.end(), pipes.begin(), pipes.end());
        return infrastructures;
    }

    else { //Searching just Madeira Cities
        vector<WaterInfrastructure> cities = DataReader::readCities("Docs/Project1DataSetSmall/Cities_Madeira.csv");
        vector<WaterInfrastructure> stations = DataReader::readPumpingStations("Docs/Project1DataSetSmall/Stations_Madeira.csv");
        vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("Docs/Project1DataSetSmall/Reservoirs_Madeira.csv");
        vector<WaterInfrastructure> pipes = DataReader::readPipes("Docs/Project1DataSetSmall/Pipes_Madeira.csv");
        vector<WaterInfrastructure> infrastructures;
        infrastructures.insert(infrastructures.end(), cities.begin(), cities.end());
        infrastructures.insert(infrastructures.end(), stations.begin(), stations.end());
        infrastructures.insert(infrastructures.end(), reservoirs.begin(), reservoirs.end());
        infrastructures.insert(infrastructures.end(), pipes.begin(), pipes.end());
        return infrastructures;
    }
}

Graph<string> Menu::getGraph(const vector<WaterInfrastructure>& infrastructures){
    Graph<string> graph;
    for (const auto &infrastructure : infrastructures) {
        switch (infrastructure.type) {
            case RESERVOIR:
                graph.addVertex(infrastructure.reservoir.getCode());
                break;
            case CITY:
                graph.addVertex(infrastructure.city.getCode());
                break;
            case PUMPINGSTATION:
                graph.addVertex(infrastructure.pumpingStation.getCode());
                break;
            case PIPE:
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
                // Assuming addEdge function takes source, target, and capacity as parameters
                break;
            default:
                break;
        }
    }
    return graph;
}

void Menu::mainMenu() {
    int input;
    drawBox("Choose your Main File");
         cout << "1. Just Madeira cities"
         << endl
         << "2. All Portugal cities"
         << endl
         << "3. Exit"
         << endl
         << "Enter your choice:";
    cin >> input;
    cout << endl;

    if (!(input == 1 or input == 2 or input == 3 )) {
        cout << "Invalid option! please try again:" << endl
             << endl;
        mainMenu();
    }

    switch (input) {
        case 1: {
            isPortugal = false;
            afterMenu();
            break;
        }
        case 2:{
            isPortugal = true;
            afterMenu();
            break;
        }
        case 3:{
            exit(EXIT_SUCCESS);
        }
    }
}

void Menu::afterMenu() {
    int input;
    drawBox("MAIN MENU");
    cout << "1. Maximum Water Supply of the Cities"
         << endl
         << "2. Water Supply Adequacy"
         << endl
         << "3. Metrics before/after balacing the network"
         << endl
         << "4. Check reliability of the system"
         << endl
         << "5. Exit"
         << endl
         << "Enter your choice:";
    cin >> input;
    cout << endl;

    if (!(input == 1 or input == 2 or input == 3 or input == 4 or input == 5)) {
        cout << "Invalid option! please try again:" << endl
             << endl;
        afterMenu();
    }

    switch (input) {
        case 1: {
            maximumSupply();
            break;
        }
        case 2:{
            //(T2.2) List the city(code,value) value = deficit of the water,cities that
            //cannot be supplied by the desired water rate level
            systemAdequacy();
            break;
        }
        case 3:{
            vector<WaterInfrastructure> infrastructures = getInfrastructure();
            Graph<string> graph = getGraph(infrastructures);
            balanceFlow(&graph);
            goBackMenu();
            break;
        }
        case 4:{
            //(T3)
            systemRealiability();
            break;
        }
        case 5:{
            exit(EXIT_SUCCESS);

        }
    }
}

void Menu::goBackMenu() {
    int input;
    cout << endl
    << "+---------------------+"
    << endl
    << "1. Go back to main menu"
    << endl
    << "2. Exit"
    << endl
    << "Enter your choice:";
    cin >> input;
    if (!(input == 1 | input == 2)){
        cout << "Invalid option! please try again:" << endl
             << endl;
        goBackMenu();
    }
    switch (input) {
        case 1:{
            mainMenu();
            break;
        }
        case 2:{
            exit(EXIT_SUCCESS);
            break;
        }
    }
}

void Menu::maximumSupply() {
    vector<WaterInfrastructure> infrastructures = getInfrastructure();
    drawBox("MAXIMUM FLOW");
    calculateMaxFlowAllCities(infrastructures);
    goBackMenu();
}

void Menu::systemRealiability() {
    int input;
    drawBox("SYSTEM REABILITY");
    cout<<endl
        << "1. Water supply after removing reservoir"
        << endl
        << "2. Water supply after removing pumping station"
        << endl
        << "3. Water supply after removing pipeline"
        << endl
        << "4. Return back to Main Menu"
        << endl
        << "Enter your choice:";

    cin>> input;

    switch(input){
        case 1: {
            //(T3.1)
            removedReservoir();
            break;
        }
        case 2:{
            //(T3.2)
            removedStation();
            break;
        }
        case 3:{
            removedPipeline();
            break;
        }
        case 4:{
            mainMenu();
            break;
        }
        default: {
            cout << "Invalid option! please try again:"
                 << endl;
            systemRealiability();
        }
    }
}

void Menu::systemAdequacy() {
    vector<WaterInfrastructure> infrastructures = getInfrastructure();

    // Find deficit cities
    map<string, double> deficitCities = findDeficitCities(infrastructures);

    // Check if there are any deficit cities
    if (deficitCities.empty()) {
        drawBox("NO DEFICIT CITIES FOUND");
    } else {
        drawBox("DEFICIT CITIES");
        cout << "City\tDeficit" << endl;
        for (const auto& city : deficitCities) {
            cout << city.first << "\t" << city.second << endl;
        }
    }
    goBackMenu();
}


void Menu::removedReservoir() {
    drawBox("REMOVE RESERVOIR");
    vector<WaterInfrastructure> infrastructures = getInfrastructure();
    string reservoirCodeToRemove;
    if (isPortugal){
        cout << "To remove a reservoir choose it like R_(1...24)"
             << endl
             << "Enter your choice:";
    }
    else{
        cout << "To remove a reservoir choose it like R_(1...4)"
             << endl
             << "Enter your choice:";
    }
    cin >> reservoirCodeToRemove;
    map<string, pair<double, double>> affectedCitiesReservoir = checkReservoirImpact(reservoirCodeToRemove, infrastructures);
    if (affectedCitiesReservoir.find("ReservoirNotFound") != affectedCitiesReservoir.end()) {
        cout << "The reservoir " << reservoirCodeToRemove << " does not exist. Try again" << endl;
        removedReservoir();
    }
    else {
        cout << "Cities affected by removing reservoir " << reservoirCodeToRemove << ":" << endl;
        cout << "City  Old Flow\tNew Flow" << endl;
        for (const auto &city: affectedCitiesReservoir) {
            cout << city.first << ":\t" << city.second.first << "\t\t" << city.second.second << endl;
        }
        goBackMenu();
    }
}

void Menu::removedStation() {
    drawBox("REMOVE PUMPING STATION");
    vector<WaterInfrastructure> infrastructures = getInfrastructure();
    string stationCodeToRemove;
    if (isPortugal){
        cout << "To remove a pumping station choose it like PS_(1...81)"
             << endl
             << "Enter your choice:";
    }
    else {
        cout << "To remove a pumping station choose it like PS_(1...12)"
             << endl
             << "Enter your choice:";
    }
    cin >> stationCodeToRemove;
    map<string, pair<double, double>> affectedCitiesStation = checkStationImpact(stationCodeToRemove, infrastructures);
    if (affectedCitiesStation.find("StationNotFound") != affectedCitiesStation.end()) {
        cout << "The pumping station " << stationCodeToRemove << " does not exist. Try again" << endl;
        removedStation();
    }
    else {
        cout << "Cities affected by removing station " << stationCodeToRemove << ":" << endl;
        cout << "City  Old Flow\tNew Flow" << endl;
        for (const auto &city: affectedCitiesStation) {
            cout << city.first << ":\t" << city.second.first << "\t\t" << city.second.second << endl;
        }
        goBackMenu();
    }
}

void Menu::removedPipeline() {
    drawBox("REMOVE PIPELINE");
    vector<WaterInfrastructure> infrastructures = getInfrastructure();
    string sourceServiceToRemove;
    string targetServiceToRemove;
    cout << "Choose your source service to remove:";
    cin >> sourceServiceToRemove;
    cout << "Now choose your target service to remove the pipe:";
    cin >> targetServiceToRemove;
    map<string, pair<double, double>> affectedCitiesPipe = checkPipelineImpact(sourceServiceToRemove, targetServiceToRemove, infrastructures);
    if (affectedCitiesPipe.find("PipeNotFound") != affectedCitiesPipe.end()) {
        cout << "The pipeline from " << sourceServiceToRemove << " to " << targetServiceToRemove << " does not exist. Try again" << endl;
        removedPipeline();
    } else if (affectedCitiesPipe.empty()) {
        cout << "No cities were affected by removing the pipeline." << endl;
    } else {
        cout << "Cities affected by removing the pipeline from " << sourceServiceToRemove << " to " << targetServiceToRemove << ":" << endl;
        cout << "City  Old Flow\tNew Flow" << endl;
        for (const auto &city: affectedCitiesPipe) {
            cout << city.first << ":\t" << city.second.first << "\t\t" << city.second.second << endl;
        }
        goBackMenu();
    }
}

void Menu::drawBox(string text) {
    int width = text.length() + 4;
    string horizontalLine(width, '-');
    cout << "   +" << horizontalLine << "+" << endl;
    cout << "   |  " << text << "  |" << endl;
    cout << "   +" << horizontalLine << "+" << endl;
}