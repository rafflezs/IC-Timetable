#ifndef _SOLUTION_H
#define _SOLUTION_H

#include "dependencies.h"
#include "schedule.h"
#include "data.h"

using namespace std;

class Solution{

    public:
        vector <Schedule> teacher;
        vector <Schedule> grade;
        vector <Schedule> room;

        Solution(Data* d);

        void read();

        void printGrade();
        void printTeacher();
        void printRoom();

        bool checkDisponibility(Schedule teacher, Schedule grade, Schedule room,int* day, int* start, int end);
        int discToTeacher(Data* d, int discId);
        int discToGrade(Data* d, int discId);
        int insertEarly(Data* data, int discId);
        bool checkConsecutive(int *day, int *firstSlot, int size, int dayStart, int slotStart, int slotEnd, set<int> tabooDays, Schedule teacher, Schedule grade, Schedule room);

        int roomToDisc(int discId, Data* data);
};

#endif