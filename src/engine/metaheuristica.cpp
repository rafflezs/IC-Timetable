#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){

    Data data;
    Solucao solucao = Solucao();
    solucoes.push_back(solucao);

    inserirInicio(&data);


    exibeSolucoes();
}

bool Metaheuristica::inserirInicio(Data* data){

    Solucao solucao = Solucao();

 

    solucoes.push_back(solucao);

    return false;

}

void Metaheuristica::exibeSolucoes(){

    for(int i = 0; i < solucoes.size(); i++){
        for(auto temp = solucoes[i].horarioTurma.begin(); temp != solucoes[i].horarioTurma.end(); temp++){
            temp->first->print();
        }
    }

}