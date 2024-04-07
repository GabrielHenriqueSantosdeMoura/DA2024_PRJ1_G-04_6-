#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#include "headers/Graph.h"
#include "headers/WaterInfrastructure.h"
#include "headers/DataReader.h"
using namespace std;

/**
 * @brief Namespace containing all of the algorithms of the water supply system.
 */
namespace Script{
    /**
 * @brief Tests and visits a vertex based on an edge and residual flow.
 * @tparam T Type of information stored in the vertex.
 * @param q Queue of vertices to visit.
 * @param e Edge being considered.
 * @param w Vertex to visit.
 * @param residual Residual flow along the edge.
 */
    template <class T>
    void testAndVisit(queue<Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);

    /**
 * @brief Implements the Edmonds-Karp algorithm to find the maximum flow in a graph.
 * @tparam T Type of information stored in the vertices.
 * @param g Pointer to the graph.
 * @param source Source vertex of the flow.
 * @param target Target vertex of the flow.
 * @return Maximum flow from source to target.
 * @complexity O(V * E^2), where V is the number of vertices and E is the number of edges in the graph.
 */
    template <class T>
    double edmondsKarp(Graph<T> *g, T source, T target);

/**
 * @brief Finds an augmenting path in the graph using BFS.
 * @tparam T Type of information stored in the graph.
 * @param g Pointer to the graph.
 * @param s Source vertex of the path.
 * @param t Target vertex of the path.
 * @return True if an augmenting path is found, false otherwise.
 * @complexity O(V + E),where V is the number of vertices and E is the number of edges in the graph.
 */
    template <class T>
    bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);

/**
 * @brief Finds the minimum residual along an augmenting path.
 * @tparam T Type of information stored in the vertices.
 * @param s Source vertex of the path.
 * @param t Target vertex of the path.
 * @return Minimum residual along the path.
 * @complexity O(E), where E is the number of edges in the graph.
 */
    template <class T>
    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);

/**
 * @brief Augments the flow along an augmenting path.
 * @tparam T Type of information stored in the vertices.
 * @param s Source vertex of the path.
 * @param t Target vertex of the path.
 * @param f Flow to augment along the path.
 * @complexity O(E), where E is the number of edges in the graph.
 */
    template <class T>
    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);



/**
 * @brief Calculates the maximum flow for all cities in the water infrastructure data.
 * @param infrastructures Vector containing water infrastructure data.
 */

    void calculateMaxFlowAllCities(const vector<WaterInfrastructure>& infrastructures);

/**
 * @brief Calculates the maximum flow for a specific city in the water infrastructure data.
 * @param infrastructures Vector containing water infrastructure data.
 * @param cityCode Code of the city.
 * @return Maximum flow for the specified city.
 */
    double calculateMaxFlowForCity(const vector<WaterInfrastructure> &infrastructures, const string &cityCode);

/**
 * @brief Finds cities with water supply deficit in the water infrastructure data.
 * @param infrastructures Vector containing water infrastructure data.
 * @return Map of cities with their corresponding water supply deficits.
 * @complexity O(nlogk),where n is the number of elements in the infrastructures vector, and k is the number of entries in the deficitCities map.
 */
    map<string, double> findDeficitCities(const vector<WaterInfrastructure> &infrastructures);

/**
 * @brief Checks the impact of a reservoir on the water infrastructure.
 * @param reservoirCode Code of the reservoir.
 * @param infrastructures Vector containing water infrastructure data.
 * @return Map of affected cities with their corresponding deficit and excess.
 * @complexity O(n⋅m).
 */
    map<string, pair<double, double>> checkReservoirImpact(const string& reservoirCode, vector<WaterInfrastructure> &infrastructures);

/**
 * @brief Checks the impact of a pumping station on the water infrastructure.
 * @param stationCode Code of the pumping station.
 * @param infrastructures Vector containing water infrastructure data.
 * @return Map of affected cities with their corresponding deficit and excess.
 * @complexity O(n⋅m).
 */
    map<string, pair<double, double>> checkStationImpact(string stationCode, vector<WaterInfrastructure> &infrastructures);

/**
 * @brief Checks the impact of a pipeline on the water infrastructure.
 * @param sourceService Code of the source service.
 * @param targetService Code of the target service.
 * @param infrastructures Vector containing water infrastructure data.
 * @return Map of affected cities with their corresponding deficit and excess.
 * @complexity O(n⋅m).
 */
    map<string, pair<double, double>> checkPipelineImpact(const string& sourceService, const string& targetService, vector<WaterInfrastructure> &infrastructures);

/**
 * @brief Balances the flow in the graph to ensure conservation of flow.
 * @param g Pointer to the graph.
 */
    void balanceFlow(Graph<string> *g);


};



#endif // SCRIPT_H
