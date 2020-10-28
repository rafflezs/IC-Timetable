#ifndef _DISCSOLUCAO_H
#define _DISCSOLUCAO_H

#include "../io/data.hpp"

#include <list>

class DiscSolucao{

    public:
        Turma* turma;
        Sala* lab;
        Disciplina* disciplina;
        /* 
        *  Obtem os horarios consecutivos de 
        *  @param int : diaDaAula @return list : horariosConsecutivos
        */
        DiscSolucao(Data* data, Disciplina* disciplina);

        Sala* selecionaSala(Disciplina* disciplina);

        /* 
        *  Exibe os recursos alocados na classe 
        *  @param NULL @return NULL
        */
        void exibeRecursos();

};

#endif