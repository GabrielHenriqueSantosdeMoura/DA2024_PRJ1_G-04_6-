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
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
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
    std::queue<Vertex<T> *> q;
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
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
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
        throw std::logic_error("Invalid source and/or target vertex");

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

void calculateMaxFlow(const vector<WaterInfrastructure> &infrastructures) {

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

    // Add edges to the graph for each pipe connecting the water infrastructures
    for (const auto &infrastructure : infrastructures) {
        if (infrastructure.type == PIPE) {
            graph.addEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(),
                          infrastructure.pipe.getCapacity());
        }
    }

    // Calculate maximum flow to each city using Edmonds-Karp algorithm
    cout << "Maximum flow to each city:" << endl;
    double totalMaxFlow = 0.0;
    for (const auto &city : infrastructures) {
        if (city.type == CITY) {
            double maxFlow = 0.0;
            for (const auto &reservoir : infrastructures) {
                if (reservoir.type == RESERVOIR) {
                    double flow = edmondsKarp(&graph, reservoir.reservoir.getCode(), city.city.getCode());
                    if (flow > maxFlow) {
                        maxFlow = flow;
                    }
                }
            }
            cout << city.city.getCode() << ": " << maxFlow << " m3/sec" << endl;
            totalMaxFlow += maxFlow; // Add the maximum flow for this city to the total
        }
    }

    // Print the total maximum flow across all cities
    cout << "Total maximum flow across all cities: " << totalMaxFlow << " m3/sec" << endl;
}
