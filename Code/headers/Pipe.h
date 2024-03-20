
#ifndef DA2024_PRJ1_G_04_6__PIPE_H
#define DA2024_PRJ1_G_04_6__PIPE_H
#include <string>
using namespace std;

class Pipe {

private:
    string sourceService;

    string targetService;

    double capacity;

    string direction;

public:
    // Constructors
    Pipe(const string& sourceService, const string& targetService, double capacity, string direction);

    // Getters
    string getSourceService() const;

    string getTargetService() const;

    double getCapacity() const;

    string getDirection() const;



};


#endif DA2024_PRJ1_G_04_6__PIPE_H
