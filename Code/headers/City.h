
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

    basic_string<char> population;

public:

    City(const string& name, int id, const string& code, double demand, const string& population);
    // getters
    string getName() const;

    int getId() const;

    string getCode() const;

    double getDemand() const;

    int getPopulation() const;

    bool operator==(const City& other) const {
        // Define your comparison logic here
        return (this->name == other.name && this->id == other.id && this->code == other.code
        && this->demand == other.demand && this->population == other.population);
    }
    //setters
};


#endif //DA2024_PRJ1_G_04_6__CITY_H
