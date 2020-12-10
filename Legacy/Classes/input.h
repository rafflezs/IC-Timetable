#ifndef _INPUT_H
#define _INPUT_H

#include "read.h"
#include "schedule.h"
#include "data.h"
#include "solution.h"
#include "heuristic.h"

using namespace std;

    void start();
    vector <Solution> generateList(Data* d, Solution* sol);
    int constructDisc(Solution* temp, Data* data);
    int constructTeacher(Solution* temp, Data* data);
    int constructGrade(Solution* temp, Data* data);
    vector <int> generateRandomList(Data* data,int constructMethod);
    void printSolution(vector<Solution> scheduleList);

#endif