#include "../Classes/input.h"

void start(){

    vector <Solution> scheduleList;

    cout << "Iniciando leitura de dados!" << endl;
    Data* d = new Data();
    d->read();
    d->discToTeacher();
    d->discToGrade();
    d->roomToClass();
    Solution* solution = new Solution(d);

    scheduleList = generateList(d, solution);
    cout << "Chegou aqui" << endl;
    for(int i = 1; i < scheduleList.size(); i++){
        timeSwap(&scheduleList[i], d);
        gradeSwap(&scheduleList[i], d);
        fixAndOptimize(&scheduleList[i], d);
    }

    //printSolution(scheduleList);

    cout << "Leitura finalizada!" << endl;

}

void printSolution(vector<Solution> scheduleList){
    
    for(int i = 0; i < scheduleList.size(); i++){
        cout << "\033[1m\033[33m Print da solução ["<< i <<"]" << endl;
        scheduleList[i].printTeacher();
        scheduleList[i].printGrade();
        scheduleList[i].printRoom();
    }
}

vector <Solution> generateList(Data* d, Solution* sol){

    vector <Solution> solution;

    solution.push_back(*sol);
    int i = 0;

    while(solution.size() <= 3 && i < 10000){

        Solution* temp = new Solution(d);
        switch (1 + rand() % 3){
        case 1:{
            //cout << "Solução: " << i+1 << " || Random Discipline" << endl;
            if(constructDisc(temp, d) == 0){
                //temp->printGrade();
                //getchar();
                cout << "\033[0m";
                cout << "Insert na Solution" << endl;
                solution.push_back(*temp);
            }else{
                delete temp;
            }
        }break;
        case 2:{
            //cout << "Solução: " << i+1 << " || Ordered by Teacher" << endl;
            if(constructTeacher(temp, d) == 0){
                //temp->printGrade();
                //getchar();
                cout << "\033[0m";
                cout << "Insert na Solution" << endl;
                solution.push_back(*temp);
            }else{
                delete temp;
            }
        }break;
        case 3:{
            //cout << "Solução: " << i+1 << " || Ordered by Grade" << endl;
            if(constructGrade(temp, d) == 0){
                //temp->printGrade();
                //getchar();
                cout << "\033[0m";
                cout << "Insert na Solution" << endl;
                solution.push_back(*temp);
            }else{
                delete temp;
            }
        }break;
        default:
            break;
        }
        cout << "Total de soluções semi-decentes: " << solution.size() << "|| Estamos na: " << i+1 << " iteracao" << endl;
        i++;
    }

    return solution;
}

int constructDisc(Solution* temp, Data* data){

    vector<int> list;
    list = generateRandomList(data, 1);

    //int list[] = {5,8,1,2,3,4,6,7,9,10,11,12,13,14,15,16,17,18,19,20,21,22};

    for(int d = 0; d < 22 /* list.size() */; d++){
        if(temp->insertEarly(data, list[d]) == 1)
            return 1;
    }

    return 0;
}

int constructTeacher(Solution* temp, Data* data){

    vector<int> list;
    list = generateRandomList(data, 2);

    //int list[] = {5,8,1,2,3,4,6,7,9,10,11,12,13,14,15,16,17,18,19,20,21,22};

    for(int d = 0; d < 22 /* list.size() */; d++){
        if(temp->insertEarly(data, list[d]) == 1)
            return 1;
    }

    return 0;
}

int constructGrade(Solution* temp, Data* data){

    vector<int> list;
    list = generateRandomList(data, 3);

    //int list[] = {5,8,1,2,3,4,6,7,9,10,11,12,13,14,15,16,17,18,19,20,21,22};

    for(int d = 0; d < 22 /* list.size() */; d++){
        if(temp->insertEarly(data, list[d]) == 1)
            return 1;
    }

    return 0;
}

vector <int> generateRandomList(Data* data,int constructMethod){

    vector <int> list;

    //Lucas pedofilos
    switch (constructMethod){
        case 1:{
            for(int i = 1; i < data->discSize; i++){
                list.push_back(i);
            }
        random_shuffle(list.begin(), list.end());
        }break;
        case 2:{
            vector<Teacher*> randTeacher = data->teachers;
            random_shuffle(randTeacher.begin(), randTeacher.end());
            for(auto t = randTeacher.begin(); t != randTeacher.end(); t++){
                for(auto d = (*t)->disc.begin(); d != (*t)->disc.end(); d++){
                    //cout << (*d)->id-1 << " | ";
                    list.push_back((*d)->id);
                }
            }
        }break;
        case 3:{
            vector<Grade*> randGrade = data->grades;
            random_shuffle(randGrade.begin(), randGrade.end());
            for(auto g = randGrade.begin(); g != randGrade.end(); g++){
                for(auto d = data->disciplines.begin(); d != data->disciplines.end(); d++){
                    for(auto disc = (*g)->disciplinesId.begin(); disc != (*g)->disciplinesId.end(); disc++){
                        if((*disc) == (*d)->id_if){
                            //cout << (*d)->id-1 << " | ";
                            list.push_back((*d)->id);
                        }
                    }
                }
            }
        }break;
    default: cout << "Operação inválida" << endl;
        break;
    }
    return list;
}