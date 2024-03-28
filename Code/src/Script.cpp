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
            graph.addBidirectionalEdge(infrastructure.pipe.getSourceService(), infrastructure.pipe.getTargetService(),
                                       infrastructure.pipe.getCapacity());
        }
    }

    // Find the maximum flow to each city using the Edmonds-Karp algorithm
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
            cout << "Maximum flow to city " << city.city.getCode() << ": " << maxFlow << " m3/sec" << endl;
            totalMaxFlow += maxFlow;
        }
    }

    // Print the total maximum flow across all cities
    cout << "Total maximum flow across all cities: " << totalMaxFlow << " m3/sec" << endl;
}

void balanceFlow(Graph<string> *g) {

    // This shows the difference of some metrics before/after a balancing

    double totalDiff = 0.0;
    double maxDiff = 0.0;
    int pipeCount = 0;

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

    cout << endl << " Initial Metrics:" << endl;
    cout << "Average difference: " << avgDiff << endl;
    cout << "Variance of differences: " << (totalDiff * totalDiff) / pipeCount << endl;
    cout << "Maximum difference: " << maxDiff << endl;

    cout << endl << " Metrics after balancing:" << endl;
    cout << "Average difference: " << avgDiffAfter << endl;
    cout << "Variance of differences: " << (totalDiffAfter * totalDiffAfter) / pipeCount << endl;
    cout << "Maximum difference: " << maxDiffAfter << endl;
}
