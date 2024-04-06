#ifndef DA2024_PRJ1_G_04_6__PIPE_H
#define DA2024_PRJ1_G_04_6__PIPE_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Represents a pipe connecting two services in a water infrastructure system.
 */
class Pipe {
private:
    /**< The source service connected by the pipe. */
    string sourceService;

    /**< The target service connected by the pipe. */
    string targetService;

    /**< The capacity of the pipe. */
    double capacity;

    /**< The direction of the pipe, true for unidirectional, false for bidirectional. */
    bool direction;

public:
    /**
     * @brief Constructs a new Pipe object with provided attributes.
     * @param sourceService The name of the source service.
     * @param targetService The name of the target service.
     * @param capacity The capacity of the pipe.
     * @param direction The direction of the pipe (true for unidirectional, false for bidirectional).
     */
    Pipe(const string& sourceService, const string& targetService, double capacity, bool direction);

    /**
     * @brief Default constructor for Pipe class.
     */
    Pipe() = default;

    /**
     * @brief Gets the name of the source service connected by the pipe.
     * @return The name of the source service.
     */
    string getSourceService() const;

    /**
     * @brief Gets the name of the target service connected by the pipe.
     * @return The name of the target service.
     */
    string getTargetService() const;

    /**
     * @brief Gets the capacity of the pipe.
     * @return The capacity of the pipe.
     */
    double getCapacity() const;

    /**
     * @brief Checks if the pipe is bidirectional.
     * @return True if the pipe is bidirectional, false otherwise.
     */
    bool isBidirectional() const;

    /**
     * @brief Method for printing information about the pipe.
     * Could be deleted or used for debugging purposes.
     */
    void print() const {
        //cout << "Pipe: " << getCapacity() << '\n';
    }
};

#endif // DA2024_PRJ1_G_04_6__PIPE_H
