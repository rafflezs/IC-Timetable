#include "agenda.hpp"

Agenda::Agenda(Turma* recursoTurma){


    /* this->recursoTurma = recursoTurma; */

    this->idRecurso = recursoTurma->id;
    this->nome = recursoTurma->nome;

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            this->agenda[dia][horario] = recursoTurma->disponibilidade[dia][horario];
        }
    }
}

Agenda::Agenda(Sala* recursoSala){
    
/*     this->recursoSala = recursoSala; */

    this->idRecurso = recursoSala->id;
    this->nome = recursoSala->nome;

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            this->agenda[dia][horario] = recursoSala->disponibilidade[dia][horario];
        }
    }
}

Agenda::Agenda(Professor* recursoProfessor){
    
/*     this->recursoProfessor = recursoProfessor; */

    this->idRecurso = recursoProfessor->id;
    this->nome = recursoProfessor->nome;

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            this->agenda[dia][horario] = recursoProfessor->disponibilidade[dia][horario];
        }
    }
}

/* template <class genericClass> void Agenda::exibirAgenda(genericClass recurso){

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            std::cout << "Nome : " << recurso.nome << "ID: " << recurso.id << std::endl;
            std::cout << std::setw(5) << this->agenda[dia][horario];
        }
    }    
} */

//Devolve uma lista de horarios consecutivos
std::set <int> Agenda::checarConsecutivo( int dia, int tamanhoSplit, int discIndex ){

    std::set <int> listaHorarios;

    for(int slot = 0; slot < 16; slot++){
        if( agenda[dia][slot] == discIndex ){

            if( checarDisponibilidade( dia, slot, (slot + tamanhoSplit), discIndex, &listaHorarios ) ){
                return listaHorarios;
            }

        }
    }

    return listaHorarios;

}

bool checarConsecutivo(int dia, std::set <int> *listaHorarios, int discIndex){

}

//Checa a disponibilidade de um horario para a alocação de um recurso
bool Agenda::checarDisponibilidade( int dia, int inicio, int fim, int discIndex, std::set <int> *listaHorarios ){

    int flagIni = 0;
    int flagFim = fim - inicio - 1;

    for(int slot = inicio; slot < fim; slot++){
        if(( agenda[dia][slot] == discIndex ) && ( agenda[dia][slot - flagIni] == discIndex ) && ( agenda[dia][slot + flagFim] == discIndex ) ){
            (*listaHorarios).insert(slot);
            flagFim--;
            flagIni++;
        }
    }

    if((*listaHorarios).size() == (fim - inicio)){
        return true;
    }

    return false;

}

//Exibe a matriz agenda do recurso, juntamente do nome (função generica)
void Agenda::printAgenda(){

    std::cout << this->nome << std::endl;

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            std::cout << std::setw(5) << this->agenda[dia][horario];
        }
        std::cout << std::endl;
    } 

}