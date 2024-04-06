#ifndef DA2024_PRJ1_G_04_6__WATERSYSTEM_H
#define DA2024_PRJ1_G_04_6__WATERSYSTEM_H

#include <vector>
#include <iostream>
#include "Reservoir.h"
#include "PumpingStation.h"
#include "City.h"
#include "Pipe.h"
#include "Graph.h"
#include "WaterInfrastructure.h"
using namespace std;

/**
 * @brief A class constructs the graph of Water Infrastructure type.
 * @tparam T The type of data stored in the graph vertices.
 */
template<class T>
class WaterSystem {
private:
    /**< Graph representing the water supply system. */
    Graph<T> supplySystem;

public:
    /**
     * @brief Adds vertices to the graph from a vector.
     * @param vertices Vector containing vertices to be added.
     */
    void addVertexFromVector(const vector<T>& vertices) {
        for (const T& vertex : vertices) {
            supplySystem.addVertex(vertex);
        }
    }

    /**
     * @brief Adds edges to the graph from a vector.
     * @param edges Vector containing edges to be added.
     */
    void addEdgeFromVector(const vector<T>& edges) {
        for (const T& edge : edges) {
            if (!this->addEdge(edge)) {
                cout << "Some error occurred while adding edge";
            }
        }
    }

    /**
     * @brief Adds an edge to the graph based on water infrastructure data.
     * @param waterinfrastructure Water infrastructure data containing edge information.
     * @return True if the edge was added successfully, false otherwise.
     */
    bool addEdge(const T& waterinfrastructure) {
        auto sourceCode = waterinfrastructure.pipe.getSourceService();
        auto targetCode = waterinfrastructure.pipe.getTargetService();
        auto weight = waterinfrastructure.pipe.getCapacity();

        Vertex<T>* source = this->getVertexByCode(sourceCode);
        Vertex<T>* target = this->getVertexByCode(targetCode);

        return supplySystem.addEdge(source->getInfo(), target->getInfo(), weight);
    }

    /**
     * @brief Retrieves a vertex from the graph based on its code.
     * @param code Code of the vertex to retrieve.
     * @return Pointer to the vertex if found, nullptr otherwise.
     * @throw runtime_error if the vertex with the provided code is not found.
     */
    Vertex<T>* getVertexByCode(string& code) {
        auto set = supplySystem.getVertexSet();
        for (auto vertex : set) {
            WaterInfrastructure w = vertex->getInfo();
            string vertexCode;
            switch (w.type) {
                case CITY:
                    vertexCode = w.city.getCode();
                    break;
                case PUMPINGSTATION:
                    vertexCode = w.pumpingStation.getCode();
                    break;
                case RESERVOIR:
                    vertexCode = w.reservoir.getCode();
                    break;
                default:
                    throw runtime_error("Error");
            }
            if (vertexCode == code) {
                return vertex;
            }
        }
        throw runtime_error("Error");
    }

    /**
     * @brief Prints information about vertices and their adjacent edges.
     */
    void print() {
        for (const auto& vertex : supplySystem.getVertexSet()) {
            vertex->getInfo().print();
            cout << "Edges number: " << vertex->getAdj().size() << '\n';
        }
    }
};

#endif // DA2024_PRJ1_G_04_6__WATERSYSTEM_H
