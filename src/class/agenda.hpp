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

        std::string idRecurso;
        std::string nome;

        Agenda(Turma* );
        Agenda(Sala* );
        Agenda(Professor*);

        /* 
        *  Exibe matriz de horarios para determinado recurso 
        *  @param NULL @return NULL
        */
        void printAgenda();

        /* 
        *  Checa a disponibilidade (consecutividade) em determinado intervalo
        *  @param int*, int*, int* @return bool
        */
        bool checarDisponibilidade(int* dia, int* inicio, int* fim);

        /* 
        *  Obtem lista de horarios consecutivos em determinado dia 
        *  @param int* @return list
        */
        std::list <int> checarConsecutivo(int* dia, int* tamanhoSplit);
};

#endif //!_HORARIO_HPP