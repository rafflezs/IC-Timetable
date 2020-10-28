#ifndef _PROFESSOR_H
#define _PROFESSOR_H

#include "disciplina.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class Professor{
    public:

        std::vector <Disciplina*> listaDiscs;

        int index;
        std::string nome;
        std::string id; //ID unico relativo ao valor usado pela instituição
        int disponibilidade[6][16]; //Matriz de horarios factíveis (diaXhorario)

        /* 
        *  Função simples, inviabilizando arquivo.cpp
        *  Imprime os dados primitivos do objeto
        *  @param NULL @return NULL
        */
        void print(){
            std::cout << "Nome: " << nome << "\nID: " << id << std::endl;
            if(index > 0)
                for(int dia = 0; dia < 6; dia++){
                    for(int horario = 0; horario < 16; horario++){
                        std::cout << std::setw(5) << disponibilidade[dia][horario];
                    }std::cout << std::endl;
                }std::cout << std::endl;
        };
};

#endif //_PROFESSOR_H