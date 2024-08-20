#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int duration;
    int earlyStart;
    int earlyFinish;
    int lateStart;
    int lateFinish;
    int freeFloat;
    int totalFloat;
    int interferingFloat;
    int independentFloat;
    vector<Node *> predecessors;
    vector<Node *> successors;

    Node(string name, int duration)
        : name(name), duration(duration), earlyStart(0), earlyFinish(0), lateStart(0), lateFinish(0),
          freeFloat(0), totalFloat(0), interferingFloat(0), independentFloat(0) {}

    void calculateEarlyTimes();
    void calculateLateTimes(int projectDuration);
    void calculateFloats();
};

#endif
