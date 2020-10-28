#ifndef _HORARIO_HPP
#define _HORARIO_HPP

#include "../class/sala.hpp"
#include "../class/professor.hpp"
#include "../class/turma.hpp"

#include <iostream>
#include <list>

class Agenda{
    public:
        int agenda[6][16];
        
        Sala* recursoSala = NULL;
        Turma* recursoTurma = NULL;
        Professor* recursoProfessor = NULL;

        Agenda(Turma* recursoTurma);
        Agenda(Sala*);
        Agenda(Professor*);

        /* 
        *  Exibe matriz de horarios para determinado recurso 
        *  @param templateClass @return NULL
        */
        template <class genericClass> void exibirAgenda(genericClass recurso);
        
        /* 
        *  Checa a disponibilidade (consecutividade) em determinado intervalo
        *  @param int*, int*, int* @return bool
        */
        bool checarDisponibilidade(int* dia, int* inicio, int* fim);

        /* 
        *  Obtem lista de horarios consecutivos em determinado dia 
        *  @param int* @return list
        */
        std::list <int> checarConsecutivo(int* dia);
};

#endif //!_HORARIO_HPP