#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>


template <class T>
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

/**
 * @brief Represents a vertex in a graph with generic information of type T.
 * @tparam T The type of information stored in the vertex.
 */
template <class T>
class Vertex {
private:
    /**< The information stored in the vertex. */
    T info;

    /**< The outgoing edges from the vertex. */
    std::vector<Edge<T> *> adj;

    /**< Flag indicating whether the vertex has been visited during traversal. */
    bool visited = false;

    /**< Flag indicating whether the vertex is being processed during traversal. */
    bool processing = false;

    /**< The number of incoming edges to the vertex. */
    unsigned int indegree;

    /**< The distance from the source vertex. */
    double dist = 0;

    /**< The path leading to this vertex. */
    Edge<T> *path = nullptr;

    /**< The incoming flow to the vertex. */
    double incflow;

    /**< The incoming edges to the vertex. */
    std::vector<Edge<T> *> incoming;

public:
    /**
     * @brief Constructs a new Vertex object with the given information.
     * @param in The information to be stored in the vertex.
     */
    Vertex(T in);

    /**
     * @brief Gets the information stored in the vertex.
     * @return The information stored in the vertex.
     */
    T getInfo() const;

    /**
     * @brief Gets the outgoing edges from the vertex.
     * @return A vector of pointers to the outgoing edges.
     */
    std::vector<Edge<T> *> getAdj() const;

    /**
     * @brief Checks if the vertex has been visited during traversal.
     * @return True if the vertex has been visited, otherwise false.
     */
    bool isVisited() const;

    /**
     * @brief Checks if the vertex is being processed during traversal.
     * @return True if the vertex is being processed, otherwise false.
     */
    bool isProcessing() const;

    /**
     * @brief Gets the number of incoming edges to the vertex.
     * @return The number of incoming edges.
     */
    unsigned int getIndegree() const;

    /**
     * @brief Gets the distance from the source vertex.
     * @return The distance from the source vertex.
     */

    Edge<T> *getPath() const;

    /**
     * @brief Gets the incoming edges to the vertex.
     * @return A vector of pointers to the incoming edges.
     */
    std::vector<Edge<T> *> getIncoming() const;

    /**
     * @brief Sets the information stored in the vertex.
     * @param info The information to be stored.
     */

    void setVisited(bool visited);

    /**
     * @brief Sets the processing flag of the vertex.
     * @param processing The value to set for the processing flag.
     */
    void setProcesssing(bool processing);

    /**
     * @brief Sets the number of incoming edges to the vertex.
     * @param indegree The number of incoming edges.
     */
    void setIndegree(unsigned int indegree);

    /**
     * @brief Sets the distance from the source vertex.
     * @param dist The distance from the source vertex.
     */

    void setPath(Edge<T> *path);

    /**
     * @brief Adds an outgoing edge from the vertex to the destination vertex with the given weight.
     * @param dest A pointer to the destination vertex.
     * @param w The weight of the edge.
     * @return A pointer to the newly created edge.
     */
    Edge<T> *addEdge(Vertex<T> *dest, double w);

    /**
     * @brief Removes an outgoing edge from the vertex with the given information.
     * @param in The information of the destination vertex of the edge to be removed.
     * @return True if the edge was successfully removed, otherwise false.
     */
    bool removeEdge(T in);

    /**
     * @brief Removes all outgoing edges from the vertex.
     */
    void removeOutgoingEdges();

    /**
     * @brief Sets the incoming flow to the vertex.
     * @param f The incoming flow to be set.
     */
    void setflow(double f);

    /**
     * @brief Gets the incoming flow to the vertex.
     * @return The incoming flow to the vertex.
     */
    double getFlow() const;

    /**
     * @brief Deletes the specified edge from the vertex's adjacency list.
     * @param edge A pointer to the edge to be deleted.
     */
    void deleteEdge(Edge<T> *edge);

    /**
    * @brief Overload of the less than operator for comparing vertices based on their distance.
    * @param vertex The vertex to compare with.
    * @return True if this vertex has a smaller distance than the specified vertex, otherwise false.
    */
    bool operator<(Vertex<T> & vertex) const;
};

/********************** Edge  ****************************/

/**
 * @brief Represents an edge in a graph connecting two vertices.
 * @tparam T The type of information stored in the vertices.
 */
template <class T>
class Edge {
private:

    /**< Pointer to the destination vertex of the edge. */
    Vertex<T> * dest;

    /**< The weight of the edge. */
    double weight;

    /**< Pointer to the original (source) vertex of the edge. */
    Vertex<T> *orig;

    /**< Pointer to the reverse edge, used for bidirectional graphs. */
    Edge<T> *reverse = nullptr;

    /**< The flow value associated with the edge. */
    double flow;

public:
    /**
     * @brief Constructs an edge with the given origin, destination, and weight.
     * @param orig Pointer to the origin vertex.
     * @param dest Pointer to the destination vertex.
     * @param w The weight of the edge.
     */
    Edge(Vertex<T> *orig, Vertex<T> *dest, double w);

    /**
     * @brief Gets the destination vertex of the edge.
     * @return Pointer to the destination vertex.
     */
    Vertex<T> * getDest() const;

    /**
     * @brief Gets the weight of the edge.
     * @return The weight of the edge.
     */
    double getWeight() const;

    /**
     * @brief Gets the origin vertex of the edge.
     * @return Pointer to the origin vertex.
     */
    Vertex<T> * getOrig() const;

    /**
     * @brief Gets the flow value associated with the edge.
     * @return The flow value.
     */
    double getFlow() const;

    /**
     * @brief Sets the reverse edge for bidirectional graphs.
     * @param reverse Pointer to the reverse edge.
     */
    void setReverse(Edge<T> *reverse);

    /**
     * @brief Sets the flow value associated with the edge.
     * @param flow The flow value to set.
     */
    void setFlow(double flow);


};


/********************** Graph  ****************************/

/**
 * @brief Represents a graph data structure with vertices and edges.
 * @tparam T The type of information stored in the vertices.
 */
template <class T>
class Graph {
private:
    /**< The set of vertices in the graph. */
    std::vector<Vertex<T> *> vertexSet;

public:
    /**
     * @brief Finds a vertex in the graph with the given information.
     * @param in The information to search for in the vertices.
     * @return Pointer to the vertex with the specified information, or nullptr if not found.
     */
    Vertex<T> *findVertex(const T &in) const;

    /**
     * @brief Adds a vertex with the given information to the graph.
     * @param in The information to be stored in the new vertex.
     * @return True if the vertex is added successfully, false otherwise (e.g., if the vertex already exists).
     */
    bool addVertex(const T &in);

    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param sourc The information of the source vertex.
     * @param dest The information of the destination vertex.
     * @param w The weight of the edge.
     * @return True if the edge is added successfully, false otherwise (e.g., if the source or destination vertex does not exist).
     */
    bool addEdge(const T &sourc, const T &dest, double w);

    /**
     * @brief Adds a bidirectional edge between two vertices in the graph.
     * @param sourc The information of the source vertex.
     * @param dest The information of the destination vertex.
     * @param w The weight of the edge.
     * @return True if the bidirectional edge is added successfully, false otherwise.
     */
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);

    /**
     * @brief Gets the set of vertices in the graph.
     * @return A vector containing pointers to all vertices in the graph.
     */
    std::vector<Vertex<T> *> getVertexSet() const;
};

/************************* Vertex  **************************/

/**
 * @brief Constructs a new Vertex object with the given information.
 * @tparam T The type of information stored in the vertex.
 * @param in The information to be stored in the vertex.
 */
template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/**
 * @brief Adds an edge from this vertex to the specified destination vertex with the given weight.
 * @tparam T The type of information stored in the vertices.
 * @param d Pointer to the destination vertex.
 * @param w The weight of the edge.
 * @return Pointer to the newly created edge.
 */
template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *d, double w) {
    auto newEdge = new Edge<T>(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/**
 * @brief Overloaded less-than operator to compare vertices based on their distance.
 * @tparam T The type of information stored in the vertices.
 * @param vertex The vertex to compare with.
 * @return True if this vertex's distance is less than the other vertex's distance, false otherwise.
 */
template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

/**
 * @brief Gets the information stored in the vertex.
 * @tparam T The type of information stored in the vertex.
 * @return The information stored in the vertex.
 */
template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

/**
 * @brief Gets the list of outgoing edges from this vertex.
 * @tparam T The type of information stored in the vertices.
 * @return A vector containing pointers to the outgoing edges.
 */
template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}

/**
 * @brief Checks if the vertex has been visited.
 * @tparam T The type of information stored in the vertices.
 * @return True if the vertex has been visited, false otherwise.
 */
template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

/**
 * @brief Sets the flow value for the vertex.
 * @tparam T The type of information stored in the vertices.
 * @param f The flow value to set.
 */
template <class T>
void Vertex<T>::setflow(double f) {
    incflow = f;
}

/**
 * @brief Gets the flow value for the vertex.
 * @tparam T The type of information stored in the vertices.
 * @return The flow value of the vertex.
 */
template <class T>
double Vertex<T>::getFlow() const {
    return this->incflow;
}

/**
 * @brief Gets the path associated with the vertex.
 * @tparam T The type of information stored in the vertices.
 * @return Pointer to the edge representing the path associated with the vertex.
 */
template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

/**
 * @brief Gets the list of incoming edges to this vertex.
 * @tparam T The type of information stored in the vertices.
 * @return A vector containing pointers to the incoming edges.
 */
template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

/**
 * @brief Sets the visited status of the vertex.
 * @tparam T The type of information stored in the vertices.
 * @param visited The visited status to set.
 */
template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * @brief Sets the path associated with the vertex.
 * @tparam T The type of information stored in the vertices.
 * @param path Pointer to the edge representing the path to set.
 */
template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

/********************** Edge  ****************************/

/**
 * @brief Constructs a new Edge object with the specified origin, destination, and weight.
 * @tparam T The type of information stored in the vertices.
 * @param orig Pointer to the origin vertex of the edge.
 * @param dest Pointer to the destination vertex of the edge.
 * @param w The weight of the edge.
 */
template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double w): orig(orig), dest(dest), weight(w) {}

/**
 * @brief Gets the destination vertex of the edge.
 * @tparam T The type of information stored in the vertices.
 * @return Pointer to the destination vertex.
 */
template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

/**
 * @brief Gets the weight of the edge.
 * @tparam T The type of information stored in the vertices.
 * @return The weight of the edge.
 */
template <class T>
double Edge<T>::getWeight() const {
    return this->weight;
}

/**
 * @brief Gets the origin vertex of the edge.
 * @tparam T The type of information stored in the vertices.
 * @return Pointer to the origin vertex.
 */
template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

/**
 * @brief Gets the flow value associated with the edge.
 * @tparam T The type of information stored in the vertices.
 * @return The flow value of the edge.
 */
template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

/**
 * @brief Sets the reverse edge of this edge.
 * @tparam T The type of information stored in the vertices.
 * @param reverse Pointer to the reverse edge.
 */
template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}

/**
 * @brief Sets the flow value for the edge.
 * @tparam T The type of information stored in the vertices.
 * @param flow The flow value to set.
 */
template <class T>
void Edge<T>::setFlow(double flow) {
    this->flow = flow;
}


/********************** Graph  ****************************/
/**
 * @brief Gets the vector containing pointers to all vertices in the graph.
 * @tparam T The type of information stored in the vertices.
 * @return Vector containing pointers to all vertices.
 */
template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/**
 * @brief Finds and returns a vertex with the given information.
 * @tparam T The type of information stored in the vertices.
 * @param in The information to search for in the vertices.
 * @return Pointer to the vertex if found, otherwise nullptr.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

/**
 * @brief Adds a new vertex with the given information to the graph.
 * @tparam T The type of information stored in the vertices.
 * @param in The information to be stored in the new vertex.
 * @return True if the vertex was successfully added, false if a vertex with the same information already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/**
 * @brief Adds an edge between vertices with the specified source and destination information, with the given weight.
 * @tparam T The type of information stored in the vertices.
 * @param sourc The information of the source vertex.
 * @param dest The information of the destination vertex.
 * @param w The weight of the edge.
 * @return True if the edge was successfully added, false if either the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/**
 * @brief Adds a bidirectional edge between vertices with the specified source and destination information, with the given weight.
 * @tparam T The type of information stored in the vertices.
 * @param sourc The information of the source vertex.
 * @param dest The information of the destination vertex.
 * @param w The weight of the edge.
 * @return True if the bidirectional edge was successfully added, false if either the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

#endif /* DA_TP_CLASSES_GRAPH */