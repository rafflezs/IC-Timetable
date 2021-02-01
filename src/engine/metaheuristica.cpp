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

        cout << "\nDisciplina passando pela heuristica construtiva\n";
        cout << "Disciplina: " << disc->first->id << " | " << disc->first->nome << " | ";

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
            cout << "Nome do corno " << prof.front()->professor->nome << endl;
        }

        //Lista de dias randomizados
        int listaDias[6] = {0,1,2,3,4,5};
        geraListaDias(listaDias, 6);

        for(int s = 0, dia = 0; s < splits; s++){

            horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s],disc->first->index);

            if(dia > 6){
                dia = 0;
            }

            while(horariosConsec.empty()) {
                dia++;
                horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s],disc->first->index);
            };

            while ( !horariosConsec.empty() ){
                int flag = 0;
                
                for(auto p = prof.begin(); p != prof.end(); p++){
                    if(!(*p)->agendaProf->checarConsecutivo(listaDias[dia], horariosConsec.front(), tamanhoSplit[s], 0)){
                        flag = 1;
                        break;
                    }
                }

                if(flag == 1){
                    horariosConsec.pop_front();
                    break;
                }

                for(auto p = prof.begin(); p != prof.end(); p++){
                    for(auto slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                        (*p)->agendaProf->agenda[listaDias[dia]][slot] = disc->first->index;
                    }
                    (*p)->agendaProf->printAgenda();
                }

                for(auto slot = horariosConsec.front(); tamanhoSplit[s] > 0; slot++, tamanhoSplit[s]--){
                    turma->second->agendaTurma->agenda[listaDias[dia]][slot] = disc->first->index;
                    //getchar();
                }
                turma->second->agendaTurma->printAgenda();

                horariosConsec.clear();

            } //!_while (!empty)

            dia++;

        } //!_for(int s)

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

/* SalaSol* Metaheuristica::selecionaSala(Solucao* sol, Disciplina* disc, list <int> horariosConsec){

    SalaSol* sala;

    for( auto temp = sol->horarioSala.begin(); temp != sol->horarioSala.end(); temp++ ){

        if(temp->first->tipo == disc->tipoSala){
            sala = (*temp).second;
        }
    }

    return sala;

} */

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
