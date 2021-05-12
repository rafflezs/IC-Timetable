#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){
    
    for(int i = 0; i < 2; i++){
        Solucao sol = Solucao();
        solucoes.push_back(sol);
    }
    
    for( int i = 1; i < solucoes.size(); i++ ){
        auto listaDisc = geraListaDisc( &solucoes[i], 1);
        std::cout << "ListaDisc size(): " << listaDisc.size() << endl;
        std::cout << "----------------------Comecando inserirInicio----------------------" << endl << endl;
        inserirInicio( &solucoes[i], listaDisc );
        //std::std::cout << endl << "Função objetivo: " << solucoes[i].calcFuncObjetivo(solucoes[i].data) << std::endl;
    }
    //trocarHorario(solucoes[1]);
    printSolucoes();
}

void Metaheuristica::inserirInicio( Solucao* sol, std::list <Disciplina*> listaDisc ){

    list <Disciplina*> discNaoAlocadas;
    for(auto nao = listaDisc.begin(); nao != listaDisc.end(); nao++){
        discNaoAlocadas.push_back(*nao);
    }

    //
    for( auto d = listaDisc.begin(); d != listaDisc.end(); d++ ){
        
        auto disc = sol->discSol.find( *d );
        
        //Pega o mapa da turma associada a disciplina
        auto turma = sol->horarioTurma.find(disc->second->turma);
        
        //Gera variaveis necessarias para parametrizar a agenda de Disciplinas
        int splits = disc->first->splits;
        int chPresencial = disc->first->chPresencial;
        int chEad = disc->first->chEad;
        int minimoDiario = disc->first->minimoDiario;
        int tamanhoSplit[splits];

        int aulasRestantes = chPresencial + chEad;

        std::cout << "Disciplina "<< disc->first->id << " " << disc->first->nome << endl << "Agenda turma pré-disc \n";
        turma->second->print();
        std::cout << endl;

        //Gera vetor com o tamanho de cada split (mesma tecnica do Legacy)
        for(int i = 0; i < splits; i++) tamanhoSplit[i] = minimoDiario;
        
        //Lista de dias consecutivos com o tamanho de determinado split
        list <int> horariosConsec;

        //Lista de professores e salas da disciplina
        list <ProfSol*> prof;

        //Preenche a lista de professores
        for(int i = 0; i < disc->first->professorIndex.size(); i++){
            prof.push_back(sol->horarioProf.find( sol->data->professores[disc->first->professorIndex[i]] )->second);
        }
        //Lista de dias randomizados
        int listaDias[] = {0,1,2,3,4,5};
        geraListaDias(listaDias, sizeof(listaDias)/sizeof(int));

        //Alocação de disciplinas EaD
        if(chEad > 0){
        std::cout << "Disciplina EaD com ch-online de " << disc->first->chEad << " horas" << endl;
            do{
                horariosConsec = turma->second->agendaTurma->alocaEad(*d,chEad);
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
                        (*p)->agendaProf->agenda[5][slot] = disc->first->index;
                
                for (int slot = horariosConsec.front(); slot < horariosConsec.front() + chEad; slot++)
                    turma->second->agendaTurma->agenda[5][slot]  = disc->first->index;

                chEad--;
                aulasRestantes--;
            }
        }

        if(chPresencial == 0) continue;

        std::cout << "Debug 3" << endl << endl;
        for(int i = 0; i < chPresencial % (minimoDiario * splits); i++) tamanhoSplit[i % splits]++;

        sort(tamanhoSplit, tamanhoSplit + (sizeof(tamanhoSplit) / sizeof(tamanhoSplit[0])), greater<int>());

        horariosConsec.clear();
        int s = 0;
        for(int dia = 0; s < splits; dia++){
            
            list <int> diaTabu; 

            int travaDisc;
            
            //Alterar para olhar if(disc->first->turno == manha) = 0~6
            if(turma->first->turno != disc->first->turno) 
                travaDisc = -1;
            else travaDisc = 0;

            int satanasTemporario;

            //Cagada
            for(int cont = 0; horariosConsec.empty(); dia++, cont++){
                std::cout << "Contador " << cont << endl;
                if(cont > 60) break;
                
                if(cont < 40){
                    if(dia > 4) dia = 0;
                    std::cout << "DIA ESCOLHIDO: " << listaDias[dia] << endl;
                    horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s], travaDisc);
                    //mostrarHorarios(horariosConsec, turma->second);
                    satanasTemporario = dia;
                } else if(cont >= 40){
                    if(dia > 5) dia = 0;
                    std::cout << "D1" << std::endl;
                    std::cout << "DIA ESCOLHIDO: " << listaDias[dia] << endl;
                    horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s], travaDisc);
                    //mostrarHorarios(horariosConsec, turma->second);
                    std::cout << "D2" << std::endl;
                    satanasTemporario = dia;
                }
                std::cout << "D3" << std::endl;
            }//Fim da cagada
            
            dia = satanasTemporario;

            while ( horariosConsec.size() > 0 ){

                int flag = 0;
                //Checa se o professor tem horario pra esse dia
                for(auto p = prof.begin(); p != prof.end(); p++){
                    if(!(*p)->agendaProf->checarConsecutivo( listaDias[dia], horariosConsec.front(), tamanhoSplit[s], travaDisc )){
                        flag = 1;
                        break;
                    }
                }
                
                for(auto lab = disc->second->lab.begin(); lab != disc->second->lab.end(); lab++){
                    if(!(*lab)->agendaSala->checarConsecutivo( listaDias[dia], horariosConsec.front(), tamanhoSplit[s], travaDisc )){
                        flag = 2;
                        break;
                    }
                }
                
                if(flag != 0){
                    horariosConsec.pop_front();
                    continue;
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
                cout << "TamanhoSplit[" << tamanhoSplit[s] << "] | s: " << s << " | Aulas restantes: " << aulasRestantes << endl;
                aulasRestantes = aulasRestantes - tamanhoSplit[s];
                for(auto slot = horariosConsec.front(); tamanhoSplit[s] > 0; slot++, tamanhoSplit[s]--){
                    turma->second->agendaTurma->agenda[listaDias[dia]][slot] = disc->first->index;
                    //getchar();
                }
                s++;
                break;
            } //!_while (!empty)
        } //!_for(int s)
        if(aulasRestantes ==0) { discNaoAlocadas.remove(disc->first); }
        cout << "Final do caralho -- tamanhoSplit[" << tamanhoSplit[s] << "] | s: " << s << " | Aulas restantes: " << aulasRestantes << endl;

        turma->second->agendaTurma->printAgenda();
        std::cout << endl << endl;
    } //!for (disc)
    for(auto nao = discNaoAlocadas.begin(); nao != discNaoAlocadas.end(); nao++) std::cout << (*nao)->id << " ";
    std::cout << std::endl;
} //!_inserirInicio()

void Metaheuristica::mostrarHorarios(list <int> listaHorarios, TurmaSol* turma){

    if(listaHorarios.empty()){
        std::cout << "\nLista vazia\n\n";
        turma->agendaTurma->printAgenda();
        return;
    }

    std::cout << "Lista de horarios: ";
    for(auto i = listaHorarios.begin(); i != listaHorarios.end(); i++)
        std::cout << *i << " | ";
    std::cout << endl << "Tamanho total: " << listaHorarios.size() << endl;
    std::cout << std::endl;
}

void Metaheuristica::printSolucoes(){
    for(int i = 1; i < solucoes.size(); i++){
        
        std::cout << "\n\nSolução [" << i << "]" << "\n" << endl;
        
        for( auto turma = solucoes[i].horarioTurma.begin(); turma != solucoes[i].horarioTurma.end(); turma++){
            turma->second->print();
        }
        for( auto prof = solucoes[i].horarioProf.begin(); prof != solucoes[i].horarioProf.end(); prof++){
            prof->second->print();
        }
        for( auto sala = solucoes[i].horarioSala.begin(); sala != solucoes[i].horarioSala.end(); sala++){
            if(sala->second->usado == true)
                sala->second->print();
        }
    }
} //!_printSolucoes()


void Metaheuristica::geraListaDias(int listaDias[], int tam){
    random_shuffle( listaDias, listaDias+tam-1 );
    std::cout << listaDias[0] << " " << listaDias[1] << " " << listaDias[2] << " " << listaDias[3] << " " << listaDias[4] << " " << listaDias[5] << endl; 
}

std::list <Disciplina*> Metaheuristica::geraListaDisc(Solucao* sol, int parametro){
    
    std::cout << "Parametro randomico: " << parametro << endl;

    std::list <Disciplina*> listaDisc;
    
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
            listaDisc.push_back( sol->data->disciplinas[(*it)] );
        }
        for(auto it = discResto.begin(); it != discResto.end(); it++){
            listaDisc.push_back( sol->data->disciplinas[(*it)] );
        }
    } break;
    
    case 1:{
        vector <Professor*> temp = sol->data->professores;
        random_shuffle(temp.begin(), temp.end());
        for (auto prof = temp.begin(); prof != temp.end(); prof++){
            for (auto disc = (*prof)->listaDiscs.begin(); disc != (*prof)->listaDiscs.end(); disc++) {
                listaDisc.push_back((*disc));
            }
        }
    } break;

    case 3 :{
        for(auto disc = sol->discSol.begin(); disc != sol->discSol.end(); disc++) listaDisc.push_back((*disc).first);
    }

    }

    return listaDisc;
}