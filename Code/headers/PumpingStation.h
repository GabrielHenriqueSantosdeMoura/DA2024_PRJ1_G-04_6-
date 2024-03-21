
#ifndef DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
#define DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
#include <string>
#include "Pipe.h"


using namespace std;

class PumpingStation  {
private:

    int id = 0;

    string code;

public:
    // constructors

    PumpingStation(int id, const string &code);
    PumpingStation() = default;

    // getters
    int getId() const;

    string getCode() const;

    //method for checking the data, could be deleted
    void print() const{
        cout<<"station id: "<<getCode()<<'\n';
    }

};

#endif DA2024_PRJ1_G_04_6__PUMPINGSTATION_H
