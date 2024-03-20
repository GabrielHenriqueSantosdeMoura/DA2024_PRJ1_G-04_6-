
#include "headers/Pipe.h"
using namespace std;

Pipe::Pipe(const string& sourceService, const string& targetService, double capacity, string direction)
        : sourceService(sourceService), targetService(targetService), capacity(capacity), direction(direction) {}


string Pipe::getSourceService() const {
    return sourceService;
}

string Pipe::getTargetService() const {
    return targetService;
}

double Pipe::getCapacity() const {
    return capacity;
}

string Pipe::getDirection()const {
    return direction;
}
