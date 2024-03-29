#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "../class/discSol.hpp"
#include "../class/turmaSol.hpp"
#include "../class/profSol.hpp"
#include "../class/salaSol.hpp"

#include <set>

class Solucao{
    public:

        Data* data;

        set <Sala*> tabuManha, tabuTarde, tabuNoite;

        int FuncObjetivo;
        int janelaHorario;
        int diasTrabalhados;
        int sextoHorario;

        std::map <Disciplina*, DiscSol*> discSol;
        std::map <Turma*, TurmaSol*> horarioTurma;
        std::map <Professor*, ProfSol*> horarioProf;
        std::map <Sala*, SalaSol*> horarioSala;

        Solucao();

        int calcFuncObjetivo(Data* data);
        int calcJanela(Agenda* professor);
        int calcSextoHorario(Agenda* turma);
        int calcDiasTrabalhados(Agenda* professor);

        void selecionaSala(DiscSol* disciplina, Data* data);
        void print();
};

#endif
