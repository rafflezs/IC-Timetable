#include "./engine/solucao.hpp"

int main(){

    Solucao sol;

    for(auto t = sol.horarioTurma.begin(); t != sol.horarioTurma.end(); t++){
        cout << t->second->salaBase.nome << endl;
    }

}