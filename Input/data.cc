#include "../Classes/data.h"

void Data::read(){

    /*
     *This function holds all the vector for the software,
     *by calling each corresponding readVector function
     *and storing its data in each specified container.
    */

    this->courses = readCourse();
    this->grades = readGrade(courses);
    this->rooms = readRoom();
    this->disciplines = readDiscipline(rooms);
    this->teachers = readTeacher(disciplines);

    this->roomSize = rooms.size();
    this->discSize = disciplines.size();
    this->courseSize = courses.size();
    this->gradeSize = grades.size();
    this->teacherSize = teachers.size();

    this->classifyRoom();

}

void Data::discToTeacher(){
    for(int disc = 0; disc != this->disciplines.size(); disc++){
        for(int t = 0; t != this->teachers.size(); t++){
            if(disciplines[disc]->teacherName == teachers[t]->name){
                disciplines[disc]->teacherId = teachers[t]->id;
            }
        }
    }
}

void Data::discToGrade(){
    for(auto disc = this->disciplines.begin(); disc != this->disciplines.end(); disc++){
        for(auto t = this->grades.begin(); t != this->grades.end(); t++){
            if((*disc)->gradeName == (*t)->id_if){
                (*disc)->gradeId = (*t)->id;
            }
        }
    }
}

//Comparar as turmas:
//Exemplo. BCC 1 e 3 podem usar a mesma sala já que são de horarios diferentes

void Data::roomToClass(){
    for(int g = 1; g < grades.size(); g++){
        for(int r = 1; r < rooms.size(); r++){
            if((grades[g]->dayTime == "Manhã" && rooms[r]->isUsed[0] == false) && rooms[r]->type == "Sala"){
                grades[g]->room = rooms[r];
                rooms[r]->gradeId = grades[g]->id;
                rooms[r]->isUsed[0] = true;
                break;
            }else if((grades[g]->dayTime == "Tarde" && rooms[r]->isUsed[1] == false) && rooms[r]->type == "Sala"){
                grades[g]->room = rooms[r];
                rooms[r]->isUsed[1] = true;
                rooms[r]->gradeId = grades[g]->id;
                break;
            }else if((grades[g]->dayTime == "Noite" && rooms[r]->isUsed[2] == false) && rooms[r]->type == "Sala"){
                grades[g]->room = rooms[r];
                rooms[r]->isUsed[2] = true;
                rooms[r]->gradeId = grades[g]->id;
                break;
            }
        }
    }
}

void Data::classifyRoom(){
    for(int r = 1; r != rooms.size(); r++){
        if(rooms[r]->type == "Sala"){
            sala.push_back(rooms[r]);
        }else if(rooms[r]->type == "Info"){
            info.push_back(rooms[r]);
        }else if(rooms[r]->type == "Lab"){
            lab.push_back(rooms[r]);
        }
    }
}