#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "read.h"
#include "schedule.h"

using namespace std;

        void start();

        vector <Schedule*> generate(vector <Teacher*>, vector <Discipline*>, vector <Course*>, vector <Grade*>, vector <Room*>);

        Schedule* getSc(Teacher* t, Discipline* d, Course* c, Schedule* sch);

#endif