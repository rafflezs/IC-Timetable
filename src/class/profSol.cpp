#include "profSol.hpp"

ProfSol::ProfSol(Professor professor){

    this->professor = professor;

    this->agendaProf = new Agenda(&professor);

}

void ProfSol::exibeRecursos(){

    std::cout << "Nome: " << professor.nome << std::endl;

    agendaProf->exibirAgenda();

}