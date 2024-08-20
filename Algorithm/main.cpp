#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

// Function to find the project duration
int findProjectDuration(const vector<Node *> &nodes)
{
    int projectDuration = 0;
    for (const auto &node : nodes)
    {
        projectDuration = max(projectDuration, node->earlyFinish);
    }

    return projectDuration;
}

// Function to display the results
void displayResults(const vector<Node *> &nodes)
{
    cout << "Node\tES\tEF\tLS\tLF\tTF\tFF\tIF\tIndF\n";
    for (const auto &node : nodes)
    {
        cout << node->name << "\t"
             << node->earlyStart << "\t"
             << node->earlyFinish << "\t"
             << node->lateStart << "\t"
             << node->lateFinish << "\t"
             << node->totalFloat << "\t"
             << node->freeFloat << "\t"
             << node->interferingFloat << "\t"
             << node->independentFloat << "\n";
    }
}

int main()
{
    // Creating nodes (example)
    Node Start("Start", 0);
    Node A("A", 3);
    Node B("B", 2);
    Node C("C", 4);
    Node D("D", 2);
    Node E("E", 3);
    Node F("F", 1);
    Node Finish("Finish", 0);

    // Defining relationships
    Start.successors = {&A};
    A.predecessors.push_back(&Start);
    A.successors = {&B, &C};
    B.predecessors = {&A};
    B.successors = {&D};
    C.predecessors = {&A};
    C.successors = {&E};
    D.predecessors = {&B};
    D.successors = {&F};
    E.predecessors = {&C};
    E.successors = {&F};
    F.predecessors = {&D, &E};
    F.successors.push_back(&Finish);
    Finish.predecessors = {&F};

    // List of all nodes
    vector<Node *> nodes = {&Start, &A, &B, &C, &D, &E, &F, &Finish};

    // Calculate early start and early finish times
    for (auto &node : nodes)
    {
        node->calculateEarlyTimes();
    }

    // Calculate the project duration
    int projectDuration = findProjectDuration(nodes);

    // Calculate late start and late finish times

    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        nodes[i]->calculateLateTimes(projectDuration);
    }

    // Calculate floats
    for (auto &node : nodes)
    {
        node->calculateFloats();
    }

    // Display the results
    displayResults(nodes);

    return 0;
}