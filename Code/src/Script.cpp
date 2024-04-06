#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include "headers/Graph.h"
#include "headers/WaterInfrastructure.h"
#include "headers/DataReader.h"
#include "headers/Script.h"
#include "headers/Menu.h"

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
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for (auto e : v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
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
        double currFlow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(f + currFlow);
            v = e->getOrig();
        } else {
            e->setFlow(currFlow - f);
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

    for (auto &v : g->getVertexSet()){
        double flow = 0;
        for (auto e : v->getIncoming()) {
            flow += e->getFlow();
        }
        v->setflow(flow);
    }
    return maxFlow;
}

double calculateMaxFlowForCity(const vector<WaterInfrastructure> &infrastructures, const string &cityCode) {
    Graph<string> graph;

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

    string superSource = "SuperSource";
    string superSink = "SuperSink";

    // Add the super source and super sink vertices
    graph.addVertex(superSource);
    graph.addVertex(superSink);

    // Add edges from the super source to all reservoirs
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == RESERVOIR) {
            graph.addEdge(superSource, infrastructure.reservoir.getCode(), infrastructure.reservoir.getMaxDelivery());
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
                graph.addBidirectionalEdge(infrastructure.pipe.getSourceService(),infrastructure.pipe.getTargetService(),infrastructure.pipe.getCapacity());
            } else {
                // For unidirectional pipes, add edge in one direction only
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
            }
        }
    }

    // Find the maximum flow using the Edmonds-Karp algorithm
    double totalMaxFlow = edmondsKarp(&graph, superSource, superSink);

    double cityMaxFlow = 0.0;
    bool found = false;

    for (auto it = infrastructures.begin(); it != infrastructures.end(); ++it) {
        if (it->type == CITY && it->city.getCode() == cityCode) {
            cityMaxFlow = graph.findVertex(it->city.getCode())->getFlow();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "City with code " << cityCode << " does not exist." << std::endl;
    }

    return cityMaxFlow;
}






void calculateMaxFlowAllCities(const std::vector<WaterInfrastructure> &infrastructures) {
    Graph<string> graph;

    // Create the graph
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

    string superSource = "SuperSource";
    string superSink = "SuperSink";

    // Add the super source and super sink vertices
    graph.addVertex(superSource);
    graph.addVertex(superSink);

    // Add edges from the super source to all reservoirs
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == RESERVOIR) {
            graph.addEdge(superSource, infrastructure.reservoir.getCode(), infrastructure.reservoir.getMaxDelivery());
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
                graph.addBidirectionalEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
            } else {
                // For unidirectional pipes, add edge in one direction only
                graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(), infrastructure.pipe.getCapacity());
            }
        }
    }

    // Find the maximum flow using the Edmonds-Karp algorithm
    double totalMaxFlow = edmondsKarp(&graph, superSource, superSink);

    // Output the maximum flow to each city
    ofstream outputFile("/home/tiago/Desktop/DA/projeto/DA2024_PRJ1_G-04_6-/Docs/max_flow_per_city.txt");
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double cityMaxFlow = graph.findVertex(infrastructure.city.getCode())->getFlow();
            cout << "Maximum flow to city " << infrastructure.city.getCode() << " - " << infrastructure.city.getName() << ": " << cityMaxFlow << " m3/sec" << endl;
            outputFile << "Maximum flow to city " << infrastructure.city.getCode() << " - " << infrastructure.city.getName() << ": " << cityMaxFlow << " m3/sec" << endl;
        }
    }
    outputFile.close();

    // Print the total maximum flow across all cities
    cout << "Total maximum flow across all cities: " << totalMaxFlow << " m3/sec" << endl;
}


//This can be used for 2.2
map<string, double> findDeficitCities(const vector<WaterInfrastructure> &infrastructures) {
    map<string, double> deficitCities;

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

map<string, pair<double, double>> checkReservoirImpact(const string& reservoirCode, vector<WaterInfrastructure> &infrastructures) {
    map<string, double> initialMaxFlows;
    map<string, double> newMaxFlows;

    // Store the initial maximum flows for cities
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            initialMaxFlows[infrastructure.city.getCode()] = maxFlow;
        }
    }

    // reservoir failure
    auto it = infrastructures.begin();
    bool found = false;

    while (it != infrastructures.end()) {
        if (it->type == RESERVOIR && it->reservoir.getCode() == reservoirCode) {
            infrastructures.erase(it);
            found = true;
            break;
        }
        ++it;
    }

    if (!found) {
        map<string, pair<double, double>> reservoirNotFound;
        reservoirNotFound["ReservoirNotFound"] = {-1, -1}; // or any other suitable indicator
        return reservoirNotFound;
    }

    // Calculate new maximum flows after reservoir failure
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            newMaxFlows[infrastructure.city.getCode()] = maxFlow;
        }
    }

    // Compare old and new maximum flows to determine impact
    map<string, pair<double, double>> affectedCities;
    for (const auto& initialFlowPair : initialMaxFlows) {
        const string& cityCode = initialFlowPair.first;
        double oldFlow = initialFlowPair.second;
        double newFlow = newMaxFlows[cityCode];
        if (oldFlow != newFlow) {
            affectedCities[cityCode] = {oldFlow, newFlow};
        }
    }

    return affectedCities;
}

map<string, pair<double, double>> checkStationImpact(const string stationCode, vector<WaterInfrastructure> &infrastructures) {
    map<string, double> initialMaxFlows;
    map<string, double> newMaxFlows;



    // Store the initial maximum flows for cities
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            initialMaxFlows[infrastructure.city.getCode()] = maxFlow;
        }
    }

    // checking if it's real and removal
    auto it = infrastructures.begin();
    bool found = false;

    while (it != infrastructures.end()) {
        if (it->type == PUMPINGSTATION && it->pumpingStation.getCode() == stationCode) {
            infrastructures.erase(it);
            found = true;
            break;
        }
        ++it;
    }

    if (!found) {
        map<string, pair<double, double>> stationNotFound;
        stationNotFound["StationNotFound"] = {-1, -1}; // or any other suitable indicator
        return stationNotFound;
    }

    // Calculate new maximum flows after station removal
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            newMaxFlows[infrastructure.city.getCode()] = maxFlow;
        }
    }

    // Compare old and new maximum flows to determine impact
    map<string, pair<double, double>> affectedCities;
    for (const auto& initialFlowPair : initialMaxFlows) {
        const string& cityCode = initialFlowPair.first;
        double oldFlow = initialFlowPair.second;
        double newFlow = newMaxFlows[cityCode];
        if (oldFlow != newFlow) {
            affectedCities[cityCode] = {oldFlow, newFlow};
        }
    }

    return affectedCities;
}



map<string, pair<double, double>> checkPipelineImpact(const string& sourceService, const string& targetService, vector<WaterInfrastructure> &infrastructures) {
    map<string, double> initialMaxFlows;
    map<string, double> newMaxFlowsPFailure;

    // Store the initial maximum flows for cities without the failure
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            initialMaxFlows[infrastructure.city.getCode()] = maxFlow;
        }
    }

    //remove the pipeline
    auto it = infrastructures.begin();
    bool found = false;

    while (it != infrastructures.end()) {
        if (it->type == PIPE && it->pipe.getSourceService() == sourceService && it->pipe.getTargetService() == targetService) {
            infrastructures.erase(it);
            found = true;
            break;
        }
        ++it;
    }

    if (!found) {
        map<string, pair<double, double>> pipeNotFound;
        pipeNotFound["PipeNotFound"] = {-1, -1}; // or any other suitable indicator
        return pipeNotFound;
    }


    // Calculate new maximum flows after pipeline failure
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == CITY) {
            double maxFlow = calculateMaxFlowForCity(infrastructures, infrastructure.city.getCode());
            newMaxFlowsPFailure[infrastructure.city.getCode()] = maxFlow;
        }
    }

    // Compare old and new maximum flows to see where are the affected cities
    map<string, pair<double, double>> affectedCities;
    for (const auto& initialFlowPair : initialMaxFlows) {
        const string& cityCode = initialFlowPair.first;
        double oldFlow = initialFlowPair.second;
        double newFlow = newMaxFlowsPFailure[cityCode];
        if (oldFlow != newFlow) {
            affectedCities[cityCode] = {oldFlow, newFlow};
        }
    }

    return affectedCities;
}
/* void balanceFlow(Graph<string> *g) {
    double totalDiff = 0.0;
    double maxDiff = 0.0;
    int pipeCount = 0;

    // Compute initial metrics
    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            double capacity = e->getWeight();
            double flow = e->getFlow();
            double diff = capacity - flow;
            totalDiff += diff;
            maxDiff = max(maxDiff, diff);
            pipeCount++;
        }
    }

    double avgDiff = totalDiff / pipeCount;

    // Balancing algorithm
    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            double capacity = e->getWeight();
            double flow = e->getFlow();
            double diff = capacity - flow;

            if (diff > avgDiff) {
                // Reduce excess flow
                e->setFlow(capacity);
            } else if (diff < -avgDiff) {
                // Increase flow to meet capacity
                e->setFlow(capacity);
            }
        }
    }

    // Compute metrics after balancing
    double totalDiffAfter = 0.0;
    double maxDiffAfter = 0.0;

    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            double capacity = e->getWeight();
            double flow = e->getFlow();
            double diff = capacity - flow;
            totalDiffAfter += diff;
            maxDiffAfter = max(maxDiffAfter, diff);
        }
    }

    double avgDiffAfter = totalDiffAfter / pipeCount;

    // Output results
    cout << "Initial Metrics:" << endl;
    cout << "Average difference: " << avgDiff << endl;
    cout << "Variance of differences: " << (totalDiff * totalDiff) / pipeCount << endl;
    cout << "Maximum difference: " << maxDiff << endl;

    cout << endl << "Metrics after balancing:" << endl;
    cout << "Average difference: " << avgDiffAfter << endl;
    cout << "Variance of differences: " << (totalDiffAfter * totalDiffAfter) / pipeCount << endl;
    cout << "Maximum difference: " << maxDiffAfter << endl;
} */
