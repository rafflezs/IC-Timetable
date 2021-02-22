#ifndef _METAHEURISTICA_H
#define _METAHEURISTICA_H

#include "solucao.hpp"

#include <algorithm>
#include <random>
#include <cmath>

class Metaheuristica{
    public:
        vector <Solucao> solucoes;
    
        Metaheuristica();
    
        //algoritmoGenerico(Data* data);
        void inserirInicio( Solucao* sol, std::vector <Disciplina*> listaDisc);
        Solucao* trocarDisciplinas(Solucao sol);
        void trocarHorario(Data* data);             // Essas três //
        void trocarTurma(Data* data);               // funções estão
        //void trocarSala( param );                 // atreladas ///
        void fixAndOptimize(Data* data);
        void printSolucoes();
        void geraListaDias(int listaDias[], int tam);
    
        std::vector <Disciplina*> geraListaDisc(Solucao* sol);
        list <SalaSol*> selecionaSala(Solucao* sol, Disciplina* disc, TurmaSol* turma, int* dia, int* horario, int* tamanho);
};

#endif