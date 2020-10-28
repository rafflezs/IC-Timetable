#include "profSol.hpp"

ProfSol::ProfSol(Professor* professor, Agenda* agendaProf, Data* data){

    this->professor = professor;
    this->agendaProf = agendaProf;

}

void ProfSol::exibeRecursos(){

    std::cout << "Nome: " << professor->nome << std::endl;

    agendaProf->exibirAgenda(agendaProf);

}