#include "discSol.hpp"

DiscSol::DiscSol(Data* data, Disciplina* disciplina){

    this->disciplina = disciplina;
    this->turma = data->turmas[disciplina->turmaIndex];

}

void DiscSol::print(){

    std::cout << "Nome: " << disciplina->nome << "\nID: " << disciplina->index << std::endl;

}