#include "solucao.hpp"

Solucao::Solucao(){

    Data* data = new Data();

    data->lerDados();

    for(int index = 1; index < data->professores.size(); index++){
        ProfSol* prof = new ProfSol(data->professores[index]);
        this->horarioProf.insert( pair <Professor*, ProfSol*>(data->professores[index], prof) );         
    }

    for(int index = 1; index < data->salas.size(); index++){
        SalaSol* sala = new SalaSol(data->salas[index]);
        this->horarioSala.insert( pair <Sala*, SalaSol*>(data->salas[index], sala) );        
    }

    for(int index = 1; index < data->turmas.size(); index++){
        TurmaSol* turma = new TurmaSol(data->turmas[index]);
        turma->salaBase = selecionaSala(data, turma);
        horarioTurma.insert( pair<Turma*, TurmaSol*> (data->turmas[index], turma) );
    }

    for(int index = 1; index < data->disciplinas.size(); index++){
        DiscSol* disc = new DiscSol(data, data->disciplinas[index]);
        discSol.insert( pair<Disciplina*, DiscSol*> (data->disciplinas[index], disc) );
    }
}

/* Sala* Solucao::selecionaSala(DiscSol* disciplina, Data* data){

} */

Sala* Solucao::selecionaSala(Data* data, TurmaSol* turma){
    //O problema tá aqui nesse IF

        for(int i = 1; i < data->salas.size(); i++){
            if(turma->turma->turno == "Manhã" && !(tabuManha.count(data->salas[i]))){
                tabuManha.insert(data->salas[i]);
                return data->salas[i];
            }
            if(turma->turma->turno == "Tarde" && !(tabuTarde.count(data->salas[i]))){
                tabuTarde.insert(data->salas[i]);
                return data->salas[i];
            }
            if(turma->turma->turno == "Noite" && !(tabuNoite.count(data->salas[i]))){
                tabuNoite.insert(data->salas[i]);
                return data->salas[i];
            }
        }

    return data->salas[0];

}


int Solucao::calcFuncObjetivo(Data* data){
    
    this->sextoHorario = 0;
    this->janelaHorario = 0;
    this->diasTrabalhados = 0;

    for( auto turma = horarioTurma.begin(); turma != horarioTurma.end(); turma++ ){
        this->sextoHorario += calcSextoHorario( turma->second->agendaTurma );
    }

    for( auto professor = horarioProf.begin(); professor != horarioProf.end(); professor++ ){
        this->janelaHorario += calcJanela( professor->second->agendaProf );
        this->diasTrabalhados += calcDiasTrabalhados( professor->second->agendaProf );
    }
    
    return (this->sextoHorario + this->janelaHorario + this->diasTrabalhados);
}


int Solucao::calcJanela(Agenda* professor){

    int dias[6];
    int janelaHorarios = 0;

    for(int dia = 0; dia < 6; dia++){

        int slotInicio = 0;
        int slotFim = 0;

        //If the resource has no activity in the given day, go to the next day
        if(dias[dia] == 0){
            continue;
        }

        //Manhã
        for(int slot = 0; slot < 6; slot++){
            if(professor->agenda[dia][slot] > 0){
                slotInicio = slot;
                break;
            }
        }
        for(int slot = 5; slot >= 0; slot--){
            if(professor->agenda[dia][slot] > 0){
                slotFim = slot;
                break;
            }
        }

        for(int slot = slotInicio+1; slot < slotFim; slot++){
            if(professor->agenda[dia][slot] <= 0){
                janelaHorarios++;
            }
        }

        slotInicio = 0;
        slotFim = 0;

        //Tarde
        for(int slot = 6; slot < 12; slot++){
            if(professor->agenda[dia][slot] > 0){
                slotInicio = slot;
                break;
            }
        }
        for(int slot = 11; slot >= 6; slot--){
            if(professor->agenda[dia][slot] > 0){
                slotFim = slot;
                break;
            }
        }

        for(int slot = slotInicio+1; slot < slotFim; slot++){
            if(professor->agenda[dia][slot] <= 0){
                janelaHorarios++;
            }
        }

        slotInicio = 0;
        slotFim = 0;


        //Noite
        for(int slot = 12; slot < 16; slot++){
            if(professor->agenda[dia][slot] > 0){
                slotInicio = slot;
                break;
            }
        }
        for(int slot = 15; slot >= 12; slot--){
            if(professor->agenda[dia][slot] > 0){
                slotFim = slot;
                break;
            }
        }

        for(int slot = slotInicio+1; slot < slotFim; slot++){
            if(professor->agenda[dia][slot] <= 0){
                janelaHorarios++;
            }
        }
    }

    cout << "\033[0m";

    if(janelaHorarios > 0){
        professor->printAgenda();
    }
    
    return janelaHorarios;

}


int Solucao::calcSextoHorario(Agenda* turma){

    int sextoHorario = 0;

    for(int dia = 0; dia < 5; dia++){
        if(turma->agenda[dia][5 || 11] > 0){
            this->sextoHorario++;
        }
    }

    return sextoHorario;

}


int Solucao::calcDiasTrabalhados(Agenda* professor){

    int atividade[6];

    for(int i = 0; i < 6; i++){
        atividade[i] = 0;
    }

    int diasTrabalhados = 0;
    int diaInicio = 0;
    int diaFim = 5;

    for(int dia = 0; dia < 6; dia++){
        for(int slot = 0; slot < 16; slot++){
            if(professor->agenda[dia][slot] > 0){
                atividade[dia] = 1;
            }
        }
    }

    //Find the first and last day of activity
    for(int dia = 0; dia < 6; dia++){
        if(atividade[dia] == 1){
            diaInicio = dia;
            break;
        }
    }
    for(int dia = 5; dia >= diaInicio; dia--){
        if(atividade[dia] == 1){
            diaFim = dia;
            break;
        }
    }

    for(int dia = diaInicio+1; dia < diaFim; dia++){
        if(!atividade[dia]){
            diasTrabalhados++;
        }
    }

    return diasTrabalhados;

}


void Solucao::print(){

    std::cout << "\n------------------------Disciplinas------------------------" << endl;

    for(auto disc = discSol.begin(); disc != discSol.end(); disc++){
        std::cout << "Disciplina (Primitivo)" << endl;
        disc->first->print();
        std::cout << "Disciplina (Solucao)" << endl;
        disc->second->print();
        std::cout << std::endl;

    }

    std::cout << "\n------------------------Professores------------------------" << endl;

    for(auto prof = horarioProf.begin(); prof != horarioProf.end(); prof++){
        std::cout << "Professor (Primitivo)" << endl;
        prof->first->print();
        std::cout << "Professor (Solucao)" << endl;
        prof->second->print();
        std::cout << std::endl;

    }

    std::cout << "\n------------------------Turmas------------------------" << endl;

    for(auto turma = horarioTurma.begin(); turma != horarioTurma.end(); turma++){
        std::cout << "Turma (Primitivo)" << endl;
        turma->first->print();
        std::cout << "Turma (Solucao)" << endl;
        turma->second->print();
        std::cout << std::endl;
    }

    std::cout << "\n------------------------Salas------------------------" << endl;

    for(auto sala = horarioSala.begin(); sala != horarioSala.end(); sala++){
        std::cout << "Sala (Primitivo)" << endl;
        sala->first->print();
        std::cout << "Sala (Solucao)" << endl;
        sala->second->print();
        std::cout << std::endl;

    }

}