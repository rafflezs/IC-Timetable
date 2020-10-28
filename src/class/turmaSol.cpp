#include "turmaSol.hpp"

TurmaSol::TurmaSol(Turma* turma, Data* data, Agenda* agendaTurma){

    this->turma = turma;
    this->agendaTurma = agendaTurma;
}

void TurmaSol::exibeRecursos(){

    std::cout << "Turma: " << this->turma->nome << std::endl;

    agendaTurma->exibirAgenda(agendaTurma);

}