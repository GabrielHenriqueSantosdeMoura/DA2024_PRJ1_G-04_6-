#ifndef DA2024_PRJ1_G_04_6__CITY_H
#define DA2024_PRJ1_G_04_6__CITY_H

#include <string>
#include <iostream>
using namespace std;

/**
 * @brief Represents a city in the water supply network.
 */
class City {
private:
    /**< The name of the city. */
    string name;

    /**< The unique identifier of the city. */
    int id;

    /**< The code of the city. */
    string code;

    /**< The rate demand or need of the city in m3/sec. */
    double demand;

    /**< The total population of the city. */
    string population;

public:
    /**
     * @brief Default constructor for the City class.
     */
    City() = default;

    /**
     * @brief Constructor with parameters for the City class.
     * @param name The name of the city.
     * @param id The unique identifier of the city.
     * @param code The code of the city.
     * @param demand The rate demand or need of the city in m3/sec.
     * @param population The total population of the city.
     */
    City(const string& name, int id, const string& code, double demand, const string& population);

    /**
     * @brief Get the name of the city.
     * @return The name of the city.
     */
    string getName() const;

    /**
     * @brief Get the unique identifier of the city.
     * @return The unique identifier of the city.
     */
    int getId() const;

    /**
     * @brief Get the code of the city.
     * @return The code of the city.
     */
    string getCode() const;

    /**
     * @brief Get the rate demand or need of the city.
     * @return The rate demand or need of the city in m3/sec.
     */
    double getDemand() const;

    /**
     * @brief Get the total population of the city.
     * @return The total population of the city.
     */
    string getPopulation() const;

    /**
     * @brief Print code of the the city.
     */
    void print() const {}
};

#endif // DA2024_PRJ1_G_04_6__CITY_H
