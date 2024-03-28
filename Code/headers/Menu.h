#ifndef DA2024_PRJ1_G_04_6_MENU_H
#define DA2024_PRJ1_G_04_6_MENU_H

#include "WaterSystem.h"
#include "Script.h"
#include <iomanip>

class Menu {
public:
    void clearScreen();

    vector<WaterInfrastructure> getInfrastructure();

    void mainMenu();

    void goBackMenu();

    void maximumSupply();

    void systemAdequacy();

    void systemRealiability();

    void pipelineFailure();

    void removedReservoir();

    void removedStation();
};

#endif //DA2024_PRJ1_G_04_6_MENU_H
