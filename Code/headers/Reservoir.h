
#ifndef DA2024_PRJ1_G_04_6__RESERVOIR_H
#define DA2024_PRJ1_G_04_6__RESERVOIR_H
#include <string>
using namespace std;

class Reservoir {

private:
    string name;

    string municipality;

    int id;

    string code;

    double maxDelivery;

public:

    //constructors
    Reservoir(const string &id);

    Reservoir(const string& name, const string& municipality, int id, const string& code, double maxDelivery);

    //getters
    string getName() const;

    string getMunicipality() const;

    int getId() const;

    string getCode() const;

    double getMaxDelivery() const;

    //setters

};


#endif DA2024_PRJ1_G_04_6__RESERVOIR_H
