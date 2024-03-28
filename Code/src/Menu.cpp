//
// Created by Gabriel on 19/03/2024.
//

#include "headers/Menu.h"
#include "headers/Script.h"

void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

vector<WaterInfrastructure> Menu::getInfrastructure(){
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

void Menu::mainMenu() {
    int input;
    cout << "+---------------+"
         << endl
         << "|   MAIN MENU   |"
         << endl
         << "+---------------+"
         << endl
         << "1. Maximum Water Supply of the Cities"
         << endl
         << "2. Water Supply Adequacy"
         << endl
         << "3. Check reliability of the system"
         << endl
         << "4. Pipeline Failure Analysis "
         << endl
         << "5. Exit"
         << endl
         << "Enter your choice: ";
    cin >> input;

    if (!(input == 1 or input == 2 or input == 3 or input == 4 or input == 5)) {
        cout << "Invalid option! please try again:" << endl
             << endl;
        mainMenu();
    }

    switch (input) {
        case 1: {
            vector<WaterInfrastructure> infrastructures = getInfrastructure();
            calculateMaxFlow(infrastructures);
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
            //(T3)
            clearScreen();
            systemRealiability();
            break;
        }
        case 4:{
            //(T3.3)
            clearScreen();
            pipelineFailure();
            break;
        }
        case 5:{
            exit(EXIT_SUCCESS);
        }
        default: {
            cout << "Invalid option! please try again:"
                 << endl;
            mainMenu();
        }

    }
}
void Menu::maximumSupply() {
    //should the list of the cities be immediately uploaded
    // with enumeration and after user choice run the function

    //Or have 1. Check the cities list -> output the list -> another Menu void() to run the Edmonds Karp function
    //2. return back to Main Menu
}
void Menu::systemAdequacy() {
    cout<<endl
        << "+---------------------------+"
        <<endl
        << "|   WATER SUPPLY ADEQUACY   |"
        << endl
        << "+---------------------------+";
}

void Menu::systemRealiability() {
    int input;

    cout<<endl
        << "+------------------------+"
        <<endl
        << "|   SYSTEM RELIABILITY   |"
        << endl
        << "+------------------------+"
        <<endl
        << "1. Water supply after removing reservoir"
        << endl
        << "2. Water supply after removing pumping station"
        << endl
        << "3. Return back to Main Menu"
        <<endl
        << "Enter your choice: ";

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
            mainMenu();
            break;
        }
        default: {
            cout << "Invalid option! please try again:"
                 << endl;
            mainMenu();
        }
    }
}
void Menu::pipelineFailure() {
    cout<<endl
        << "+----------------------+"
        <<endl
        << "|   PIPELINE FAILURE   |"
        << endl
        << "+----------------------+";
}

void Menu::removedReservoir() {
    cout<<endl
        <<"List of the reservoirs:"
        <<endl;
    //the same question as in maximumSupply
}

void Menu::removedStation() {
    cout<<endl
        <<"List of the pumping stations:"
        <<endl;
    //the same question as in removedReservoir();
}