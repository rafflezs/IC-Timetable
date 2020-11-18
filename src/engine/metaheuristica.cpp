#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){

    Data* data = new Data();
    Solucao* sol = new Solucao();

    solucoes.push_back(sol);

    for( int i = 0; i < 1; i++ ){

        Solucao* temp = inserirInicio(data);
        solucoes.push_back(temp);
    }

    //printSolucoes();

}

Solucao* Metaheuristica::inserirInicio(Data* data){

    Solucao* sol = new Solucao();

    //Pega as disciplinas em ordem de leitura
    for( auto disc = sol->discSol.begin(); disc != sol->discSol.end() ; disc++ ){
        
        //Pega o mapa da turma associada a disciplina
        auto turma = sol->horarioTurma.find(disc->second->turma);

        //Gera variaveis necessarias para parametrizar a agenda de Disciplinas
        int splits = disc->first->splits;
        int cargaHoraria = disc->first->cargaHoraria;
        int minimoDiario = disc->first->minimoDiario;
        int tamanhoSplit[splits];
        
        //Gera vetor com o tamanho de cada split (mesma tecnica do Legacy)
        
        for(int i = 0; i < splits; i++){
            tamanhoSplit[i] = minimoDiario;
        }
        for(int i = 0; i < cargaHoraria % (minimoDiario * splits); i++){
            tamanhoSplit[i % splits]++;
        }
        
        //Lista de dias consecutivos com o tamanho de determinado split
        set <int> horariosConsec;
        
        //Lista de dias desconsiderados na busca
        set <int> diaTabu;


        for( int qtdSplit = 0; qtdSplit < splits; qtdSplit++ ){
        
        do
        {
            int dia = rand() % 6;
 
            if( diaTabu.count(dia) == false ){

                    horariosConsec = turma->second->agendaTurma->checarConsecutivo( dia, tamanhoSplit[qtdSplit], 0 );
                


                for(auto slot = horariosConsec.begin(); slot != horariosConsec.end(); slot++){
                    turma->second->agendaTurma->agenda[dia][*slot] = disc->first->index;
                }

                cout << disc->first->nome;
                cout << "\n" << disc->second->turma->nome << "\n";
                turma->second->agendaTurma->printAgenda();

                std::getchar();

                diaTabu.insert(dia);
            }
    
        } while (horariosConsec.size() == 0);
        }

    }

    return sol;
    
}

void Metaheuristica::printSolucoes(){

    for(int i = 0; i < solucoes.size(); i++){
        
        cout << "\n\nSolução [" << i << "]" << "\n" << endl;
        
        for( auto turma = solucoes[i]->horarioTurma.begin(); turma != solucoes[i]->horarioTurma.end(); turma++){
            turma->second->print();
        }

    }
}