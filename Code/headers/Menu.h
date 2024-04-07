#ifndef DA2024_PRJ1_G_04_6_MENU_H
#define DA2024_PRJ1_G_04_6_MENU_H

#include "WaterSystem.h"
#include "Script.h"
#include <iomanip>

/**
 * @brief Represents a user interface of the system.
 */
class Menu {
public:
    /**
     * @brief Flag indicating whether the search is performed in Portugal cities (true) or just in Madeira cities (false).
     */
    bool isPortugal;

    /**
     * @brief Clears the console screen.
     */
    void clearScreen();

    /**
     * @brief Retrieves a vector containing information about water infrastructures.
     * @return Vector containing WaterInfrastructure objects.
     */
    vector<WaterInfrastructure> getInfrastructure();

    /**
     * @brief Constructs a graph based on the provided water infrastructure data.
     * @param infrastructures Vector containing water infrastructure data.
     * @return Graph constructed from the provided data.
     */
    Graph<string> getGraph(const vector<WaterInfrastructure>& infrastructures);

    /**
     * @brief Displays the main menu.
     */
    void mainMenu();

    /**
     * @brief Displays the menu after an action has been performed.
     */
    void afterMenu();

    /**
     * @brief Displays the "go back" menu.
     */
    void goBackMenu();

    /**
     * @brief Draws a box around the specified text.
     * @param text The text to be displayed within the box.
     */
    void drawBox(string text);

    /**
     * @brief Calculates and displays the maximum supply.
     */
    void maximumSupply();

    /**
     * @brief Calculates and displays the system reliability.
     */
    void systemRealiability();

    /**
     * @brief Displays the menu for removing a reservoir.
     */
    void removedReservoir();

    /**
     * @brief Displays the menu for removing a station.
     */
    void removedStation();

    /**
     * @brief Displays the menu for removing a pipeline.
     */
    void removedPipeline();

    /**
     * @brief Calculates and displays the system adequacy.
     */
    void systemAdequacy();
};

#endif //DA2024_PRJ1_G_04_6_MENU_H
