#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){

    Solucao* sol = new Solucao();

    solucoes.push_back(sol);

    for( int i = 0; i < 1; i++ ){
        
        srand( time( 0 ) );

        auto listaDisc = geraListaDisc(sol);

        Solucao* temp = inserirInicio( sol, listaDisc );
        solucoes.push_back(temp);
        //std::cout << "Função objetivo: " << temp->calcFuncObjetivo(sol->data) << std::endl;
        
    }

    printSolucoes();

}

Solucao* Metaheuristica::inserirInicio( Solucao* sol, std::vector <Disciplina*> listaDisc ){

    Solucao* temp = new Solucao();

    /*  Loop de disciplinas em ordem randomica (ver geraListaDisc) */
    for( auto d = listaDisc.begin(); d != listaDisc.end(); d++ ){

        auto disc = sol->discSol.find( *d );

        cout << "\n-----------------------------------------------------------------\n";
        cout << "Disciplina: " << disc->first->id << " | " << disc->first->nome << endl;

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
        list <ProfSol*> prof;

        for(int i = 0; i < disc->first->professorIndex.size(); i++){
            prof.push_back(sol->horarioProf.find( sol->data->professores[disc->first->professorIndex[i]] )->second);
        }

        //Lista de dias randomizados
        int listaDias[6] = {0,1,2,3,4,5};
        geraListaDias(listaDias, 6);

        list <SalaSol*> sala;
        if(disc->first->tipoSala != "Sala"){
            sala = selecionaSala(sol, disc->first);
        }

        for(int s = 0, dia = 0; s < splits; s++, dia++){
            horariosConsec = turma->second->agendaTurma->checarConsecutivo(listaDias[dia], tamanhoSplit[s], 0);

            while ( !horariosConsec.empty() ){
                int flag = 0;

                for(auto p = prof.begin(); p != prof.end(); p++){
                    if(!(*p)->agendaProf->checarConsecutivo(listaDias[dia], (horariosConsec.front()), tamanhoSplit[s], 0)){
                        flag = 1;
                        break;
                    }
                }
            
                if(!sala.front()->agendaSala->checarConsecutivo(listaDias[dia], (horariosConsec.front()), tamanhoSplit[s], 0)){
                    sala.pop_front();
                }

                if(flag == 1){
                    horariosConsec.pop_front();
                    break;
                }

                for(auto p = prof.begin(); p != prof.end(); p++){
                    for(int slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                        (*p)->agendaProf->agenda[listaDias[dia]][slot] = disc->first->index;
                    }
                }
            
                for(int slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                    turma->second->agendaTurma->agenda[listaDias[dia]][slot] = disc->first->index;
                        sol->horarioSala.find(turma->second->salaBase)->second->agendaSala->agenda[listaDias[dia]][slot] = disc->first->index;
                        if(disc->first->tipoSala != "Sala")
                            sala.front()->agendaSala->agenda[listaDias[dia]][slot] = disc->first->index;
                }

            }
            

        }

    } //!for (disc)
    return temp;
} //!_inserirInicio()


void Metaheuristica::printSolucoes(){

    for(int i = 0; i < solucoes.size(); i++){
        
        cout << "\n\nSolução [" << i << "]" << "\n" << endl;
        
        for( auto turma = solucoes[i]->horarioTurma.begin(); turma != solucoes[i]->horarioTurma.end(); turma++){
            turma->second->print();
        }
        //for( auto prof = solucoes[i]->horarioProf.begin(); prof != solucoes[i]->horarioProf.end(); prof++){
        //    prof->second->print();
        //}

    }
} //!_printSolucoes()

list <SalaSol*> Metaheuristica::selecionaSala(Solucao* sol, Disciplina* disc){

    list <SalaSol*> listaSalas;

    for( auto temp = sol->horarioSala.begin(); temp != sol->horarioSala.end(); temp++ ){

        if( disc->tipoSala == (*temp).first->tipo ){
            listaSalas.push_back((*temp).second);
        }

    }

    return listaSalas;

}

void Metaheuristica::geraListaDias(int listaDias[], int tam){

    shuffle( listaDias, listaDias + tam, default_random_engine( 0 ) );

}

std::vector <Disciplina*> Metaheuristica::geraListaDisc(Solucao* sol){

    vector <int> discIndex;

    for(int it = 1; it < sol->data->disciplinas.size(); it++){
        discIndex.push_back(it);
    }

    random_shuffle( discIndex.begin(), discIndex.end() ); 

    std::vector <Disciplina*> listaDisc;

    for(auto it = discIndex.begin(); it != discIndex.end(); it++){

        /* cout << (*it) << " " << endl; */

        listaDisc.push_back( sol->data->disciplinas[(*it)] );
        /* cout << "Disc: " << sol->data->disciplinas[(*it)]->nome << endl; */

    }

    return listaDisc;

}
