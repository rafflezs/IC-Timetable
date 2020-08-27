#ifndef _CLASS_H
#define _CLASS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "course.h"
#include "room.h"

class Grade{
    
    public:
        int id;
        std::string id_if;
        std::string name;
        std::string dayTime;
        
        vector <string> disciplinesId;

        Course* course;
        Room* room;

        int disponibility[6][16];

};

#endif