#include "agenda.hpp"

Agenda::Agenda(Turma* recursoTurma){


    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            this->agenda[dia][horario] = recursoTurma->disponibilidade[dia][horario];
        }
    }
}

Agenda::Agenda(Sala* recursoSala){
    
    this->recursoSala = recursoSala;

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            this->agenda[dia][horario] = recursoSala->disponibilidade[dia][horario];
        }
    }
}

Agenda::Agenda(Professor* recursoProfessor){
    
    this->recursoProfessor = recursoProfessor;

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            this->agenda[dia][horario] = recursoProfessor->disponibilidade[dia][horario];
        }
    }
}

template <class genericClass> void Agenda::exibirAgenda(genericClass recurso){

    for(int dia = 0; dia < 6; dia++){
        for(int horario = 0; horario < 16; horario++){
            std::cout << "Nome : " << recurso.nome << "ID: " << recurso.id << std::endl;
            std::cout << std::setw(5) << this->agenda[dia][horario];
        }
    }    
}

bool Agenda::checarDisponibilidade(int* dia, int* inicio, int* fim){

    for(int horario = *inicio; horario < *fim; horario++){
        if(this->agenda[*dia][horario] != 0){
            return false;
        }
    }

    return true;
}

std::list <int> Agenda::checarConsecutivo(int* dia){

    std::list <int> listaHorarios;

    for(int horario = 0; horario < 16; horario++){
        if(checarDisponibilidade(dia, &horario, &horario+1)){
            listaHorarios.push_back(horario);
        }
    }

    return listaHorarios;
}