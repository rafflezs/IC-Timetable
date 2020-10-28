#ifndef _DISCIPLINA_H
#define _DISCIPLINA_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>


class Disciplina{
    public:
        int TurmaIndex;
        std::vector <int> ProfessorIndex;

        int index;
        std::string nome;
        std::string id; //ID unico relativo ao valor usado pela instituição
        int cargaHoraria;
        int minimoDiario;
        int splits;
        int capacidadeTurma;
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

#endif //_DISCIPLINA_H