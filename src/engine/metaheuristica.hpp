#ifndef _METAHEURISTICA_H
#define _METAHEURISTICA_H

#include "solucao.hpp"

#include <algorithm>
#include <random>
#include <ctime>

class Metaheuristica{
    public:
        vector <Solucao*> solucoes;

        Metaheuristica();

        //algoritmoGenerico(Data* data);
        Solucao* inserirInicio( Solucao* sol, std::vector <Disciplina*> listaDisc);
        bool trocarHorario(Data* data);
        bool trocarTurma(Data* data);
        bool fixAndOptimize(Data* data);
        void printSolucoes();

        void geraListaDias(int listaDias[], int tam);

        std::vector <Disciplina*> geraListaDisc(Solucao* sol);

        SalaSol* selecionaSala(Solucao* sol, Disciplina* disc, list <int> horariosConsec);
};

#endif