//
// Created by CTW02617-admin on 3/19/2024.
//


#ifndef DA2024_PRJ1_G_04_6__CITY_H
#define DA2024_PRJ1_G_04_6__CITY_H
#include <string>
using namespace std;

class City {
private:
    string name;

    int id;

    string code;

    double demand;

    int population;

public:

    // constructors
    City(int id);

    City(int id, const string& name, const string& code, double demand, int population);

    // getters
    string getName() const;

    int getId() const;

    string getCode() const;

    double getDemand() const;

    int getPopulation() const;

    //setters
};


#endif //DA2024_PRJ1_G_04_6__CITY_H
