#include "turmaSol.hpp"

TurmaSol::TurmaSol(Turma* turma){

    this->turma = turma;

    this->agendaTurma = new Agenda(turma);

}

void TurmaSol::print(){

    std::cout << "Turma: " << this->turma->nome << std::endl;

    agendaTurma->printAgenda();

}