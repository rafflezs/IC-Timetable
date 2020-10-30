#include "solucao.hpp"

Solucao::Solucao(){

    Data data;

    data.lerDados();

    for(int index = 1; index < data.turmas.size(); index++){
        
        TurmaSol* temp = new TurmaSol(data.turmas[index]);

        this->horarioTurma.insert( pair <Turma, TurmaSol*>(data.turmas[index], temp) );        
    }

    for(int index = 1; index < data.professores.size(); index++){
        
        ProfSol* temp = new ProfSol(data.professores[index]);

        this->horarioProf.insert( pair <Professor, ProfSol*>(data.professores[index], temp) );         
    }

    for(int index = 1; index < data.salas.size(); index++){
        
        SalaSol* temp = new SalaSol(data.salas[index]);

        this->horarioSala.insert( pair <Sala, SalaSol*>(data.salas[index], temp) );        
    }

}

/* Sala* Solucao::selecionaSala(DiscSolucao* disciplina, Data* data){

} */

void Solucao::selecionaSala(Turma* turma, Data* data){
    
    set <Sala> tabuManha, tabuTarde, tabuNoite;


    //O problema tá aqui nesse IF

    for(auto tempTurma = horarioTurma.begin(); tempTurma != horarioTurma.end(); tempTurma++){
        for(auto tempSala = horarioSala.begin(); tempSala != horarioSala.end(); tempSala++){
            if(tempTurma->first.turno == "Manhã" && !(tabuManha.count( (*tempSala).first ))){
                Sala satanas = (*tempSala).first;
                (*tempTurma).second->salaBase = satanas;
                tabuManha.insert(satanas);
            }
        }
    }

}

/*
int calcFuncObjetivo(Data* data){

}

int calcJanela(Agenda* professor){

}

int calcSextoHorario(Agenda* turma){

}

int calcDiasTrabalhados(Agenda* professor){

} */