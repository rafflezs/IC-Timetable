#ifndef _METAHEURISTICA_H
#define _METAHEURISTICA_H

#include "data.hpp"
#include "solucao.hpp"

class Metaheuristica{
    public:
        vector <Solucao> solucoes;

        //algoritmoGenerico(Data* dados);
        bool inserirInicio(Data* dados);
        bool trocarHorario(Data* dados);
        bool trocarTurma(Data* dados);
        bool fixAndOptimize(Data* dados);
        //void exportarSaida( /* melhorSol */ );
};

#endif