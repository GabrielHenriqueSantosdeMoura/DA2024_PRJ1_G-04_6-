#ifndef DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
#define DA2024_PRJ1_G_04_6__PUMPINGSTATION_H

#include <string>

using namespace std;

/**
 * @brief Represents a pumping station in a water infrastructure system.
 */
class PumpingStation {
private:
    /**< The ID of the pumping station. */
    int id;

    /**< The code of the pumping station. */
    string code;

public:

    /**< Default constructor. */
    PumpingStation() = default;
    /**
     * @brief Constructs a new PumpingStation object with provided attributes.
     * @param id The ID of the pumping station.
     * @param code The code of the pumping station.
     */
    PumpingStation(int id, const string &code);

    /**
     * @brief Gets the code of the pumping station.
     * @return The code of the pumping station.
     */
    string getCode() const;
    /**
     * @brief Prints the station ID (code) for debugging purposes.
     */
    void print() const;
};

#endif // DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
