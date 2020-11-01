#include "turmaSol.hpp"

TurmaSol::TurmaSol(Turma turma){

    this->turma = turma;

    this->agendaTurma = new Agenda(&turma);

}

void TurmaSol::exibeRecursos(){

    std::cout << "Turma: " << this->turma.nome << std::endl;

    agendaTurma->exibirAgenda();

}