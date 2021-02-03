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

//Devolve uma lista de horarios consecutivos
//Possivelmente o problema esta aqui nessa função ou na debaixo
std::list <int> Agenda::checarConsecutivo( Disciplina* disc, int dia, int tamanhoSplit, int discIndex ){

    int slotInicio, slotFim;

    if(disc->turno == "Manhã"){
        slotInicio = 0;
        slotFim = 5;
    }else if(disc->turno == "Tarde"){
        slotInicio = 6;
        slotFim = 11;
    }else{
        slotInicio = 12;
        if(dia == 6)
            slotInicio = 0;
        slotFim = 15;
    }

    std::list <int> listaHorarios;

    for(; slotInicio <= slotFim - (tamanhoSplit-1); slotInicio++){
        
        int flag = 0;

        for(int i = slotInicio; i <= slotFim; i++){
            if(this->agenda[dia][i] != 0){
                flag = 1;
                break;
            }
        }

        if(flag == 0){
           listaHorarios.push_back(slotInicio);
       }
    }

    return listaHorarios;

}

bool Agenda::checarConsecutivo(int dia, int horarioInicial, int tamSplit, int discIndex){

    for(int i = horarioInicial; i < horarioInicial + tamSplit; i++){

        if(agenda[dia][i] != discIndex){
            return false;
        }

    }

    return true;

}

//Checa a disponibilidade de um horario para a alocação de um recurso
/* bool Agenda::checarDisponibilidade( int dia, int inicio, int fim, int discIndex, std::set <int> *listaHorarios ){

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

} */

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