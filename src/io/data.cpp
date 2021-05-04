#include "data.hpp"


void Data::lerDados(){

    map<string, int> mapProf;
    map<string, int> mapTurma;
    map<string, int> mapDisc;

    professores = lerProfessor(&mapProf);
    salas = lerSala();
    disciplinas = lerDisc(&mapDisc);
    cursos = lerCurso();
    turmas = lerTurma(&mapTurma, cursos); 

    relaciona(professores, &mapDisc);
    relaciona(disciplinas, &mapProf, &mapTurma);
    relaciona(turmas, &mapProf, &mapDisc);
}


vector <Professor*> Data::lerProfessor(map<string, int> *mapProf){
    //Corresponde as colunas de cada linha de informação
    vector <string> colData;
    string tempString;
    int id = 0;

    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Professores.csv");

    getline(file, tempString, '\n');

    Professor* tProf = new Professor();
    tProf->index = id;
    tProf->id = "NULL";
    tProf->nome = "NULL";

    professores.push_back(tProf);

    while (file.good()){

        id++;

        getline(file, tempString, '\n');
        colData = separadorString(tempString, ';');

        if(colData.size() <= 0) break;

        Professor* prof = new Professor();
        prof->index = id;
        prof->id = colData[0];
        prof->nome = colData[1];

        for(int dia = 0; dia < 6; dia++){
            for(int horario = 0; horario < 16; horario++){
                prof->disponibilidade[dia][horario] = 0;
            }
        }

        for(int i = 3, j = 0; i < 9; i++, j++){
            disponibilidade(prof, &colData[i], j);
        }

        mapProf->insert( pair<string, int>(colData[1], id ));

        professores.push_back(prof);
    }
    return professores;
}


vector<Sala*> Data::lerSala(){
    //Corresponde as colunas de cada linha de informação
    vector <string> colData;
    string tempString;
    int id = 0;

    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Salas.csv");

    getline(file, tempString, '\n');

    Sala* tSala = new Sala();
    tSala->index = id;
    tSala->id = "NULL";
    tSala->nome = "NULL";

    salas.push_back(tSala);

    while (file.good()){

        id++;

        getline(file, tempString, '\n');
        colData = separadorString(tempString, ';');

        if(colData.size() <= 0) break;

        Sala* sala = new Sala();
        sala->index = id;
        sala->id = colData[0];
        sala->nome = colData[1];
        sala->bloco = colData[2];
        sala->capacidade = stoi(colData[3]);
        sala->tipo = colData[4];

        for(int dia = 0; dia < 6; dia++){
            for(int horario = 0; horario < 16; horario++){
                sala->disponibilidade[dia][horario] = 0;
            }
        }

        for(int i = 5, j = 0; i < 11; i++, j++){
            disponibilidade(sala, &colData[i], j);
        }

        salas.push_back(sala);
    }
    
    return salas;

}

vector <Disciplina*> Data::lerDisc(map<string, int> *mapDisc){

    //Corresponde as colunas de cada linha de informação
    vector <string> colData;
    string tempString;
    int id = 0;

    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Disciplinas.csv");

    getline(file, tempString, '\n');

    Disciplina* tDisc = new Disciplina();
    tDisc->index = id;
    tDisc->id = "NULL";
    tDisc->nome = "NULL";

    disciplinas.push_back(tDisc);

    while (file.good()){

        id++;

        getline(file, tempString, '\n');
        colData = separadorString(tempString, ';');

        if(colData.size() <= 0) break;

        Disciplina* disc = new Disciplina();
        disc->index = id;
        disc->id = colData[0];
        disc->nome = colData[1];

        cout << disc->nome << endl;

        disc->turno = colData[5];

        disc->sala = separadorString(colData[6], ',');
        cout << "(Sala) Linha do csv: " << colData[6] << endl;
        for(auto cu = disc->sala.begin(); cu != disc->sala.end(); cu++){
            cout << (*cu) << " | ";
        } cout << endl;
        cout << endl;
        disc->lab = separadorString(colData[7], ',');
        cout << "(Lab) Linha do csv: " << colData[7] << endl;
        for(auto cu = disc->lab.begin(); cu != disc->lab.end(); cu++){
            cout << (*cu) << " | ";
        } cout << endl << endl << endl;

        disc->capacidadeTurma = stoi(colData[8]);
        disc->chPresencial = stoi(colData[9]);
        disc->chEad = stoi(colData[10]);
        disc->minimoDiario = stoi(colData[11]);
        disc->splits = stoi(colData[12]);

        for(int dia = 0; dia < 6; dia++){
            for(int horario = 0; horario < 16; horario++){
                disc->disponibilidade[dia][horario] = 0;
            }
        }

        for(int i = 13, j = 0; i < colData.size(); i++, j++){
            disponibilidade(disc, &colData[i], j);
        }

        mapDisc->insert( pair<string, int>(colData[0], id ));

        disciplinas.push_back(disc);
    }
    
    return disciplinas;

}

vector <Curso*> Data::lerCurso(){

    //Corresponde as colunas de cada linha de informação
    vector <string> colData;
    string tempString;
    int id = 0;

    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Cursos.csv");

    getline(file, tempString, '\n');

    Curso* tCurso = new Curso();
    tCurso->index = id;
    tCurso->id = "NULL";
    tCurso->nome = "NULL";

    cursos.push_back(tCurso);

    while (file.good()){

        id++;

        getline(file, tempString, '\n');
        colData = separadorString(tempString, ';');

        if(colData.size() <= 0) break;

        Curso* curso = new Curso();
        curso->index = id;
        curso->id = colData[0];
        curso->nome = colData[1];
        curso->grauDeFormacao = colData[2];

        for(int dia = 0; dia < 6; dia++){
            for(int horario = 0; horario < 16; horario++){
                curso->disponibilidade[dia][horario] = 0;
            }
        }

        for(int i = 4, j = 0; i < 10; i++, j++){
            disponibilidade(curso, &colData[i], j);
        }

        cursos.push_back(curso);
    }
    
    return cursos;

}

vector <Turma*> Data::lerTurma(map<string, int> *mapTurma, vector <Curso*> cursos){

    //Corresponde as colunas de cada linha de informação
    vector <string> colData;
    string tempString;
    int id = 0;

    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Turmas.csv");

    getline(file, tempString, '\n');

    Turma* tTurma = new Turma();
    tTurma->index = id;
    tTurma->id = "NULL";
    tTurma->nome = "NULL";

    turmas.push_back(tTurma);

    while (file.good()){

        id++;

        getline(file, tempString, '\n');
        colData = separadorString(tempString, ';');

        if(colData.size() <= 0) break;

        Turma* turma = new Turma();
        turma->index = id;
        turma->id = colData[0];
        turma->nome = colData[1];

        for(vector<Curso*>::iterator it = cursos.begin();
            it != cursos.end(); it++){
                if( (*it)->nome == colData[2] ){
                    turma->curso = (*it);
                }
            }

        turma->turno = colData[3];

        for(int dia = 0; dia < 6; dia++){
            for(int horario = 0; horario < 16; horario++){
                turma->disponibilidade[dia][horario] = 0;
            }
        }

        for(int i = 5, j = 0; i < 11; i++, j++){
            disponibilidade(turma, &colData[i], j);
        }

        mapTurma->insert( pair<string, int>(colData[0], id ));

        turmas.push_back(turma);
    }
    
    return turmas;

}

const vector <string> Data::separadorString(const string& entrada, const char& operador){
    string buffer{""};
    vector <string> tString;

    for (auto temp:entrada){
        if(temp != operador){
            buffer += temp; 
        }else{
		    if(temp == operador && buffer != "") { tString.push_back(buffer); buffer = ""; }
        }  
	}
	
    if(buffer != "") tString.push_back(buffer);
	
	return tString;
}

template <class genericClass> 
void Data::disponibilidade(genericClass* objTemp, string* colunaDado, int dia){

    vector <string> inicio, fim;
    
    inicio = separadorString(*colunaDado, ',');
    if(inicio[0] == "0"){
        inicio[0] = "17";
    }else{
        for(auto n:inicio){
            if(n.length()>2){
                vector<string> temp;    
                string  tempWord;
                temp = separadorString(n, '-');
                int start, end;
                start = stoi(temp[0]); 
                end = stoi(temp[1]);
                for(int i = start; i <= end; i++){
                    tempWord = to_string(i);
                    fim.push_back(tempWord);
                }
            }else{
                fim.push_back(n);
            }
        }
        for(int i = 0; i < 16; i++){
            objTemp->disponibilidade[dia][i] = 0;
        }
    }
    for(auto n:fim){
            objTemp->disponibilidade[dia][stoi(n)-1] = -1;
    }

}

//Relaciona o objeto PROFESSOR com sua Disciplina
void Data::relaciona(vector<Professor*> professores, map<string, int> *mapDisc){

    string tempString;
    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Professores.csv");

    getline(file, tempString, '\n');

    int tempProf = 1;

    while (file.good())
    {
        getline(file, tempString, '\n');
        vector <string> colData = separadorString(tempString, ';');
        vector <string> idDisciplinas = separadorString(colData[2], ',');

        for(auto index = idDisciplinas.begin(); index != idDisciplinas.end(); index++){
            for(auto mp = mapDisc->begin(); mp != mapDisc->end(); mp++){
                if(mp->first == (*index)){
                    professores[tempProf]->listaDiscs.push_back(disciplinas[mp->second]);
                }
            }
        }
        tempProf++;
    }  
}

//Relaciona o objeto DISCIPLINA com seu Professor e Turma
void Data::relaciona(vector<Disciplina*> disciplinas, map<string, int> *mapProf, map<string, int> *mapTurma){

    string tempString;
    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Disciplinas.csv");

    getline(file, tempString, '\n');

    auto tempDisc = 1;

    while (file.good())
    {
        getline(file, tempString, '\n');
        vector <string> colData = separadorString(tempString, ';');
        vector <string> nomeProf = separadorString(colData[2], ',');
        
        for(auto nome = nomeProf.begin(); nome != nomeProf.end(); nome++){
            for(auto mp = mapProf->begin(); mp != mapProf->end(); mp++){
                if(mp->first == (*nome)){
                    disciplinas[tempDisc]->professorIndex.push_back(mp->second);
                }
            }
            for(auto mp = mapTurma->begin(); mp != mapTurma->end(); mp++){
                if(mp->first == colData[4]){
                    disciplinas[tempDisc]->turmaIndex = mp->second;
                }
            }
        }
        tempDisc++;
    }
}

//Relaciona o objeto TURMA com seu respectivo professor
void Data::relaciona(vector<Turma*> turmas, map<string, int> *mapProf, map<string, int> *mapDisc){

    string tempString;
    ifstream file;
    file.open("/home/rafflezs/Documentos/universityTimetabling/csv/Turmas.csv");

    getline(file, tempString, '\n');

    auto tempTurma = 1;

    while (file.good())
    {
        getline(file, tempString, '\n');
        vector <string> colData = separadorString(tempString, ';');

        vector <string> idDisc = separadorString(colData[4], ',');

        for(auto index = idDisc.begin(); index != idDisc.end(); index++){
            for(auto mp = mapDisc->begin(); mp != mapDisc->end(); mp++){
                if(mp->first == (*index)){
                    turmas[tempTurma]->listaDiscs.push_back( disciplinas[mp->second] );

                    auto profId = disciplinas[mp->second]->professorIndex;

                }
            }
        }

        tempTurma++;
    }
}

void Data::print(){

    std::cout << "------------------------Disciplinas------------------------" << endl;
    for(auto disc = disciplinas.begin(); disc != disciplinas.end(); disc++){
        (*disc)->print();
    }

    std::cout << "\n------------------------Professores------------------------" << endl;
    for(auto prof = professores.begin(); prof != professores.end(); prof++){
        (*prof)->print();
    }

    std::cout << "\n------------------------Cursos------------------------" << endl;
    for(auto cu = cursos.begin(); cu != cursos.end(); cu++){
        (*cu)->print();
    }

    std::cout << "\n------------------------Turmas------------------------" << endl;
    for(auto turmaSoQueIndividual = turmas.begin(); turmaSoQueIndividual != turmas.end(); turmaSoQueIndividual++){
        (*turmaSoQueIndividual)->print();
    }

    std::cout << "\n------------------------Salas------------------------" << endl;
    for(auto deposito = salas.begin(); deposito != salas.end(); deposito++){
        (*deposito)->print();
    }

}