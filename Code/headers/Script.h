#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
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

void calculateMaxFlow(const vector<WaterInfrastructure>& infrastructures);

void balanceFlow(Graph<string> *g);

#endif // SCRIPT_H
