
#ifndef DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
#define DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
#include <string>
using namespace std;

class PumpingStation {
private:

    int id;

    string code;

public:
    // constructors
    PumpingStation(int id);

    PumpingStation(int id, const string& code);

    // getters
    int getId() const;

    string getCode() const;

    //setters

};

#endif DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
