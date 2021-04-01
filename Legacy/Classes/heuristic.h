#ifndef _HEURISTIC_H
#define _HEURISTIC_H

#include "objFunction.h"

    int getGrade(Data* data);

    void gradeSwap(Solution* solution, Data* data);
    void timeSwap(Solution* solution, Data* data);
    void fixAndOptimize(Solution* solution, Data* data);

    void deallocateResource(Solution* solution, Data* data, int* gradeId);
    int findSplit(int* randomDay, int* discId, Schedule* gradeSc, Schedule* teacherSc, int* mainFirstSlot, int* mainDiscDay);
    int fitDisc(int* swapFirstSlot,int* randomDay, int* mainFirstSlot, Schedule* gradeSc, Schedule* teacherSc, int* mainSplit);
    vector <int> randomizeSetJustBecause(set <int> discList);

#endif // !_HEURISTIC_H