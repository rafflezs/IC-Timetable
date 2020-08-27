#ifndef _READ_H
#define _READ_H

#include "../Classes/discipline.h"
#include "../Classes/course.h"
#include "../Classes/teacher.h"
#include "../Classes/grade.h"
#include "../Classes/room.h"

#include "../Classes/dependencies.h"

using namespace std;

vector <Teacher*> readTeacher(vector <Discipline*> discplines);
vector <Course*> readCourse();
vector <Grade*> readGrade(vector <Course*> courses);
vector <Discipline*> readDiscipline(vector <Room*> rooms);
vector <Room*> readRoom();

void courseCheck(Grade* a, string* temp, vector <Course*> courses);
void discCheck(Teacher* a, string temp, vector <Discipline*> discplines);

void Coursedispo(Course* a, string* in, int day);
void Gradedispo(Grade* a, string* in, int day);
void Disciplinedispo(Discipline* a, string* in, int day);
void Roomdispo(Room* a, string* in, int day);
void Teacherdispo(Teacher* a, string* in, int day);

const vector<string> explode(const string& s, const char& c);

std::set <Room*> feasibleRoomList(vector <Room*> rooms);

#endif