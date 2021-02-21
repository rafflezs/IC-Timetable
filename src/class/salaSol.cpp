#include "salaSol.hpp"

SalaSol::SalaSol(Sala* sala){
    this->sala = sala;
    this->agendaSala = new Agenda(sala);
}

void SalaSol::print(){
    std::cout << "Nome: " << sala->nome << std::endl;
    agendaSala->printAgenda();
}