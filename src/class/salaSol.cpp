#include "salaSol.hpp"

SalaSol::SalaSol(Sala sala){

    this->sala = sala;

    Agenda* agenda = new Agenda(&sala);

    this->agendaSala = agenda;
}

void SalaSol::exibeRecursos(){

    std::cout << "Nome: " << sala.nome << std::endl;

    agendaSala->exibirAgenda();

}