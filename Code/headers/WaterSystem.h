#ifndef DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#define DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#include <vector>
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include "Pipe.h"
#include "Graph.h"

using namespace std;
#include <unordered_map>

template<class T>
class WaterSystem {
private:
    Graph<T> supplySystem;
    unordered_map<string, Vertex<T>*> verticesMap;
    unordered_map<string, Edge<T>*> edgesMap;
public:
    // Method to add a vertex to the graph and hash table
    bool addVertex(const T& info) {
        if (!verticesMap.count(info.getCode())) {
            verticesMap[info.getCode()] = supplySystem.addVertex(info);
            return true;
        }
        return false;
    }

    // Method to add an edge to the graph and hash table
    bool addEdge(const T& edge) {



    }
    /*auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;*/
    // Method to retrieve a vertex by its code
    Vertex<T>* getVertex(const std::string& code) {
        if (verticesMap.count(code))
            return verticesMap[code];
        return nullptr; // Vertex not found
    }

    // Method to retrieve an edge by the codes of its source and destination vertices
    Edge<T>* getEdge(const std::string& sourceCode, const std::string& destCode) {
        std::string edgeKey = sourceCode + destCode;
        if (edgesMap.count(edgeKey))
            return edgesMap[edgeKey];
        return nullptr; // Edge not found
    }

};


#endif //DA2024_PRJ1_G_04_6__WATERSYSTEM_H
