#ifndef _HORARIO_HPP
#define _HORARIO_HPP

#include "../class/sala.hpp"
#include "../class/professor.hpp"
#include "../class/turma.hpp"

#include <iostream>
#include <set>
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
        *  Obtem lista de horarios consecutivos em determinado dia 
        *  @param int* @return list
        */
        std::list <int> checarConsecutivo(int dia, int tamanhoSplit, int discIndex);

        bool checarConsecutivo(int dia, int horarioInicial, int tamSplit, int discIndex);

        /* 
        *  Checa a disponibilidade (consecutividade) em determinado intervalo
        *  @param int*, int*, int* @return bool
        */
        bool checarDisponibilidade(int dia, int inicio, int fim, int discIndex, std::set <int> *listaHorarios);
};

#endif //!_HORARIO_HPP