#include "turmaSol.hpp"

TurmaSol::TurmaSol(Turma temp){

    this->turma = temp;

    Agenda* agenda = new Agenda(&temp);

    this->agendaTurma = agenda;

}

void TurmaSol::exibeRecursos(){

    std::cout << "Turma: " << this->turma.nome << std::endl;

    agendaTurma->exibirAgenda();

}