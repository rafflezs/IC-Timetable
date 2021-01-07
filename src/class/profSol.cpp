#include "profSol.hpp"

ProfSol::ProfSol(Professor* professor){

    this->professor = professor;

    this->agendaProf = new Agenda(professor);

}

void ProfSol::print(){

    std::cout << "ID: " << professor->id << " | Nome: " << professor->nome << std::endl;

    agendaProf->printAgenda();

}