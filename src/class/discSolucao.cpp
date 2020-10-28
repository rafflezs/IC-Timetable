#include "discSolucao.hpp"

DiscSolucao::DiscSolucao(Data* data, Disciplina* disciplina){

    this->disciplina = disciplina;
    this->turma = &(data->turmas[disciplina->TurmaIndex]);

}

void DiscSolucao::exibeRecursos(){

    std::cout << "Nome: " << this->disciplina->nome << "\nID: " << this->disciplina->index << std::endl;

}