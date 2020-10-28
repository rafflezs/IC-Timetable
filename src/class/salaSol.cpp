#include "salaSol.hpp"

SalaSol::SalaSol(Sala* sala, Data* data, Agenda* agenda){

    this->sala = sala;
    this->agendaSala = agenda;

}

void SalaSol::exibeRecursos(){

    std::cout << "Nome: " << sala->nome << std::endl;

    agendaSala->exibirAgenda(agendaSala);

}