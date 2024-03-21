
#ifndef DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H
#define DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H
#include "headers/Pipe.h"
#include "headers/City.h"
#include "headers/PumpingStation.h"
#include "headers/Reservoir.h"
//enum types to identify the type of the objects of the classes which general WaterInfrastructure class contains
enum Watertype{
    CITY,
    PUMPINGSTATION,
    PIPE,
    RESERVOIR
};

//class created by composition of the entity classes
//The Graph<T> can have just one data type <T> for edges and vertexes
//so class holds the classes in one general
class  WaterInfrastructure {
public:
    //instance of the City class
    City city;
    //instance of the PumpingStation class
    PumpingStation pumpingStation;
    //instance of the Pipe class
    Pipe pipe;
    //instance of the Reservoir class
    Reservoir reservoir;
    //instance of enum
    Watertype type;

    //constructor for a City class
    WaterInfrastructure(const string &name, int id, const string &code, double demand, const string &population)
    :city(name, id, code,demand,population){
        type = CITY ;
    }

    //constructor for a Pipe class
    WaterInfrastructure(const string &sourceService, const string &targetService, double capacity)
    : pipe(sourceService,targetService,capacity){
        type = PIPE;
    }

    //constructor for a PumpingStation class
    WaterInfrastructure(int id, const string &code)
    : pumpingStation(id, code){
        type = PUMPINGSTATION;
    }

    //constructor for a Reservoir class
    WaterInfrastructure(const string &name, const string &municipality, int id, const string &code, double maxDelivery)
    : reservoir(name, municipality,id,code, maxDelivery){
        type = RESERVOIR;
    }

    //operator overload
    bool operator == (const WaterInfrastructure& other ) const {
        if (type != other.type ){
            return false;
        }
        switch ( type) {
            case CITY:
                return city.getCode() == other.city.getCode();
            case RESERVOIR:
                return reservoir.getCode() == other.reservoir.getCode();
            case PUMPINGSTATION:
                return pumpingStation.getCode() == other.pumpingStation.getCode();
            case PIPE:
                return pipe.getSourceService() == other.pipe.getSourceService() && pipe.getTargetService() == other.pipe.getTargetService();
        }
    }

    //print method to check the consistency of the data , could be delted as well
    void print () {
        switch ( type) {
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

