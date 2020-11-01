#ifndef _TURMASOL_H
#define _TURMASOL_H

#include "discSol.hpp"
#include "agenda.hpp"

class TurmaSol{

    public:
        Turma turma;
        std::list <DiscSol*> discLista;
        Sala* salaBase;
        Agenda* agendaTurma;

        TurmaSol(Turma turma);
        void exibeRecursos();

};

#endif