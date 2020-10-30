#include "profSol.hpp"

ProfSol::ProfSol(Professor professor){

    this->professor = professor;

    Agenda* agenda = new Agenda(&professor);

    this->agendaProf = agenda;

}

void ProfSol::exibeRecursos(){

    std::cout << "Nome: " << professor.nome << std::endl;

    agendaProf->exibirAgenda();

}