#include "solucao.hpp"

Solucao::Solucao(){

    Data* data = new Data();

    data->lerDados();

    for(int index = 1; index < data->professores.size(); index++){
        ProfSol* prof = new ProfSol(data->professores[index]);
        this->horarioProf.insert( pair <Professor*, ProfSol*>(data->professores[index], prof) );         
    }

    for(int index = 1; index < data->salas.size(); index++){
        SalaSol* sala = new SalaSol(data->salas[index]);
        this->horarioSala.insert( pair <Sala*, SalaSol*>(data->salas[index], sala) );        
    }

    for(int index = 1; index < data->turmas.size(); index++){
        TurmaSol* turma = new TurmaSol(data->turmas[index]);
        turma->salaBase = selecionaSala(data, turma);
        horarioTurma.insert( pair<Turma*, TurmaSol*> (data->turmas[index], turma) );
    }

    for(int index = 1; index < data->turmas.size(); index++){
        DiscSol* disc = new DiscSol(data, data->disciplinas[index]);
        discSol.insert( pair<Disciplina*, DiscSol*> (data->disciplinas[index], disc) );
    }
}

/* Sala* Solucao::selecionaSala(DiscSol* disciplina, Data* data){

} */

Sala* Solucao::selecionaSala(Data* data, TurmaSol* turma){
    //O problema tá aqui nesse IF

        for(int i = 1; i < data->salas.size(); i++){
            if(turma->turma->turno == "Manhã" && !(tabuManha.count(data->salas[i]))){
                tabuManha.insert(data->salas[i]);
                return data->salas[i];
            }
            if(turma->turma->turno == "Tarde" && !(tabuTarde.count(data->salas[i]))){
                tabuTarde.insert(data->salas[i]);
                return data->salas[i];
            }
            if(turma->turma->turno == "Noite" && !(tabuNoite.count(data->salas[i]))){
                tabuNoite.insert(data->salas[i]);
                return data->salas[i];
            }
        }

    return data->salas[0];

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