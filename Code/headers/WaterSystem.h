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

    //add vertexes to the graph
    void addVertexFromVector(const vector<T>& vertices) {
        for (const T& vertex : vertices) {
            supplySystem.addVertex(vertex);
        }
    }

    //add edges to the graph
    void addEdgeFromVector(const vector<T>& edges){
        for (const T& edge : edges){
            if (!this->addEdge(edge)){
                cout<<"Some error occurred while adding edge";
            }

        }
    }


    bool addEdge(const T& waterinfrastructure) {
        auto sourceCode = waterinfrastructure.pipe.getSourceService();
        auto targetCode = waterinfrastructure.pipe.getTargetService();

        auto weight = waterinfrastructure.pipe.getCapacity();

        Vertex <T > * source = this->getVertexByCode(sourceCode);
        Vertex <T > * target = this->getVertexByCode(targetCode);
        return supplySystem.addEdge(source->getInfo(),target->getInfo(),weight);
    }


    Vertex<T> * getVertexByCode(string& code){
        auto set = supplySystem.getVertexSet();
        for ( auto vertex : set){
            WaterInfrastructure w = vertex->getInfo();
            string vertexCode ;
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
            if (vertexCode == code){
                return vertex;
            }
        }
        throw runtime_error("Error");
    }


    //the method to print the data to check if the graph created properly, could be deleted
    void print (){
        for (const auto & vertex: supplySystem.getVertexSet() ){
            vertex->getInfo().print();
            cout<<"Edges number: "<<vertex->getAdj().size()<<'\n';

        }
    }




};


#endif //DA2024_PRJ1_G_04_6__WATERSYSTEM_H
