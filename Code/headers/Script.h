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

template <class T>
void testAndVisit(queue<Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual);

template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t);

template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);

template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);

template <class T>
double edmondsKarp(Graph<T> *g, T source, T target);

void calculateMaxFlowAllCities(const vector<WaterInfrastructure>& infrastructures);

double calculateMaxFlowForCity(const vector<WaterInfrastructure> &infrastructures, const string &cityCode);

map<string, double> findDeficitCities(const vector<WaterInfrastructure> &infrastructures);

map<string, pair<double, double>> checkReservoirImpact(const string& reservoirCode, vector<WaterInfrastructure> &infrastructures);

map<string, pair<double, double>> checkStationImpact(string stationCode, vector<WaterInfrastructure> &infrastructures);

map<string, pair<double, double>> checkPipelineImpact(const string& sourceService, const string& targetService, vector<WaterInfrastructure> &infrastructures);

void balanceFlow(Graph<string> *g);

#endif // SCRIPT_H
