#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){
    
    for(int i = 0; i < 10; i++){
        Solucao sol = Solucao();
        solucoes.push_back(sol);
    }
    
    for( int i = 1; i < solucoes.size(); i++ ){
        auto listaDisc = geraListaDisc( &solucoes[i], rand() % 2);
        cout << "ListaDisc size(): " << listaDisc.size() << endl;
        cout << "Comecando inserirInicio" << endl;
        inserirInicio( &solucoes[i], listaDisc );
        //std::cout << endl << "Função objetivo: " << solucoes[i].calcFuncObjetivo(solucoes[i].data) << std::endl;
    }
    //trocarHorario(solucoes[1]);
    printSolucoes();
}

void Metaheuristica::inserirInicio( Solucao* sol, std::set <Disciplina*> listaDisc ){
    /*  Loop de disciplinas em ordem randomica (ver geraListaDisc) */

    vector <int> discsAlocadas;

    for( auto d = listaDisc.begin(); d != listaDisc.end(); d++ ){
        //cout << (*d)->nome << endl;
        auto disc = sol->discSol.find( *d );
        //Pega o mapa da turma associada a disciplina
        auto turma = sol->horarioTurma.find(disc->second->turma);
        //Gera variaveis necessarias para parametrizar a agenda de Disciplinas
        int splits = disc->first->splits;
        int chPresencial = disc->first->chPresencial;
        int chEad = disc->first->chEad;
        int minimoDiario = disc->first->minimoDiario;
        int tamanhoSplit[splits];

        //Gera vetor com o tamanho de cada split (mesma tecnica do Legacy)
        for(int i = 0; i < splits; i++){
            tamanhoSplit[i] = minimoDiario;
        }
        for(int i = 0; i < chPresencial % (minimoDiario * splits); i++){
            tamanhoSplit[i % splits]++;
        }
        //Lista de dias consecutivos com o tamanho de determinado split
        list <int> horariosConsec;
        //Lista de professores e salas da disciplina
        list <ProfSol*> prof;
        //Preenche a lista de professores
        for(int i = 0; i < disc->first->professorIndex.size(); i++){
            prof.push_back(sol->horarioProf.find( sol->data->professores[disc->first->professorIndex[i]] )->second);
        }
        //Lista de dias randomizados
        int listaDias[6] = {0,1,2,3,4,5};
        geraListaDias(listaDias, 6);
        if(chEad > 0){
            do{
                horariosConsec = turma->second->agendaTurma->checarConsecutivo(*d,5,chEad,0);
            }  while( horariosConsec.empty() );
            while(chEad != 0){
                int flag = 0;
                for(auto p = prof.begin(); p != prof.end(); p++){
                    if( (*p)->agendaProf->checarConsecutivo( 5, horariosConsec.front(), chEad, 0 )) {
                        flag = 1;
                    }
                }
                if(flag == 1 ) {
                    horariosConsec.pop_front();
                    break;
                }
                for (auto p = prof.begin(); p != prof.end(); p++)
                    for (int slot = horariosConsec.front(); slot < horariosConsec.front() + chEad; slot++)
                        (*p)->agendaProf->agenda[5][slot];
                for (int slot = horariosConsec.front(); slot < horariosConsec.front() + chEad; slot++)
                    turma->second->agendaTurma->agenda[5][slot];
                chEad--;
            }
            //turma->second->agendaTurma->printAgenda();
        }
        horariosConsec.clear();
        for(int s = 0, dia = 0; s < splits; s++, dia++){
            
            int travaDisc;
            
            //Alterar para olhar if(disc->first->turno == manha) = 0~6
            if(turma->first->turno != disc->first->turno) 
                travaDisc = -1;
            else travaDisc = 0;
            int satanasTemporario;

            //Cagada
            for(int cont = 0; horariosConsec.empty(); dia++, cont++){
                cout << cont << endl;
                if(cont > 50){
                    break;
                }
                if(dia >= 6){
                    dia = 0;
                }
                horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s], travaDisc);
                //mostrarHorarios(horariosConsec, turma->second);
                satanasTemporario = dia;
                cout << "Ainda está no count" << endl;
            }
            //Fim da cagada
            dia = satanasTemporario;
            //Checa se o professor tem horario pra esse dia
            for(auto p = prof.begin(); p != prof.end(); p++){
                if(!(*p)->agendaProf->checarConsecutivo( listaDias[dia], horariosConsec.front(), tamanhoSplit[s], travaDisc )){
                    break;
                }
            }

            while ( horariosConsec.size() > 0 ){
                int flag = 0;
                if(flag == 1){
                    horariosConsec.pop_front();
                    break;
                }
                for(auto professor = prof.begin(); professor != prof.end(); professor++){
                    for(auto slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                        (*professor)->agendaProf->agenda[listaDias[dia]][slot] = disc->first->index;
                    }
                }
                for(auto sala = disc->second->sala.begin(); sala != disc->second->sala.end(); sala++){
                    for(auto slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                        (*sala)->agendaSala->agenda[listaDias[dia]][slot] = disc->first->index;
                    }
                }
                for(auto lab = disc->second->lab.begin(); lab != disc->second->lab.end(); lab++){
                    for(auto slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                        (*lab)->agendaSala->agenda[listaDias[dia]][slot] = disc->first->index;
                    }
                }
                for(auto slot = horariosConsec.front(); tamanhoSplit[s] > 0; slot++, tamanhoSplit[s]--){
                    turma->second->agendaTurma->agenda[listaDias[dia]][slot] = disc->first->index;
                    //getchar();
                }
                horariosConsec.pop_front();
            } //!_while (!empty)
            disc->second->aulasRestantes -= tamanhoSplit[s];
        } //!_for(int s)
        turma->second->print();
        discsAlocadas.push_back((*d)->index);
    } //!for (disc)

/*     for(auto sobra = listaDisc.begin(); sobra != listaDisc.end(); sobra++){
        if(!std::count(discsAlocadas.begin(), discsAlocadas.end(), (*sobra)->index)){
            cout << "Disciplina não alocada: " << (*sobra)->index << " " << (*sobra)->nome << endl;
        }
    }
*/
    //for(auto turma = sol->horarioTurma.begin(); turma != sol->horarioTurma.end(); turma++) (*turma).second->print();

    
} //!_inserirInicio()

void Metaheuristica::mostrarHorarios(list <int> listaHorarios, TurmaSol* turma){

    if(listaHorarios.empty()){
        cout << "Lista vazia\n";
        turma->agendaTurma->printAgenda();
        return;
    }

    cout << "Lista de horarios: ";
    for(auto i = listaHorarios.begin(); i != listaHorarios.end(); i++)
        cout << *i << " | ";
    cout << endl << "Tamanho total: " << listaHorarios.size() << endl;

}

void Metaheuristica::printSolucoes(){
    for(int i = 0; i < solucoes.size(); i++){
        
        cout << "\n\nSolução [" << i << "]" << "\n" << endl;
        
        for( auto turma = solucoes[i].horarioTurma.begin(); turma != solucoes[i].horarioTurma.end(); turma++){
            turma->second->print();
        }
/*         for( auto prof = solucoes[i].horarioProf.begin(); prof != solucoes[i].horarioProf.end(); prof++){
            prof->second->print();
        } */
/*         for( auto sala = solucoes[i].horarioSala.begin(); sala != solucoes[i].horarioSala.end(); sala++){
            if(sala->second->usado == true)
                sala->second->print();
        } */
    }
} //!_printSolucoes()


void Metaheuristica::geraListaDias(int listaDias[], int tam){
    random_shuffle( listaDias, listaDias+tam );
}

std::set <Disciplina*> Metaheuristica::geraListaDisc(Solucao* sol, int parametro){
    
    cout << "Parametro randomico: " << parametro << endl;

    std::set <Disciplina*> listaDisc;
    
    switch (parametro) {
    case 0:{
        vector <int> discPrioridade, discResto;
        for(int it = 1; it < sol->data->disciplinas.size(); it++){
            if(sol->data->disciplinas[it]->chPresencial > 3 && sol->data->disciplinas[it]->splits == 1){
                discPrioridade.push_back(it);
            }else{
                discResto.push_back(it);
            }
        }

        random_shuffle( discPrioridade.begin(), discPrioridade.end() ); 
        random_shuffle( discResto.begin(), discResto.end() ); 

        for(auto it = discPrioridade.begin(); it != discPrioridade.end(); it++){
            listaDisc.insert( sol->data->disciplinas[(*it)] );
        }
        for(auto it = discResto.begin(); it != discResto.end(); it++){
            listaDisc.insert( sol->data->disciplinas[(*it)] );
        }
    } break;
    
    case 1:{
        vector <Professor*> temp = sol->data->professores;
        random_shuffle(temp.begin(), temp.end());
        for (auto prof = temp.begin(); prof != temp.end(); prof++){
            for (auto disc = (*prof)->listaDiscs.begin(); disc != (*prof)->listaDiscs.end(); disc++) {
                listaDisc.insert((*disc));
            }
        }
    } break;

    }
    return listaDisc;
}