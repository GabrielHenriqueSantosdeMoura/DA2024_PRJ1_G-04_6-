#ifndef DA2024_PRJ1_G_04_6__GRAPHFACTORY_H
#define DA2024_PRJ1_G_04_6__GRAPHFACTORY_H

#include "WaterSystem.h"

template<class T>
class GraphFactory {
private:
    WaterSystem<T> waterSystem;

public:
    void addVerticesFromVector(const vector<T>& vertices) {
        for (const T& vertex : vertices) {
            waterSystem.addVertex(vertex);
        }
    }
    void addEdgeFromVector(const vector<T>& edges){
        for (const T& edge : edges){
            waterSystem.addEdge(edge);
        }
    }
};

#endif //DA2024_PRJ1_G_04_6__GRAPHFACTORY_H
