#ifndef _SALASOL_H
#define _SALASOL_H

#include "sala.hpp"
#include "data.hpp"
#include "agenda.hpp"

class SalaSol{
    public:
        Sala* sala;
        Agenda* agendaSala;

        SalaSol(Sala* sala, Data* data, Agenda* agenda);
        void exibeRecursos();
};

#endif