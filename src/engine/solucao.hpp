#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "../class/agenda.hpp"
#include "../class/discSolucao.hpp"
#include "../class/turmaSol.hpp"
#include "../class/profSol.hpp"
#include "../class/salaSol.hpp"

#include <set>

class Solucao{
    public:

        int FuncObjetivo;
        int janelaHorario;
        int diasTrabalhados;
        int sextoHorario;

        std::map <Disciplina*, DiscSolucao*> discSol;
        
        std::map <Turma, TurmaSol*> horarioTurma;
        std::map <Professor, ProfSol*> horarioProf;
        std::map <Sala, SalaSol*> horarioSala;

        Solucao();

        int calcFuncObjetivo(Data* data);
        int calcJanela(Agenda* professor);
        int calcSextoHorario(Agenda* turma);
        int calcDiasTrabalhados(Agenda* professor);

        Sala* selecionaSala(DiscSolucao* disciplina, Data* data);
        void selecionaSala(Turma* turma, Data* data);
};

#endif
