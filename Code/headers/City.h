
#ifndef DA2024_PRJ1_G_04_6__CITY_H
#define DA2024_PRJ1_G_04_6__CITY_H
#include <string>
#include <iostream>


using namespace std;

class City{
private:
    string name;

    int id;

    string code;

    double demand;

    string population;

public:
    City() = default;

    City(const string& name, int id, const string& code, double demand, const string& population);
    // getters
    string getName() const;

    int getId() const;

    string getCode() const;

    double getDemand() const;

    string getPopulation() const;

    void print() const{
        cout<<"city name : "<<getCode()<<'\n';
    }
    //setters
};


#endif //DA2024_PRJ1_G_04_6__CITY_H
