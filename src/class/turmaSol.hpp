#ifndef _TURMASOL_H
#define _TURMASOL_H

#include "discSolucao.hpp"
#include "agenda.hpp"

class TurmaSol{

    public:
        Turma* turma;
        std::list <DiscSolucao*> discLista;
        Sala* salaBase;
        Agenda* agendaTurma;

        TurmaSol(Turma* turma, Data* data, Agenda* agendaTurma);
        void exibeRecursos();

};

#endif