#ifndef _DISCSOL_H
#define _DISCSOL_H

#include "../io/data.hpp"

#include <list>

class DiscSol{

    public:
        Turma* turma;
        Sala* lab;
        Disciplina* disciplina;
        std::vector <Professor*> profLista;
        
        /* 
        *  Obtem os horarios consecutivos de 
        *  @param int : diaDaAula @return list : horariosConsecutivos
        */
        DiscSol(Data* data, Disciplina* disciplina);
        
        Sala* selecionaSala(Disciplina* disciplina);
        
        /* 
        *  Exibe os recursos alocados na classe 
        *  @param NULL @return NULL
        */
        void print();
        std::list <SalaSol*> listaSalas;
};

#endif