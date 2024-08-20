#include "Node.h"
#include <limits.h>
#include <algorithm>
using namespace std;

// Calculate Early Start and Early Finish
void Node::calculateEarlyTimes()
{
    earlyStart = 0;
    if (!predecessors.empty())
    {
        for (auto predecessor : predecessors)
        {
            earlyStart = max(earlyStart, predecessor->earlyFinish);
        }
    }
    earlyFinish = earlyStart + duration;
}

// Calculate Late Start and Late Finish
void Node::calculateLateTimes(int projectDuration)
{
    lateFinish = projectDuration;

    if (!successors.empty())
    {
        for (auto successor : successors)
        {
            lateFinish = min(lateFinish, successor->lateStart);
        }
    }
    lateStart = lateFinish - duration;
}

// Calculate Floats
void Node::calculateFloats()
{
    int min_es = earlyFinish;
    int max_lf = INT_MIN;
    totalFloat = lateStart - earlyStart;
    if (!successors.empty())
    {
        freeFloat = earlyFinish;
    }

    for (auto successor : successors)
    {
        if (successor)
            freeFloat = min(freeFloat, successor->earlyStart) - earlyFinish;
        if (successor)
            min_es = min(min_es, successor->earlyStart);
    }
    freeFloat = max(0, freeFloat);
    interferingFloat = totalFloat - freeFloat;

    for (auto predecessor : predecessors)
    {
        if (predecessor)
            max_lf = max(max_lf, predecessor->lateFinish);
    }
    independentFloat = max(0, min_es - max_lf - duration);
}
