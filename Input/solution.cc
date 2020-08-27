#include "../Classes/solution.h"

//Starts the first solution with all schedules unallocated
Solution::Solution(Data* d){
    for(auto i = d->teachers.begin(); i != d->teachers.end(); i++){
        teacher.push_back(Schedule((*i)->disponibility, (*i)->name));
    }
    for(auto i = d->grades.begin(); i != d->grades.end(); i++){
        grade.push_back(Schedule((*i)->disponibility, (*i)->name));
    }
    for(auto i = d->rooms.begin(); i != d->rooms.end(); i++){
        room.push_back(Schedule((*i)->disponibility, (*i)->name));
    }
}

//This segment calls each main resource its internal printSchedule function
void Solution::printGrade(){
    for(int i = 1; i < this->grade.size(); i++){
        cout << "\033[1m\033[31m" << grade[i].name << endl;
        grade[i].printSchedule();
    }
}

void Solution::printTeacher(){
    for(int i = 1; i < this->teacher.size(); i++){
        cout << "\033[1m\033[35m" << teacher[i].name << endl;
        teacher[i].printSchedule();
    }
}

void Solution::printRoom(){
    for(int i = 1; i < this->room.size(); i++){
        cout << "\033[1m\033[37m" << room[i].name << endl;
        room[i].printSchedule();
    }
}

//Insert disciplines in the main resource schedules as early as possible, if avaible
int Solution::insertEarly(Data* data, int discId){
    int teacherId = discToTeacher(data, discId);
    int gradeId = discToGrade(data, discId);

    if(teacherId == -1 || gradeId == -1){
        return 1;
    }

    int weekLimit = data->disciplines[discId]->workload;
    int dailyMin = data->disciplines[discId]->dailyMin;
    int split = data->disciplines[discId]->splits;
    int splitSize[split];

    for(int i = 0; i < split; i++){
        splitSize[i] = dailyMin;
    }

    for(int i = 0; i < weekLimit % (dailyMin * split); i++){
        splitSize[i%split]++;
    }

    set <int> tabooDays;
    int day, firstSlot;
    for(int i = 0; i <= split; i++){
        int roomId = roomToDisc(discId, data);
        if(this->checkConsecutive(&day, &firstSlot, splitSize[i], 0, 0, 16, tabooDays, this->teacher[teacherId], this->grade[gradeId],this->room[roomId])){
            tabooDays.insert(day);
            for(int slot = firstSlot; slot < firstSlot + splitSize[i]; slot++){
                
                //cout << "Disciplina inserida" << endl;

                this->grade[gradeId].schedule[day][slot] = discId;
                this->teacher[teacherId].schedule[day][slot] = discId;
                this->room[data->grades[gradeId]->room->id].schedule[day][slot] = discId;
                this->room[roomId].schedule[day][slot] = discId;
                this->grade[gradeId].discList.insert(discId);
            }
        return 0;
        }else{
            return 1;
        }
    }
    return 0;
}

bool Solution::checkConsecutive(int *day, int *firstSlot, int size, int dayStart, int slotStart, int slotEnd, set<int> tabooDays, Schedule teacher, Schedule grade, Schedule room){
    for(int i = dayStart; i < 6; i++){
        for(int j = slotStart; j <= slotEnd-size && !(tabooDays.count(i)) ; j++){
            if(grade.checkDisponibility(i, j, j+size) && teacher.checkDisponibility(i, j, j+size) /* && room.checkDisponibility(i, j, j+size) */){
                *day = i;
                *firstSlot = j;
                return true;
            }
        }
    }
    for(auto it = tabooDays.begin(); it != tabooDays.end(); it++){
        for(int j = slotStart; j <= slotEnd-size; j++){
            if(grade.checkDisponibility((*it), j, j+size) && teacher.checkDisponibility((*it), j, j+size) && room.checkDisponibility((*it), j, j+size)){
                *day = (*it);
                *firstSlot = j;
                return true;
            }
        }
    }
return false;
}

bool Solution::checkDisponibility(Schedule teacher, Schedule grade, Schedule room,int* day, int* start, int end){
    return teacher.checkDisponibility(*day, *start, end) && grade.checkDisponibility(*day, *start, end) && room.checkDisponibility(*day, *start, end);
}

int Solution::discToTeacher(Data* d, int discId){
    for(auto t = d->teachers.begin(); t != d->teachers.end(); t++){
        if((*t)->id == d->disciplines[discId]->teacherId){
            return (*t)->id;
        }
    }
    return -1;
}

int Solution::discToGrade(Data* d, int discId){
    for(auto g = d->grades.begin(); g != d->grades.end(); g++){
        if((*g)->id == d->disciplines[discId]->gradeId){
            return (*g)->id;
        }
    }
    return -1;
}

int Solution::roomToDisc(int discId, Data* data){
    int dayTime;
    if(data->disciplines[discId]->dayTime == "Manhã"){
        dayTime = 0;
    }else if(data->disciplines[discId]->dayTime == "Tarde"){
        dayTime = 1;
    }else if(data->disciplines[discId]->dayTime == "Noite"){
        dayTime = 2;
    }

    if(data->disciplines[discId]->spcfRoom == "Sala"){
        for(auto r = data->sala.begin(); r != data->sala.end(); r++){
            if((*r)->isUsed[dayTime] == false){
                return (*r)->id;
            }
        }
    }else if(data->disciplines[discId]->spcfRoom == "Lab"){
        for(auto r = data->lab.begin(); r != data->lab.end(); r++){
            if((*r)->isUsed[dayTime] == false){
            return (*r)->id;
            }
        }
    }else if(data->disciplines[discId]->spcfRoom == "Info"){
        for(auto r = data->info.begin(); r != data->info.end(); r++){
            if((*r)->isUsed[dayTime] == false){
            return (*r)->id;
            }
        }
    }else{
        for(int r = 1; r < data->rooms.size(); r++){
            if(data->disciplines[discId]->spcfRoom == data->rooms[r]->name && data->rooms[r]->isUsed[dayTime] == false){
            return data->rooms[r]->id;
            }
        }
    }
    return -1;
}