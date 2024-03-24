#ifndef DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#define DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#include <vector>
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include "Pipe.h"
#include "Graph.h"
#include "WaterInfrastructure.h"
using namespace std;


//class constructs a graph
template<class T>
class WaterSystem {
private:
    Graph<T> supplySystem;

public:
    void addVertexFromVector(const vector<T>& vertices) {
        for (const T& vertex : vertices) {
            supplySystem.addVertex(vertex);
        }
    }

    void addEdgeFromVector(const vector<T>& edges) {
        for (const T& edge : edges) {
            if (!this->addEdge(edge)) {
                cout << "Some error occurred while adding edge";
            }
        }
    }

    bool addEdge(const T& waterinfrastructure) {
        auto sourceCode = waterinfrastructure.pipe.getSourceService();
        auto targetCode = waterinfrastructure.pipe.getTargetService();
        auto weight = waterinfrastructure.pipe.getCapacity();

        Vertex<T>* source = this->getVertexByCode(sourceCode);
        Vertex<T>* target = this->getVertexByCode(targetCode);

        if (source != nullptr && target != nullptr) {
            return supplySystem.addEdge(source->getInfo(), target->getInfo(), weight);
        }

        return false;
    }

    Vertex<T>* getVertexByCode(const string& code) {
        auto vertices = supplySystem.getVertexSet();
        for (auto vertex : vertices) {
            if (vertex->getInfo().getCode() == code) {
                return vertex;
            }
        }
        return nullptr;
    }

    void printGraph() {
        cout << "Vertices in the graph:" << endl;
        for (auto vertex : supplySystem.getVertexSet()) {
            cout << vertex->getInfo().getCode() << endl;
        }

        cout << "Edges in the graph:" << endl;
        for (auto vertex : supplySystem.getVertexSet()) {
            for (auto edge : vertex->getAdj()) {
                cout << vertex->getInfo().getCode() << " -> " << edge->getDest()->getInfo().getCode() << endl;
            }
        }
    }
};





#endif //DA2024_PRJ1_G_04_6__WATERSYSTEM_H
