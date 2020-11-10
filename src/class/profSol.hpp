#ifndef _PROFSOL_H
#define _PROFSOL_H

#include "agenda.hpp"

class ProfSol{
    public:
        Professor* professor;
        Agenda* agendaProf;

        ProfSol(Professor* professor);
        void print();
};

#endif