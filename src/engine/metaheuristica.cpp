#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){

    Data* data = new Data();
    Solucao* sol = new Solucao();

    solucoes.push_back(sol);

    delete sol;

/*     for( int i = 0; i < 9; i++ ){

        Solucao* temp = inserirInicio(data, sol );
        solucoes.push_back(temp);
        delete temp;
    } */

    //printSolucoes();

}

Solucao* Metaheuristica::inserirInicio(Data* data, Solucao* sol){



    //Pega as disciplinas em ordem de leitura
    for(auto disc = sol->discSol.begin(); disc != sol->discSol.end(); disc++){
        
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
        list <int> horariosConsec;
        
        //Lista de dias desconsiderados na busca
        set <int> diaTabu;
        
        /* do{
            int dia = rand() % 6;
            if(!(diaTabu.count(dia))){
                //Procura por horarios consecutivos em determinado dia (tamanho do split)
                for(int i = 0; i < tamanhoSplit[i]; i++){
                    horariosConsec = turma->second->agendaTurma->checarConsecutivo(&dia, &tamanhoSplit[i]);
                    for(auto j = horariosConsec.begin(); j != horariosConsec.end(); j++){
                        turma->second->agendaTurma->agenda[dia][*j] = disc->first->index;
                    }
                }
            }
        
            diaTabu.insert(dia);
        
        }while(diaTabu.size() < 6); */
    }

    return sol;

}

void Metaheuristica::printSolucoes(){

    for(int i = 0; i < solucoes.size(); i++){
        
        cout << "\n\nSolução [" << i << "]" << "\n" << endl;
        
        for(auto temp = solucoes[i]->discSol.begin(); temp != solucoes[i]->discSol.end(); temp++){
            //temp->second->agendaTurma->printAgenda();
            
            for( auto prof = temp->first->professorIndex.begin(); prof != temp->first->professorIndex.end(); prof++ ){
                cout << (*prof) << endl;
            }
        }
    }

}