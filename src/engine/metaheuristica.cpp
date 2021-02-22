#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(){
    for(int i = 0; i < 100; i++){
        Solucao sol = Solucao();
        solucoes.push_back(sol);
    }
    for( int i = 1; i < 100; i++ ){
        auto listaDisc = geraListaDisc( &solucoes[i]);
        //cout << "Gerando população das matrizes da Solucao[" << i <<"]"<< endl;
        inserirInicio( &solucoes[i], listaDisc );
        //std::cout << endl << "Função objetivo: " << solucoes[i].calcFuncObjetivo(solucoes[i].data) << std::endl;
    }
    printSolucoes();
}

void Metaheuristica::inserirInicio( Solucao* sol, std::vector <Disciplina*> listaDisc ){
    /*
    ** para disciplinas noturnas QUE TENHAM AULAS AOS SABADOS, priorizar a inserção durante a semana
    ** OU
    ** checar caso a caso se a turma tem 20h ou menos e mudar manualmente na tabela
    */
    
    /*
    ** Gerar um limitante de tempo para o insertEarly. Ex: não conseguiu inserir a disc apos n iterações
    ** descarta e refaz até atingir um limite de tempo para a população.
    */
    
    /*  Loop de disciplinas em ordem randomica (ver geraListaDisc) */
    for( auto d = listaDisc.begin(); d != listaDisc.end(); d++ ){
        auto disc = sol->discSol.find( *d );
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
        //Lista de professores e salas da disciplina
        list <ProfSol*> prof;
        //Preenche a lista de professores
        for(int i = 0; i < disc->first->professorIndex.size(); i++){
            prof.push_back(sol->horarioProf.find( sol->data->professores[disc->first->professorIndex[i]] )->second);
        }
        //Lista de dias randomizados
        int listaDias[6] = {0,1,2,3,4,5};
        geraListaDias(listaDias, 6);
        for(int s = 0, dia = 0; s < splits; s++){
            if(dia >= 6){
                dia = 0;
            }
            //Obtem um horario inicial pela agenda turma
            horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s],0);
            //Caso não obtenha horario nesse dia, iterar até achar um dia com horario
            while(horariosConsec.size() == 0) {
                dia++;
                if(dia >= 6){
                    dia = 0;
                }
                horariosConsec = turma->second->agendaTurma->checarConsecutivo( *d ,listaDias[dia], tamanhoSplit[s], 0);
            }
            //Checa se o professor tem horario pra esse dia
            for(auto p = prof.begin(); p != prof.end(); p++){
                if(!(*p)->agendaProf->checarConsecutivo( listaDias[dia], horariosConsec.front(), tamanhoSplit[s], 0 )){
                    break;
                }
            }
            list <SalaSol*> listaSalas = selecionaSala(sol, *d, turma->second, &listaDias[dia], &horariosConsec.front(), &tamanhoSplit[s]);
            disc->second->listaSalas = listaSalas;
            while ( !horariosConsec.empty() ){
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
                for(auto sala = listaSalas.begin(); sala != listaSalas.end(); sala++){
                    for(auto slot = horariosConsec.front(); slot < tamanhoSplit[s] + horariosConsec.front(); slot++){
                        (*sala)->agendaSala->agenda[listaDias[dia]][slot] = disc->first->index;
                    }
                }
                for(auto slot = horariosConsec.front(); tamanhoSplit[s] > 0; slot++, tamanhoSplit[s]--){
                    turma->second->agendaTurma->agenda[listaDias[dia]][slot] = disc->first->index;
                    //getchar();
                }
                horariosConsec.clear();
            } //!_while (!empty)
            dia++;
        } //!_for(int s)
    } //!for (disc)
} //!_inserirInicio()

Solucao* trocarDisciplina(Solucao sol){
    
    auto disc1 = sol.discSol.find( sol.data->disciplinas[rand() % 1 + (sol.data->disciplinas.size()-1)] );
    auto turma = sol.horarioTurma.find( disc1->second->turma );
    do{
        turma->second->discLista.sort();
    } while (turma->second->discLista.front() == disc1->second);
    
    auto disc2 = turma->second->discLista.front();
    
    int dia, tamanhoSplit, slot = 0;
    
    do {
        dia = rand() % 6;
        tamanhoSplit = desalocar( disc1->second, &sol, &dia, &slot );
    } while(tamanhoSplit == 0);
    
    for(slot = slot - (tamanhoSplit - 1); slot < tamanhoSplit; slot++){
        turma->second->agendaTurma->agenda[dia][slot] = disc2->disciplina->index;
    }
}

int desalocar(DiscSol* disc, Solucao* sol, int* dia, int* slot){
    
    auto turma = sol->horarioTurma.find(disc->turma);
    list <ProfSol*> prof;
    for(auto p = disc->profLista.begin(); p != disc->profLista.end(); p++)
        prof.push_back( sol->horarioProf.find(*p)->second );
    auto salas = disc->listaSalas;
    int tamanhoSplit;
    int slotFim;

    if(disc->disciplina->turno == "Manhã"){
        *slot = 0;
        slotFim = 6;
    }else if(disc->disciplina->turno == "Tarde"){
        *slot = 6;
        slotFim = 12;
    }else if(disc->disciplina->turno == "Noite"){
        *slot = 12;
        slotFim = 16;
    }

    for(*slot; *slot < slotFim; *slot++){
        if( turma->second->agendaTurma->agenda[*dia][*slot] == disc->disciplina->index ){
            turma->second->agendaTurma->agenda[*dia][*slot] = 0;
            for(auto s = salas.begin(); s != salas.end(); s++)
                (*s)->agendaSala->agenda[*dia][*slot] = 0;
            for(auto p = prof.begin(); p != prof.end(); p++)
                (*p)->agendaProf->agenda[*dia][*slot] = 0;
            tamanhoSplit++;
        }
    }
    
    return tamanhoSplit;
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
        for( auto sala = solucoes[i].horarioSala.begin(); sala != solucoes[i].horarioSala.end(); sala++){
            if(sala->second->usado == true)
                sala->second->print();
        }
    }
} //!_printSolucoes()

list <SalaSol*> Metaheuristica::selecionaSala(Solucao* sol, Disciplina* disc, TurmaSol* turma, int* dia, int* horario, int* tamanho){
    list <SalaSol*> listaSalas;
    listaSalas.push_back( sol->horarioSala.find( turma->salaBase )->second );
    for( auto temp = sol->horarioSala.begin(); temp != sol->horarioSala.end(); temp++ ){
        if(temp->first->tipo == disc->tipoSala && temp->second->agendaSala->checarConsecutivo( *dia, *horario, *tamanho, 0 )){
            listaSalas.push_back( temp->second );
            temp->second->usado = true;
            break;
        }
    }
    return listaSalas;
}

void Metaheuristica::geraListaDias(int listaDias[], int tam){
    random_shuffle( listaDias, listaDias+tam );
}

std::vector <Disciplina*> Metaheuristica::geraListaDisc(Solucao* sol){
    vector <int> discPrioridade, discResto;
    for(int it = 1; it < sol->data->disciplinas.size(); it++){
    
        if(sol->data->disciplinas[it]->cargaHoraria > 3 && sol->data->disciplinas[it]->splits == 1){
            discPrioridade.push_back(it);
        }else{
            discResto.push_back(it);
        }
    }
    random_shuffle( discPrioridade.begin(), discPrioridade.end() ); 
    random_shuffle( discResto.begin(), discResto.end() ); 
    std::vector <Disciplina*> listaDisc;
    for(auto it = discPrioridade.begin(); it != discPrioridade.end(); it++){
        listaDisc.push_back( sol->data->disciplinas[(*it)] );
    }
    for(auto it = discResto.begin(); it != discResto.end(); it++){
        listaDisc.push_back( sol->data->disciplinas[(*it)] );
    }
    return listaDisc;
}