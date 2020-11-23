#ifndef _CURSO_H
#define _CURSO_H

#include <string>
#include <iostream>
#include <iomanip>

class Curso{
    public:
        int index;
        std::string nome;
        std::string id; //ID unico relativo ao valor usado pela instituição
        std::string turno; //Turno relativo à "Manhã", "Tarde" e "Noite"
        std::string grauDeFormacao; //Relativo a "Bacharel", "Licenciatura", "Tecnico"

        int disponibilidade[6][16]; //Matriz de horarios factíveis (diaXhorario)

        /* 
        *  Função simples, inviabilizando arquivo.cpp
        *  Imprime os dados primitivos do objeto
        *  @param NULL @return NULL
        */
        void print(){
            std::cout << "ID: " << this->id << std::endl;
            std::cout << "Nome: " << this->nome << std::endl;
        };
};

#endif //_CURSO_H