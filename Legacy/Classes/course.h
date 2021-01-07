#ifndef _COURSE_H
#define _COURSE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <fstream>

using namespace std;

class Course{

    public:
        int id;
        string id_if;
        string name;
        string dayTime;
        string degree;
        string grades;

        int disponibility[6][16];
};

#endif
