#ifndef _SALASOL_H
#define _SALASOL_H

#include "../io/data.hpp"
#include "agenda.hpp"

class SalaSol{
    public:
        Sala* sala;
        Agenda* agendaSala;
        bool usado = false;
    
        SalaSol(Sala* sala);
        void print();
};

#endif