#ifndef DATA_READER_H
#define DATA_READER_H

#include <vector>
#include <string>
#include "City.h"
#include "PumpingStation.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "WaterInfrastructure.h"

using namespace std;

/**
 * @brief Namespace containing functions for reading data from CSV files.
 */
namespace DataReader {
    /**
     * @brief Reads information about cities from a file.
     * @param path The path to the file containing city data.
     * @return A vector of WaterInfrastructure objects representing cities.
     */
    vector<WaterInfrastructure> readCities(const string& path);

    /**
     * @brief Reads information about pumping stations from a file.
     * @param path The path to the file containing pumping station data.
     * @return A vector of WaterInfrastructure objects representing pumping stations.
     */
    vector<WaterInfrastructure> readPumpingStations(const string& path);

    /**
     * @brief Reads information about pipes from a file.
     * @param path The path to the file containing pipe data.
     * @return A vector of WaterInfrastructure objects representing pipes.
     */
    vector<WaterInfrastructure> readPipes(const string& path);

    /**
     * @brief Reads information about reservoirs from a file.
     * @param path The path to the file containing reservoir data.
     * @return A vector of WaterInfrastructure objects representing reservoirs.
     */
    vector<WaterInfrastructure> readReservoirs(const string& path);
}

#endif // DATA_READER_H
