#ifndef _METAHEURISTICA_H
#define _METAHEURISTICA_H

#include "solucao.hpp"

class Metaheuristica{
    public:
        vector <Solucao*> solucoes;

        Metaheuristica();

        //algoritmoGenerico(Data* data);
        Solucao* inserirInicio(Data* data);
        bool trocarHorario(Data* data);
        bool trocarTurma(Data* data);
        bool fixAndOptimize(Data* data);
        void printSolucoes();
};

#endif