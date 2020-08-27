#ifndef _ROOM_H
#define _ROOM_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Room{

    public:
        int id;
        std::string id_if;
        std::string name;
        std::string type;
        int capacity;
        std::string block;
        int disponibility[6][16];
        bool isUsed[3];
        int gradeId;

};

#endif