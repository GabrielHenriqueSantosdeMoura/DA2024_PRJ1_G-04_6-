
#ifndef DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H
#define DA2024_PRJ1_G_04_6__WATERINFRASTRUCTURE_H
#include "headers/Pipe.h"
#include "headers/City.h"
#include "headers/PumpingStation.h"
#include "headers/Reservoir.h"
enum Watertype{
    CITY,
    PUMPINGSTATION,
    PIPE,
    RESERVOIR
};

class  WaterInfrastructure {
public:
    City city;
    PumpingStation pumpingStation;
    Pipe pipe;
    Reservoir reservoir;
    Watertype type;

    WaterInfrastructure(const string &name, int id, const string &code, double demand, const string &population)
    :city(name, id, code,demand,population){
        type = CITY ;
    }

    WaterInfrastructure(const string &sourceService, const string &targetService, double capacity)
    : pipe(sourceService,targetService,capacity){
        type = PIPE;
    }

    WaterInfrastructure(int id, const string &code)
    : pumpingStation(id, code){
        type = PUMPINGSTATION;
    }

    WaterInfrastructure(const string &name, const string &municipality, int id, const string &code, double maxDelivery)
    : reservoir(name, municipality,id,code, maxDelivery){
        type = RESERVOIR;
    }
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

