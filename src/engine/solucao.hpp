#ifndef _SOLUCAO_HPP
#define _SOLUCAO_HPP

#include "../class/agenda.hpp"
#include "../class/discSolucao.hpp"

class Solucao{
    public:

        int FuncObjetivo;
        int janelaHorario;
        int diasTrabalhados;
        int sextoHorario;
        std::map <Turma, Agenda> agendaTurmas;
        std::map <Sala, Agenda> agendaSalas;
        std::map <Professor, Agenda> agendaProfessores;
        std::map <Disciplina*, DiscSolucao> disc;
        std::map <Turma*, Turma> turma;

        Solucao();

        int calcFuncObjetivo(Data* data);
        int calcJanela(Agenda* professor);
        int calcSextoHorario(Agenda* turma);
        int calcDiasTrabalhados(Agenda* professor);

        Sala* selecionaSala(DiscSolucao* disciplina, Data* data);
        Sala* selecionaSala(Turma* turma, Data* data);
};

#endif
