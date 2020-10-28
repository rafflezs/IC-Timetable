#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "dependencies.h"

using namespace std;

class Schedule{

    public:

        string name;
        set<int> discList;
        int schedule[6][16];
        Schedule(int dispo[6][16], string name);
        void printSchedule();

        bool checkDisponibility(int day, int start, int end);
        bool checkConsecutive(int* day, int* firstSlot, int size, int dayStart, int slotStart, int slotEnd);
};

#endif