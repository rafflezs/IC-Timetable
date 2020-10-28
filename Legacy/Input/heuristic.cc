#include "../Classes/heuristic.h"

void gradeSwap(Solution* solution, Data* data){

    cout << "Inicio da gradeSwap" << endl << endl;

    cout << "Gerando nova turma" << endl;
    int randomGrade = getGrade(data);
    cout << "Gerou uma nova turma com sucesso: " << randomGrade << endl;

    Solution* tempSolution = new Solution(*solution);
    deallocateResource(tempSolution, data, &randomGrade);

    cout << "Desalocado para a turma" << data->grades[randomGrade]->name << endl;
    tempSolution->printTeacher();
    tempSolution->printGrade();
    //getchar();

    vector <int> discIdRand = randomizeSetJustBecause(solution->grade[randomGrade].discList);

    for(auto discId = discIdRand.begin(); discId != discIdRand.end(); discId++){
        tempSolution->insertEarly(data, *discId);
    }

    ObjFunction a;
    if(a.objFunctionCalc(solution) > a.objFunctionCalc(tempSolution)){
        cout << "Melhoria encontrada!" << endl;
        solution = tempSolution;
    }
}

void timeSwap(Solution* solution, Data* data){
    
    cout << "Inicio da timeSwap()" << endl;

    int randomGrade = getGrade(data);
    Solution* tempSolution = new Solution(*solution);

    vector <int> discIdRand = randomizeSetJustBecause(solution->grade[randomGrade].discList);


    int tempIndex = rand() % solution->grade[randomGrade].discList.size();
    int discId = discIdRand[tempIndex], swapDisc, swapFirstSlot;
    int mainSplit = 0, mainFirstSlot, mainDiscDay;

    cout << "Turma " << data->grades[randomGrade]->name << " e disciplina " << data->disciplines[discId]->name << endl;
    /* cout << "Discplina: " << data->disciplines[discId]->name << " | "
        << data->disciplines[discId]->id << " | " << data->disciplines[discId]->gradeName << endl << endl;
    tempSolution->printGrade(); */

    set <int> tabooDays;
    do{
        int randomDay = rand() % 5;
        if(!tabooDays.count(randomDay))
            mainSplit = findSplit(&randomDay, &discId, 
            &tempSolution->grade[randomGrade], &tempSolution->teacher[data->disciplines[discId]->teacherId], 
            &mainFirstSlot, &mainDiscDay);
        tabooDays.insert(randomDay);
    } while (mainSplit == 0);
    cout << mainSplit << endl;


    int dayTime;
    if(data->disciplines[discId]->dayTime == "Manhã"){
        dayTime = 0;
    }
    if(data->disciplines[discId]->dayTime == "Tarde"){
        dayTime = 1;
    }
    if(data->disciplines[discId]->dayTime == "Noite"){
        dayTime = 2;
    }


    int randomDay;
    int counter = 0;
    do{
        randomDay = rand() % 5;
        swapDisc = fitDisc(&swapFirstSlot ,&randomDay, &mainFirstSlot, 
        &tempSolution->grade[randomGrade], &tempSolution->teacher[data->disciplines[discId]->teacherId], &mainSplit);
        counter++;
    } while (swapDisc == -1 && counter < 20);

    int secSplit = mainSplit;
/* 
    cout << "Disciplina substituta " << swapDisc << " no dia " << randomDay << " no horario " << swapFirstSlot << endl << endl;
    cout << "pela discplina" << swapDisc << " | " << data->disciplines[swapDisc]->name << endl;
    cout << "Antes da troca" << endl;
    tempSolution->printGrade(); */
    //getchar();
    if(counter < 20){
        for(mainFirstSlot; secSplit > 0; secSplit--, mainFirstSlot++){
            tempSolution->grade[randomGrade].schedule[mainDiscDay][mainFirstSlot] = swapDisc;
        }
        for(swapFirstSlot; mainSplit > 0; mainSplit--, swapFirstSlot++){
            tempSolution->grade[randomGrade].schedule[randomDay][swapFirstSlot] = discId;
        }
    }else{
        for(mainFirstSlot; mainSplit > 0; mainSplit--, mainFirstSlot++){
            tempSolution->grade[randomGrade].schedule[mainDiscDay][mainFirstSlot] = discId;
        }
        for(swapFirstSlot; secSplit > 0; secSplit--, swapFirstSlot++){
            tempSolution->grade[randomGrade].schedule[randomDay][swapFirstSlot] = swapDisc;
        }
    }
    cout << "Pos-troca" << endl;
    tempSolution->printGrade();
    //getchar();


    ObjFunction a;
    if(a.objFunctionCalc(solution) > a.objFunctionCalc(tempSolution)){
        cout << "Melhoria encontrada" << endl;
        solution = tempSolution;
    }
}

//Seleciona um split aleatorio de um dia aleatorio de dada disciplina e retorna o tamanho dele
int findSplit(int* randomDay, int* discId, Schedule* gradeSc, Schedule* teacherSc, int* mainFirstSlot, int* mainDiscDay){
    int mainSplit = 0;
    for(int j = 0, i = 0; j < 16; j++){
        if(gradeSc->schedule[*randomDay][j] == *discId){
            cout << "Horario " << j << " do dia " << *randomDay << endl;
/*             teacherSc->schedule[*randomDay][j] = 0;
            gradeSc->schedule[*randomDay][j] = 0; */
            mainSplit++;
            if(i == 0){
                i++;
                *mainDiscDay = *randomDay;
                *mainFirstSlot = j;
            }
        }
    }

    return mainSplit;
}

//Retorna o horario do dia da disciplina substituta
int fitDisc(int* swapFirstSlot, int* randomDay, int* mainFirstSlot, Schedule* gradeSc, Schedule* teacherSc, int* mainSplit){

    int swapSplit = 0;

    for(int j = 0, i = 0; j < 16; j++){
        if(swapSplit == *mainSplit){
            return gradeSc->schedule[*randomDay][j-1];
        }
        if(((gradeSc->schedule[*randomDay][j+1] == gradeSc->schedule[*randomDay][j]) && gradeSc->schedule[*randomDay][j+1] > 0) && gradeSc->schedule[*randomDay][j] != -1){
            swapSplit++;
            gradeSc->schedule[*randomDay][j] = 0;
            if(i == 0){
                i++;
                *swapFirstSlot = j;
            }
        }else{
            swapSplit = 0;
        }
    }

    return -1;
}

void fixAndOptimize(Solution* solution, Data* data){

    typedef struct quickDisc{
        int discId = 0;
        int split = 0;
    }QuickDisc;

    cout << "Inicio da fixAndOptimize()" << endl;

    int randomGrade = getGrade(data);
    int secondGrade = getGrade(data);
    while (data->grades[randomGrade]->dayTime != data->grades[secondGrade]->dayTime){
        secondGrade = getGrade(data);
    }
    Solution* tempSolution = new Solution(*solution);

    for(int g = 1; g < data->gradeSize; g++){
        if(g == randomGrade || g == secondGrade){
            continue;
        }else{
            deallocateResource(tempSolution, data, &g);
            vector<int> discList = randomizeSetJustBecause(solution->grade[g].discList);
            for(auto discId = discList.begin(); discId != discList.end(); discId++){
                tempSolution->insertEarly(data, *discId);
            }
        }
    }

    ObjFunction a;
    if(a.objFunctionCalc(solution) > a.objFunctionCalc(tempSolution)){
        cout << "Melhoria encontrada" << endl;
        solution = tempSolution;
    }
}

//Zera todos os recursos que tem haver com a turma que foi selecionada
void deallocateResource(Solution* solution, Data* data, int* gradeId){

    int discId;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            if(solution->grade[*gradeId].schedule[i][j] > 0){
                discId = solution->grade[*gradeId].schedule[i][j]-1;
                solution->teacher[data->disciplines[discId]->teacherId].schedule[i][j] = 0;
                solution->grade[*gradeId].schedule[i][j] = 0;
            }
        }
    }

    for(auto room = solution->room.begin(); room != solution->room.end(); room++){
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 16; j++){
                if(solution->grade[*gradeId].discList.count((*room).schedule[i][j])){
                    (*room).schedule[i][j] = 0;
                    //cout << "Sala: " << (*room).name << "Turma: " << solution->grade[gradeId].name << endl;
                    //getchar();
                }
            }
        }
    }
}

vector <int> randomizeSetJustBecause(set <int> discList){

    vector <int> discVector;

    for(auto it = discList.begin(); it != discList.end(); it++){
        discVector.push_back((*it));
    }

    std::random_shuffle(discVector.begin(), discVector.end());

    return discVector;
}

int getGrade(Data* data){

    int grade = rand() % data->gradeSize;

    if(grade != 0){
        return grade;
    }
    return getGrade(data);
}