#include "../Classes/objFunction.h"

int ObjFunction::objFunctionCalc(Solution* solution){

    this->sixthSlot = 0;
    this->gapDays = 0;
    this->gapWindow = 0;

    for(int i = 1; i < solution->grade.size(); i++){
        this->sixthSlot += objSixthSlot(&solution->grade[i]);
    }
    for(int i = 1; i < solution->teacher.size(); i++){
        this->gapDays += objGapDays(&solution->teacher[i]);
        this->gapWindow += objGapWindow(&solution->teacher[i]);
    }

    this->total = this->sixthSlot + this->gapWindow + this->gapDays;

    cout << this->total << endl;

    cout << "\nSextos horarios " << this->sixthSlot << "\nJanelas de horarios " << this->gapWindow << "\nJanela de dias " << this->gapDays << endl << endl; 

    solution->printGrade();
    solution->printTeacher();
    solution->printRoom(); 

    cout << endl << endl<< endl<< endl;

    return this->total;
}

int ObjFunction::objSixthSlot(Schedule* grade){

    int sixthSlot = 0;

    //Perhaps I shall adjust this value of I
    //but for now, I'll consider only Monday to Friday

    for(int i = 0; i < 5; i++){
        if(grade->schedule[i][5 || 11] > 0){
            sixthSlot++;
        }
    }

    return sixthSlot;
}

int ObjFunction::objGapWindow(Schedule* teacher){

    int gapWindow = 0;

    for(int i = 0; i < 6; i++){

        int firstSlot = 0;
        int lastSlot = 0;

        //If the resource has no activity in the given day, go to the next day
        if(workDays[i] == 0){
            continue;
        }

        //Manhã
        for(int j = 0; j < 6; j++){
            if(teacher->schedule[i][j] > 0){
                firstSlot = j;
                break;
            }
        }
        for(int j = 5; j >= 0; j--){
            if(teacher->schedule[i][j] > 0){
                lastSlot = j;
                break;
            }
        }

        for(int j = firstSlot+1; j < lastSlot; j++){
            if(teacher->schedule[i][j] <= 0){
                gapWindow++;
            }
        }

        firstSlot = 0;
        lastSlot = 0;

        //Tarde
        for(int j = 6; j < 12; j++){
            if(teacher->schedule[i][j] > 0){
                firstSlot = j;
                break;
            }
        }
        for(int j = 11; j >= 6; j--){
            if(teacher->schedule[i][j] > 0){
                lastSlot = j;
                break;
            }
        }

        for(int j = firstSlot+1; j < lastSlot; j++){
            if(teacher->schedule[i][j] <= 0){
                gapWindow++;
            }
        }

        firstSlot = 0;
        lastSlot = 0;


        //Noite
        for(int j = 12; j < 16; j++){
            if(teacher->schedule[i][j] > 0){
                firstSlot = j;
                break;
            }
        }
        for(int j = 15; j >= 12; j--){
            if(teacher->schedule[i][j] > 0){
                lastSlot = j;
                break;
            }
        }

        for(int j = firstSlot+1; j < lastSlot; j++){
            if(teacher->schedule[i][j] <= 0){
                gapWindow++;
            }
        }
    }

    cout << "\033[0m";

    if(gapWindow > 0){
        teacher->printSchedule();
        cout << "Gap Window para o professor " << teacher->name << " : " << gapWindow << endl;
        //getchar();
    }
    return gapWindow;
}

int ObjFunction::objGapDays(Schedule* teacher){

    for(int i = 0; i < 6; i++){
        this->workDays[i] = 0;
    }

    int gapDays = 0;
    int firstDay = 0;
    int lastDay = 5;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            if(teacher->schedule[i][j] > 0){
                workDays[i] = 1;
            }
        }
    }

    //Find the first and last day of activity
    for(int i = 0; i < 6; i++){
        if(workDays[i] == 1){
            firstDay = i;
            break;
        }
    }
    for(int i = 5; i >= firstDay; i--){
        if(workDays[i] == 1){
            lastDay = i;
            break;
        }
    }

    for(int i = firstDay+1; i < lastDay; i++){
        if(!workDays[i]){
            gapDays++;
        }
    }

    return gapDays;
}