#ifndef DA2024_PRJ1_G_04_6_MENU_H
#define DA2024_PRJ1_G_04_6_MENU_H

#include "WaterSystem.h"
#include "Script.h"
#include <iomanip>

class Menu {
public:
    bool isPortugal; // If True, we are searching in Portugal Cities, if False we are searching just in Madeira cities

    void clearScreen();

    vector<WaterInfrastructure> getInfrastructure();

    Graph<string> getGraph(const vector<WaterInfrastructure>& infrastructures);

    void mainMenu();

    void afterMenu();

    void goBackMenu();

    void drawBox(string text);

    void maximumSupply();

    void systemRealiability();

    void removedReservoir();

    void removedStation();

    void removedPipeline();

    void systemAdequacy();
};

#endif //DA2024_PRJ1_G_04_6_MENU_H
