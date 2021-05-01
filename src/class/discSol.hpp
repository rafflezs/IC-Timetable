#ifndef _DISCSOL_H
#define _DISCSOL_H

#include "../io/data.hpp"
#include "../class/salaSol.hpp"

#include <list>

class DiscSol{

    public:
        Turma* turma;
        vector <SalaSol*> sala;
        vector <SalaSol*> lab;
        Disciplina* disciplina;
        std::vector <Professor*> profLista;
        
        int aulasRestantes;

        /* 
        *  Obtem os horarios consecutivos de 
        *  @param int : diaDaAula @return list : horariosConsecutivos
        */
        DiscSol(Data* data, Disciplina* disciplina);
        
        /* 
        *  Exibe os recursos alocados na classe 
        *  @param NULL @return NULL
        */
        void print();
};

#endif