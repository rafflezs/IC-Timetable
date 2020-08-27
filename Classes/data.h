#ifndef _DATA_H
#define _DATA_H

#include "dependencies.h"

#include "read.h"

class Data{

    public:
        vector <Teacher*> teachers;
        vector <Discipline*> disciplines;
        vector <Room*> rooms;

        vector <Room*> sala;
        vector <Room*> lab;
        vector <Room*> info;

        vector <Course*> courses;
        vector <Grade*> grades;

        int teacherSize;
        int discSize;
        int roomSize;
        int courseSize;
        int gradeSize;

        int days;
        int timeSlots;

        //void print(); //Debuga o programa

        void read();
        void classifyRoom();
        void discToTeacher();
        void discToGrade();
        void roomToClass();
};

#endif