#ifndef _PROFSOL_H
#define _PROFSOL_H

#include "professor.hpp"
#include "data.hpp"
#include "agenda.hpp"

class ProfSol{
    public:
        Professor* professor;
        Agenda* agendaProf;

        ProfSol(Professor* professor, Agenda* agendaProf, Data* data);
        void exibeRecursos();
};

#endif