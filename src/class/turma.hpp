#ifndef _TURMA_H
#define _TURMA_H

#include "curso.hpp"
#include "disciplina.hpp"
#include "professor.hpp"

#include <string>
#include <vector>
#include <iomanip>

class Turma{
    public:
        Curso* curso;
        std::vector <Disciplina*> listaDiscs;
        std::vector <Professor*> listaProfs;

        int index;
        std::string nome;
        std::string id; //ID unico relativo ao valor usado pela instituição
        std::string turno; //Turno relativo à "Manhã", "Tarde" e "Noite"
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

#endif //_TURMA_H