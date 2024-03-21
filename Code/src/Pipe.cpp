
#include "headers/Pipe.h"
using namespace std;

Pipe::Pipe(const string& sourceService, const string& targetService, double capacity)
        : sourceService(sourceService), targetService(targetService), capacity(capacity){}


string Pipe::getSourceService() const {
    return sourceService;
}

string Pipe::getTargetService() const {
    return targetService;
}

double Pipe::getCapacity() const {
    return capacity;
}

