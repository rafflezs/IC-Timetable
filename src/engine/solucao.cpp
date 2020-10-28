#include "solucao.hpp"

Solucao::Solucao(){

    Data data;

    data.lerDados();

    for(auto temp = data.turmas.begin(); temp != data.turmas.end(); temp++){

        Agenda* a = new Agenda();        

    }

}

Sala* Solucao::selecionaSala(DiscSolucao* disciplina, Data* data){

}

Sala* Solucao::selecionaSala(Turma* turma, Data* data){
    
}

int calcFuncObjetivo(Data* data){

}

int calcJanela(Agenda* professor){

}

int calcSextoHorario(Agenda* turma){

}

int calcDiasTrabalhados(Agenda* professor){

}