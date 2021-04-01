#include "discSol.hpp"

DiscSol::DiscSol(Data* data, Disciplina* disciplina){

    this->disciplina = disciplina;
    this->turma = data->turmas[disciplina->turmaIndex];

    for(auto profIndex = disciplina->professorIndex.begin(); profIndex != disciplina->professorIndex.end(); profIndex++){
        profLista.push_back(data->professores[*profIndex]);
    }

}

void DiscSol::print(){

    disciplina->print();

}