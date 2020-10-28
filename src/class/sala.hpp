#ifndef _SALA_H
#define _SALA_H

#include <string>
#include <iostream>
#include <iomanip>

class Sala{
    public:
        int index;
        std::string nome;
        std::string id; //ID unico relativo ao valor usado pela instituição
        int capacidade;
        std::string bloco;
        std::string tipo; //Tipo de sala referente á "Sala de Aula", "Laboratorio" e "Informatica"
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

#endif //_SALA_H