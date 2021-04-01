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
        void inserirInicio( Solucao* sol, std::set <Disciplina*> listaDisc /* <- a lista é o parametro de caso  */);

        //inserirEspalhado( param )

        //troca duas disc (splits) de lugar
        Solucao* trocarDisciplinas(Solucao sol);
        
        //refaz o horario de uma turma aleatoriamente
        Solucao trocarHorario(Solucao sol);
        
        //pega uma disciplina de um sala e aloca em outra sala
        //void trocarSala( param );                 
        
        //
        //void trocarHorarioProfessor( param ); 
        
        //espalahar aulas de um professor -> função objetivo 

        void fixAndOptimize(Data* data);
        void printSolucoes();
        void geraListaDias(int listaDias[], int tam);
    
        std::set <Disciplina*> geraListaDisc(Solucao* sol, int parametro);
        list <SalaSol*> selecionaSala(Solucao* sol, Disciplina* disc, TurmaSol* turma, int* dia, int* horario, int* tamanho);

        void mostrarHorarios(list <int> listaHorarios, TurmaSol* turma);
};

#endif