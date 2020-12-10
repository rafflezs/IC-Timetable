#include "../Classes/schedule.h"

Schedule::Schedule(int dispo[6][16], string name){
	this->name = name;

    for(int i = 0; i < 6; i++){
    	for(int j = 0; j < 16; j++){
            schedule[i][j] = dispo[i][j];
            }
    }
}

void Schedule::printSchedule(){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            cout << setw(5) << schedule[i][j];
        }
    	cout << endl;
    }
    cout << endl;
}

bool Schedule::checkDisponibility(int day, int start, int end){

    for(int ts = start; ts < end; ts++){
        if(schedule[day][ts] != 0){
            return false;
        }
    }
    return true;
}

bool Schedule::checkConsecutive(int* day, int* firstSlot, int size, int dayStart, int slotStart, int slotEnd){

    for(int i = dayStart; i < 6; i++){
        for(int j = slotStart; j <= slotEnd-size; j++){
            if(checkDisponibility(i ,j, j+size)){
                *day = i;
                *firstSlot = j;
                return true;
            }
        }
    }
    return false;
}