
#ifndef DA2024_PRJ1_G_04_6__PIPE_H
#define DA2024_PRJ1_G_04_6__PIPE_H
#include <string>
#include <iostream>


using namespace std;

class Pipe{

private:
    string sourceService;

    string targetService;

    double capacity;


public:
    // Constructors
    Pipe(const string& sourceService, const string& targetService, double capacity);
    Pipe() = default;

    // Getters
    string getSourceService() const;

    string getTargetService() const;

    double getCapacity() const;

    string getDirection() const;

    //method for checking the data, could be deleted
    void print() const{
        cout<<"pipe: "<<getCapacity()<<'\n';
    }


};


#endif DA2024_PRJ1_G_04_6__PIPE_H
