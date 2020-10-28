#ifndef _DATA_H
#define _DATA_H

#include "../class/curso.hpp"
#include "../class/disciplina.hpp"
#include "../class/turma.hpp"
#include "../class/sala.hpp"
#include "../class/professor.hpp"

#include <map>
#include <fstream>

using namespace std;

class Data{
    public:
        vector <Curso*> cursos;
        vector <Disciplina> disciplinas;
        vector <Turma> turmas;
        vector <Sala> salas;
        vector <Professor> professores;

        void imprimirDados(void*);

        /* 
        *  Esta seção declara os métodos de leitura, o qual
        *  lerDados() chama os outros metodos de leitura 
        *  especificos para cada tipo de dado
        */
        void lerDados();

        vector <Sala> lerSala();
        vector <Professor> lerProfessor(map<string, int> *mapProf);
        vector <Disciplina> lerDisc(map<string, int> *mapDisc);
        vector <Curso*> lerCurso();
        vector <Turma> lerTurma(map<string, int> *mapTurma, vector <Curso*> cursos);

        const vector <string> separadorString(const string& entrada, const char& operador);

        template <typename genericClass> 
        void disponibilidade(genericClass* objTemp, std::string* colunaDado, int dia);

        void relaciona(vector<Professor> professores, map<string, int> *mapDisc);
        void relaciona(vector<Disciplina> disciplinas, map<string, int> *mapProf, map<string, int> *mapTurma);
        void relaciona(vector<Turma> turmas, map<string, int> *mapProf, map<string, int> *mapDisc);

};

#endif //!_DATA_H