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

void trocarDisciplina(Solucao* sol){
    
    int discIndex = rand() % 1 + (sol->data->disciplinas.size()-1);
    
    if(int r = rand() % 1){
        int tamanhoSplit = ceil(sol->data->disciplinas[discIndex]->splits / sol->data->disciplinas[discIndex]->minimoDiario);
    }else{
        int tamanhoSplit = floor(sol->data->disciplinas[discIndex]->splits / sol->data->disciplinas[discIndex]->minimoDiario + 1);
    }
    

}

void desalocar(int* tamanhoSplit, DiscSol* disc, Solucao* sol){

    auto agendaTurma = sol->horarioTurma.find(disc->turma);
    int dia = 0, slot = 0;

    for(dia; dia < 6; dia++){
        for(slot; slot < 16; slot++){
            if(agendaTurma->second->agendaTurma->agenda[dia][slot] == disc->disciplina->index && agendaTurma->second->agendaTurma->agenda[dia][slot + *tamanhoSplit - 1] ){
                break;
            }
        }
    }

    for(int i = slot; i < slot + *tamanhoSplit - 1; i++){
        agendaTurma->second->agendaTurma->agenda[dia][i] = 0;
        for(auto prof = disc->profLista.begin(); prof != disc->profLista.end(); prof++)
            
    }

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