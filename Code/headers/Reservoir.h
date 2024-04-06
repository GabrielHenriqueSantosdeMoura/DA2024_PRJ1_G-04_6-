#ifndef DA2024_PRJ1_G_04_6__RESERVOIR_H
#define DA2024_PRJ1_G_04_6__RESERVOIR_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Class representing a reservoir.
 */
class Reservoir {

private:
    /**< Name of the reservoir. */
    string name;

    /**< Municipality of the reservoir. */
    string municipality;

    /**< ID of the reservoir. */
    int id;

    /**< Code of the reservoir. */
    string code;

    /**< Maximum delivery capacity of the reservoir. */
    double maxDelivery;

public:
    /**
     * @brief Default constructor.
     */
    Reservoir() = default;

    /**
     * @brief Constructs a reservoir with provided attributes.
     * @param name Name of the reservoir.
     * @param municipality Municipality of the reservoir.
     * @param id ID of the reservoir.
     * @param code Code of the reservoir.
     * @param maxDelivery Maximum delivery capacity of the reservoir.
     */
    Reservoir(const string& name, const string& municipality, int id, const string& code, double maxDelivery);

    /**< Getter for the code of the reservoir. */
    string getCode() const;

    /**< Getter for the maximum delivery capacity of the reservoir. */
    double getMaxDelivery() const;

    /**
     * @brief Method for printing reservoir information.
     */
    void print() const {}
};

#endif // DA2024_PRJ1_G_04_6__RESERVOIR_H
