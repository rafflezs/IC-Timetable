#ifndef _TEACHER_H
#define _TEACHER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <fstream>

#include "discipline.h"

using namespace std;

class Teacher{

    public:
        int id;
        std::string id_if;
        std::string name;

        vector <Discipline*> disc;

        int disponibility[6][16];  

        void print();

};

#endif