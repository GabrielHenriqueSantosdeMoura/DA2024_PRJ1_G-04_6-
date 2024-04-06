#ifndef DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H
#define DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H

#include "Pipe.h"
#include "City.h"
#include "PumpingStation.h"
#include "Reservoir.h"

/**
 * @brief Enumerates the types of water infrastructure elements.
 */
enum Watertype {
    /**< City type. */
    CITY,
    /**< Pumping station type. */
    PUMPINGSTATION,
    /**< Pipe type. */
    PIPE,
    /**< Reservoir type. */
    RESERVOIR
};

/**
 * @brief Represents a water infrastructure object, such as a city, pumping station, pipe, or reservoir.
 */
class WaterInfrastructure {
public:
    /**< City information. */
    City city;

    /**< Pumping station information. */
    PumpingStation pumpingStation;

    /**< Pipe information. */
    Pipe pipe;

    /**< Reservoir information. */
    Reservoir reservoir;

    /**< Type of water infrastructure element. */
    Watertype type;

    /**
     * @brief Constructs a water infrastructure element representing a city.
     * @param name Name of the city.
     * @param id ID of the city.
     * @param code Code of the city.
     * @param demand Water demand of the city.
     * @param population Population of the city.
     */
    WaterInfrastructure(const string &name, int id, const string &code, double demand, const string &population)
            : city(name, id, code, demand, population), type(CITY) {}

    /**
     * @brief Constructs a water infrastructure element representing a pipe.
     * @param sourceService Source service of the pipe.
     * @param targetService Target service of the pipe.
     * @param capacity Capacity of the pipe.
     * @param direction Direction of the pipe.
     */
    WaterInfrastructure(const string &sourceService, const string &targetService, double capacity, bool direction)
            : pipe(sourceService, targetService, capacity, direction), type(PIPE) {}

    /**
     * @brief Constructs a water infrastructure element representing a pumping station.
     * @param id ID of the pumping station.
     * @param code Code of the pumping station.
     */
    WaterInfrastructure(int id, const string &code)
            : pumpingStation(id, code), type(PUMPINGSTATION) {}

    /**
     * @brief Constructs a water infrastructure element representing a reservoir.
     * @param name Name of the reservoir.
     * @param municipality Municipality of the reservoir.
     * @param id ID of the reservoir.
     * @param code Code of the reservoir.
     * @param maxDelivery Maximum delivery of the reservoir.
     */
    WaterInfrastructure(const string &name, const string &municipality, int id, const string &code, double maxDelivery)
            : reservoir(name, municipality, id, code, maxDelivery), type(RESERVOIR) {}

    /**
     * @brief Overloaded equality operator to compare water infrastructure objects.
     * @param other Water infrastructure element to compare with.
     * @return True if the elements are equal, false otherwise.
     */
    bool operator==(const WaterInfrastructure &other) const {
        if (type != other.type) {
            return false;
        }
        switch (type) {
            case CITY:
                return city.getCode() == other.city.getCode();
            case RESERVOIR:
                return reservoir.getCode() == other.reservoir.getCode();
            case PUMPINGSTATION:
                return pumpingStation.getCode() == other.pumpingStation.getCode();
            case PIPE:
                return pipe.getSourceService() == other.pipe.getSourceService() &&
                       pipe.getTargetService() == other.pipe.getTargetService();
        }
        return false;
    }

    /**
     * @brief Prints the information of the water infrastructure element.
     */
    void print() {
        switch (type) {
            case CITY:
                city.print();
                break;
            case RESERVOIR:
                reservoir.print();
                break;
            case PUMPINGSTATION:
                pumpingStation.print();
                break;
            case PIPE:
                pipe.print();
                break;
        }
    }
};

#endif //DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H
