#include "../Classes/read.h"

vector <Teacher*> readTeacher(vector <Discipline*> discplines){

    vector <Teacher*> teachers;

    vector <string> data;
    ifstream file;
    file.open("/home/rafflezs/Documentos/IC2020 - uniTimetable/Data/Professores.csv");

    string temp;

    getline(file, temp, '\n');
    
    //This section creates a "phantom Data", for better code purposes
    Teacher* tempInp = new Teacher();
    tempInp->id = 0;
    tempInp->id_if = "nullData";
    tempInp->name = "nullData";
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            tempInp->disponibility[i][j] = -1;
        }
    }
    teachers.push_back(tempInp);
    int id = 1;
    while(file.good()){

            Teacher* inp = new Teacher();

            getline(file, temp, '\n');
            data = explode(temp, ';');

            if(data.size() <= 0){
                break;
            }

            inp->id = id;
            inp->id_if = data[0];
            inp->name = data[1];          

            discCheck(inp, data[2], discplines);

            Teacherdispo(inp, &data[3], 0);
            Teacherdispo(inp, &data[4], 1);
            Teacherdispo(inp, &data[5], 2);
            Teacherdispo(inp, &data[6], 3);
            Teacherdispo(inp, &data[7], 4);
            Teacherdispo(inp, &data[8], 5);
            id++;
            teachers.push_back(inp);
    }

    return teachers;
}

vector <Course*> readCourse(){

    vector <Course*> courses;

    ifstream file;
    file.open("/home/rafflezs/Documentos/IC2020 - uniTimetable/Data/Cursos.csv");

    string temp;

    getline(file, temp, '\n');

    //This section creates a "phantom Data", for better code purposes
    Course* tempInp = new Course();
    tempInp->id = 0;
    tempInp->id_if = "nullData";
    tempInp->name = "nullData";
    tempInp->degree = "nullData";
    tempInp->grades = "nullData";
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            tempInp->disponibility[i][j] = -1;
        }
    }
    courses.push_back(tempInp);
    int id = 1;
    while(file.good()){
            Course* inp = new Course();
            getline(file, temp, '\n');
            vector <string> data = explode(temp, ';');

            if(data.size() <= 0){
                break;
            }

            inp->id = id;
            inp->id_if = data[0];
            inp->name = data[1];
            inp->degree = data[2];
            inp->grades = data[3];

            Coursedispo(inp, &data[4], 0);
            Coursedispo(inp, &data[5], 1);
            Coursedispo(inp, &data[6], 2);
            Coursedispo(inp, &data[7], 3);
            Coursedispo(inp, &data[8], 4);
            Coursedispo(inp, &data[9], 5);
            id++;
            courses.push_back(inp);
        }

    return courses;

}

vector <Grade*> readGrade(vector <Course*> courses){

    vector <Grade*> grades;

    ifstream file;
    file.open("/home/rafflezs/Documentos/IC2020 - uniTimetable/Data/Turmas.csv");

    string temp;

    getline(file, temp, '\n');

    //
    Grade* tempInp = new Grade();
    tempInp->id = 0;
    tempInp->id_if = "nullData";
    tempInp->name = "nullData";
    tempInp->course = NULL;
    tempInp->dayTime = "nullData";
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            tempInp->disponibility[i][j] = -1;
        }
    }
    grades.push_back(tempInp);    //
    int id = 1;
    while(file.good()){
            Grade* inp = new Grade();
            getline(file, temp, '\n');
            vector <string> data = explode(temp, ';');

            if(data.size() <= 0){
                break;
            }

            inp->id = id;
            inp->id_if = data[0];
            inp->name = data[1];
            courseCheck(inp, &data[2], courses);
            inp->dayTime = data[3];
            inp->disciplinesId = explode(data[4],','); //Change this to read column 0 /integer ID

            Gradedispo(inp, &data[5],0);
            Gradedispo(inp, &data[6],1);
            Gradedispo(inp, &data[7],2);
            Gradedispo(inp, &data[8],3);
            Gradedispo(inp, &data[9],4);
            Gradedispo(inp, &data[10],5);
            id++;
    grades.push_back(inp);

    }

    return grades;
}


vector <Discipline*> readDiscipline(vector <Room*> room){

    vector <Discipline*> disciplines;

    ifstream file;
    file.open("/home/rafflezs/Documentos/IC2020 - uniTimetable/Data/Disciplinas.csv");

    string temp;

    getline(file, temp, '\n');

    //
    Discipline* tempInp = new Discipline();
    tempInp->id = 0;
    tempInp->id_if = "Horario Vazio";
    tempInp->name = "Horario Vazio";
    tempInp->teacherName = "nullData";
    tempInp->courseName = "nullData";
    tempInp->gradeName = "nullData";
    tempInp->dayTime = "nullData";
    tempInp->spcfRoom = "nullData";
    tempInp->studentsLimit = 0;
    tempInp->workload = 0;
    tempInp->dailyMin = 0;
    tempInp->splits = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            tempInp->disponibility[i][j] = -1;
        }
    }
    disciplines.push_back(tempInp);    //

    int id = 1;
    while(file.good()){
            Discipline* inp = new Discipline();
            getline(file, temp, '\n');
            vector <string> data = explode(temp, ';');

            if(data.size() <= 0){
                break;
            }

            inp->id = id;
            inp->id_if = data[0];
            inp->name = data[1];
            inp->teacherName = data[2];
            inp->courseName = data[3];
            inp->gradeName = data[4];
            inp->dayTime = data[5];
            inp->spcfRoom = data[6];
            inp->studentsLimit = stoi(data[7]);
            inp->workload = stoi(data[8]);
            inp->dailyMin = stoi(data[9]);
            inp->splits = stoi(data[10]);

            Disciplinedispo(inp, &data[11], 0);
            Disciplinedispo(inp, &data[12], 1);
            Disciplinedispo(inp, &data[13], 2);
            Disciplinedispo(inp, &data[14], 3);
            Disciplinedispo(inp, &data[15], 4);
            Disciplinedispo(inp, &data[16], 5);

            //inp->possibleRoomList = feasibleRoomList(rooms);
            id++;
            disciplines.push_back(inp); 
    }

    return disciplines;

}

//Ok
vector <Room*> readRoom(){

    vector <Room*> rooms;

    ifstream file;
    file.open("/home/rafflezs/Documentos/IC2020 - uniTimetable/Data/Salas.csv");

    string temp;

    getline(file, temp, '\n');

    //
    Room* tempInp = new Room();
    tempInp->id = 0;
    tempInp->id_if = "nullData";
    tempInp->name = "nullData";
    tempInp->block = "nullData";
    tempInp->capacity = 0;
    tempInp->type = "nullData";
    tempInp->isUsed[0] = tempInp->isUsed[1] = tempInp->isUsed[2] = true;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 16; j++){
            tempInp->disponibility[i][j] = -1;
        }
    }
    rooms.push_back(tempInp);    //

    int id = 1;
    while(file.good()){
            Room* inp = new Room();
            getline(file, temp, '\n');
            vector <string> data = explode(temp, ';');

            if(data.size() <= 0){
                break;
            }

            inp->id = id;
            inp->id_if = data[0];
            inp->name = data[1];
            inp->block = data[2];
            inp->capacity = stoi(data[3]);
            inp->type = data[4];

            Roomdispo(inp, &data[5], 0);
            Roomdispo(inp, &data[6], 1);
            Roomdispo(inp, &data[7], 2);
            Roomdispo(inp, &data[8], 3);
            Roomdispo(inp, &data[9], 4);
            Roomdispo(inp, &data[10], 5);

            inp->isUsed[0] = inp->isUsed[1] = inp->isUsed[2] = false;

            rooms.push_back(inp); 
    }

    return rooms;
}

void courseCheck(Grade* a, string* temp, vector <Course*> courses){

    vector <Course*>::iterator i;

    for(i = courses.begin(); i != courses.end(); i++){
        if((*i)->id_if == *temp){
            a->course = (*i);
        }
    }

}

void discCheck(Teacher* a, string temp, vector <Discipline*> discplines){

    vector <Discipline*>::iterator d = discplines.begin();
    vector <string> disc = explode(temp, ',');

    int i = 0;

    for(d; d != discplines.end(); d++){
        if((*d)->id_if == disc[i]){
            a->disc.push_back((*d));
            (*d)->teacherId = a->id;
            i++;
        }if(i >= disc.size()){
            break;
        }
    }

}


void Disciplinedispo(Discipline *a, string* in, int day){

    vector<string> startArray, endArray;
    startArray = explode(*in, ',');
    if(startArray[0] == "0"){
        startArray[0] = "17";
    }else{
        for(auto n:startArray){
            if(n.length()>2){
                vector<string> temp;
                string  tempWord;
                temp = explode(n, '-');
                int start, end;
                start = stoi(temp[0]); 
                end = stoi(temp[1]);
                for(int i = start; i <= end; i++){
                    tempWord = to_string(i);
                    endArray.push_back(tempWord);
                }
            }else{
                endArray.push_back(n);
            }
        }
        for(int i = 0; i < 16; i++){
            a->disponibility[day][i] = 0;
        }
    }
    for(auto n:endArray){
            a->disponibility[day][stoi(n)-1] = -1;
    }
}

void Gradedispo(Grade *a, string* in, int day){

    vector<string> startArray, endArray;
    startArray = explode(*in, ',');
    if(startArray[0] == "0"){
        startArray[0] = "17";
    }else{
        for(auto n:startArray){
            if(n.length()>2){
                vector<string> temp;
                string  tempWord;
                temp = explode(n, '-');
                int start, end;
                start = stoi(temp[0]); 
                end = stoi(temp[1]);
                for(int i = start; i <= end; i++){
                    tempWord = to_string(i);
                    endArray.push_back(tempWord);
                }
            }else{
                endArray.push_back(n);
            }
        }
        for(int i = 0; i < 16; i++){
            a->disponibility[day][i] = 0;
        }
    }
    for(auto n:endArray){
            a->disponibility[day][stoi(n)-1] = -1;
    }
}

void Coursedispo(Course *a, string* in, int day){

    vector<string> startArray, endArray;
    startArray = explode(*in, ',');
    if(startArray[0] == "0"){
        startArray[0] = "17";
    }else{
        for(auto n:startArray){
            if(n.length()>2){
                vector<string> temp;
                string  tempWord;
                temp = explode(n, '-');
                int start, end;
                start = stoi(temp[0]); 
                end = stoi(temp[1]);
                for(int i = start; i <= end; i++){
                    tempWord = to_string(i);
                    endArray.push_back(tempWord);
                }
            }else{
                endArray.push_back(n);
            }
        }
        for(int i = 0; i < 16; i++){
            a->disponibility[day][i] = 0;
        }
    }
    for(auto n:endArray){
            a->disponibility[day][stoi(n)-1] = -1;
    }
}

void Roomdispo(Room *a, string* in, int day){

    vector<string> startArray, endArray;
    startArray = explode(*in, ',');
    if(startArray[0] == "0"){
        startArray[0] = "17";
    }else{
        for(auto n:startArray){
            if(n.length()>2){
                vector<string> temp;
                string  tempWord;
                temp = explode(n, '-');
                int start, end;
                start = stoi(temp[0]); 
                end = stoi(temp[1]);
                for(int i = start; i <= end; i++){
                    tempWord = to_string(i);
                    endArray.push_back(tempWord);
                }
            }else{
                endArray.push_back(n);
            }
        }
        for(int i = 0; i < 16; i++){
            a->disponibility[day][i] = 0;
        }
    }
    for(auto n:endArray){
            a->disponibility[day][stoi(n)-1] = -1;
    }
}

void Teacherdispo(Teacher *a, string* in, int day){

    vector<string> startArray, endArray;
    startArray = explode(*in, ',');
    if(startArray[0] == "0"){
        startArray[0] = "17";
    }else{
        for(auto n:startArray){
            if(n.length()>2){
                vector<string> temp;
                string  tempWord;
                temp = explode(n, '-');
                int start, end;
                start = stoi(temp[0]); 
                end = stoi(temp[1]);
                for(int i = start; i <= end; i++){
                    tempWord = to_string(i);
                    endArray.push_back(tempWord);
                }
            }else{
                endArray.push_back(n);
            }
        }
        for(int i = 0; i < 16; i++){
            a->disponibility[day][i] = 0;
        }
    }
    for(auto n:endArray){
            a->disponibility[day][stoi(n)-1] = -1;
    }
}
const vector<string> explode(const string& s, const char& c){
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

/* std::set <Room*> feasibleRoomList(vector <Room*> rooms){

    set <Room*> roomSet;



    return roomSet;
} */