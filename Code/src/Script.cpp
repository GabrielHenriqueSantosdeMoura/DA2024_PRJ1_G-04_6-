#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "headers/Graph.h"
#include "headers/WaterInfrastructure.h"
#include "headers/DataReader.h"
#include "headers/Script.h"

using namespace std;

template <class T>
void testAndVisit(queue<Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    s->setVisited(true);
    queue<Vertex<T>*> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e : v->getAdj()) {
            double residual = e->getWeight() - e->getFlow();
            testAndVisit(q, e, e->getDest(), residual);
        }
        for (auto e : v->getIncoming()) {
            double residual = e->getFlow();
            testAndVisit(q, e, e->getOrig(), residual);
        }
    }
    return t->isVisited();
}

template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            e->setFlow(e->getFlow() + f);
            v = e->getOrig();
        } else {
            e->setFlow(e->getFlow() - f);
            v = e->getDest();
        }
    }
}

template <class T>
double edmondsKarp(Graph<T> *g, T source, T target) {
    Vertex<T> *s = g->findVertex(source);
    Vertex<T> *t = g->findVertex(target);

    if (s == nullptr || t == nullptr || s == t)
        throw logic_error("Invalid source and/or target vertex");

    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }
    double maxFlow = 0.0;
    while (findAugmentingPath(g, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
        maxFlow += f;
    }
    return maxFlow;
}

double calculateMaxFlowForCity(const std::vector<WaterInfrastructure> &infrastructures, const std::string &cityCode) {
    Graph<std::string> graph;

    // Add vertices to the graph for each water infrastructure
    for (const auto &infrastructure : infrastructures) {
        switch (infrastructure.type) {
            case RESERVOIR:
                graph.addVertex(infrastructure.reservoir.getCode());
                break;
            case CITY:
                graph.addVertex(infrastructure.city.getCode());
                break;
            case PUMPINGSTATION:
                graph.addVertex(infrastructure.pumpingStation.getCode());
                break;
            default:
                break;
        }
    }

    std::string superSource = "SuperSource";
    std::string superSink = "SuperSink";

    // Add the super source and super sink vertices
    graph.addVertex(superSource);
    graph.addVertex(superSink);

    // Add edges from the super source to all reservoirs
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == RESERVOIR) {
            graph.addEdge(superSource, infrastructure.reservoir.getCode(), infrastructure.reservoir.getMaxDelivery());
        }
    }

    // Add edges from all reservoirs to their corresponding cities
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == RESERVOIR) {
            graph.addEdge(infrastructure.reservoir.getCode(), infrastructure.city.getCode(), std::numeric_limits<double>::max());
        }
    }

    // Add edges from all cities to the super sink with capacity equal to their demand
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            graph.addEdge(infrastructure.city.getCode(), superSink, infrastructure.city.getDemand());
        }
    }

    // Add edges to the graph for each pipe connecting the water infrastructures
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == PIPE) {
            if (infrastructure.pipe.isBidirectional()) {
                // For bidirectional pipes, add edges in both directions
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
                graph.addEdge(infrastructure.pipe.getTargetService(), infrastructure.pipe.getSourceService(), infrastructure.pipe.getCapacity());
            } else {
                // For unidirectional pipes, add edge in one direction only
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
            }
        }
    }

    // Find the maximum flow using the Edmonds-Karp algorithm
    double totalMaxFlow = edmondsKarp(&graph, superSource, superSink);

    double cityMaxFlow = 0.0;
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY && infrastructure.city.getCode() == cityCode) {
            for (const auto &edge : graph.findVertex(infrastructure.city.getCode())->getIncoming()) {
                if (edge->getOrig()->getInfo() != superSource) {
                    cityMaxFlow += edge->getFlow();
                }
            }
            break;
        }
    }

    return cityMaxFlow;
}






void calculateMaxFlowAllCities(const std::vector<WaterInfrastructure> &infrastructures) {
    Graph<std::string> graph;

    // Add vertices to the graph for each water infrastructure
    for (const auto &infrastructure : infrastructures) {
        switch (infrastructure.type) {
            case RESERVOIR:
                graph.addVertex(infrastructure.reservoir.getCode());
                break;
            case CITY:
                graph.addVertex(infrastructure.city.getCode());
                break;
            case PUMPINGSTATION:
                graph.addVertex(infrastructure.pumpingStation.getCode());
                break;
            default:
                break;
        }
    }

    std::string superSource = "SuperSource";
    std::string superSink = "SuperSink";

    // Add the super source and super sink vertices
    graph.addVertex(superSource);
    graph.addVertex(superSink);

    // Add edges from the super source to all reservoirs
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == RESERVOIR) {
            graph.addEdge(superSource, infrastructure.reservoir.getCode(), infrastructure.reservoir.getMaxDelivery());
        }
    }

    // Add edges from all reservoirs to their corresponding cities
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == RESERVOIR) {
            graph.addEdge(infrastructure.reservoir.getCode(), infrastructure.city.getCode(), std::numeric_limits<double>::max());
        }
    }

    // Add edges from all cities to the super sink with capacity equal to their demand
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            graph.addEdge(infrastructure.city.getCode(), superSink, infrastructure.city.getDemand());
        }
    }

    // Add edges to the graph for each pipe connecting the water infrastructures
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == PIPE) {
            if (infrastructure.pipe.isBidirectional()) {
                // For bidirectional pipes, add edges in both directions
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
                graph.addEdge(infrastructure.pipe.getTargetService(), infrastructure.pipe.getSourceService(), infrastructure.pipe.getCapacity());
            } else {
                // For unidirectional pipes, add edge in one direction only
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
            }
        }
    }

    // Find the maximum flow using the Edmonds-Karp algorithm
    double totalMaxFlow = edmondsKarp(&graph, superSource, superSink);

    // Output the maximum flow to each city
    cout << "Maximum flow to each city:" << endl;
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double cityMaxFlow = 0.0;
            for (const auto &edge : graph.findVertex(infrastructure.city.getCode())->getIncoming()) {
                if (edge->getOrig()->getInfo() != superSource) {
                    cityMaxFlow += edge->getFlow();
                }
            }
            cout << "Maximum flow to city " << infrastructure.city.getCode() << ": " << cityMaxFlow << " m3/sec" << endl;
        }
    }

    // Print the total maximum flow across all cities
    cout << "Total maximum flow across all cities: " << totalMaxFlow << " m3/sec" << std::endl;
}


map<string, double> findDeficitCities(const vector<WaterInfrastructure> &infrastructures) {
    map<std::string, double> deficitCities;

    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double cityDemand = infrastructure.city.getDemand();
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            if (maxFlow < cityDemand) {
                deficitCities[infrastructure.city.getCode()] = cityDemand - maxFlow;
            }
        }
    }

    return deficitCities;
}

map<std::string, double> checkStationImpact(string stationCode, vector<WaterInfrastructure> &infrastructures) {
    std::map<std::string, double> initialDeficitCities = findDeficitCities(infrastructures);

    for (auto it = infrastructures.begin(); it != infrastructures.end(); ++it) {
        if (it->type == PUMPINGSTATION && it->pumpingStation.getCode() == stationCode) {
            infrastructures.erase(it);
            break;
        }
    }

    // Check water supply after removing the pumping station
    std::map<std::string, double> deficitCities = findDeficitCities(infrastructures);

    // Calculate affected cities
    std::map<std::string, double> affectedCities;
    for (const auto& cityPair : deficitCities) {
        if (initialDeficitCities.find(cityPair.first) == initialDeficitCities.end() || cityPair.second > initialDeficitCities[cityPair.first]) {
            affectedCities[cityPair.first] = cityPair.second;
        }
    }

    // Reset the infrastructures
    resetData(infrastructures);

    return affectedCities;
}

map<string, double> checkPipelineImpact(const string& sourceService, const string& targetService, vector<WaterInfrastructure> &infrastructures) {
    std::map<std::string, double> initialDeficitCities = findDeficitCities(infrastructures);

    // Find the pipeline with the given source and target services and simulate its failure
    for (auto it = infrastructures.begin(); it != infrastructures.end(); ++it) {
        if (it->type == PIPE && it->pipe.getSourceService() == sourceService && it->pipe.getTargetService() == targetService) {
            it->pipe.setCapacity(0); // Simulate pipeline failure by setting its capacity to zero
            break;
        }
    }

    // Check water supply after simulating pipeline failure
    std::map<std::string, double> deficitCities = findDeficitCities(infrastructures);

    // Calculate affected cities
    std::map<std::string, double> affectedCities;
    for (const auto& cityPair : deficitCities) {
        if (initialDeficitCities.find(cityPair.first) == initialDeficitCities.end() || cityPair.second > initialDeficitCities[cityPair.first]) {
            affectedCities[cityPair.first] = cityPair.second;
        }
    }

    resetData(infrastructures);

    return affectedCities;
}


void resetData(vector<WaterInfrastructure>& infrastructures) {
    infrastructures.clear();

    // Read data again and populate infrastructures vector
    vector<WaterInfrastructure> cities = DataReader::readCities("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Cities_Madeira.csv");
    vector<WaterInfrastructure> stations = DataReader::readPumpingStations("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Stations_Madeira.csv");
    vector<WaterInfrastructure> reservoirs = DataReader::readReservoirs("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Reservoirs_Madeira.csv");
    vector<WaterInfrastructure> pipes = DataReader::readPipes("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/Project1DataSetSmall/Pipes_Madeira.csv");

    // Merge data into infrastructures vector
    infrastructures.insert(infrastructures.end(), cities.begin(), cities.end());
    infrastructures.insert(infrastructures.end(), stations.begin(), stations.end());
    infrastructures.insert(infrastructures.end(), reservoirs.begin(), reservoirs.end());
    infrastructures.insert(infrastructures.end(), pipes.begin(), pipes.end());
}





