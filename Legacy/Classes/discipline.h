#ifndef _DISCIPLINE_H
#define _DISCIPLINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "dependencies.h"

#include "room.h"

class Discipline{

    public:
        int id;
        std::string id_if;
        std::string name;
        int workload;
        int dailyMin;
        int splits;

        std::string teacherName;
        int teacherId;
        std::string courseName;
        std::string gradeName;
        int gradeId;
        std::string spcfRoom;
        int studentsLimit;
        std::string dayTime;

        std::set <Room*> possibleRoomList;

        int disponibility[6][16];

};

#endif