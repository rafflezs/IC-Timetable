#include "./engine/metaheuristica.hpp"

int main(){

    srand( time( NULL ) );
/*     std::cout << "\n\nEmanuel eu vou dizer a n-word\n\n";
    Metaheuristica* meta = new Metaheuristica();
    std::cout << "\n\nEmanuel eu vou dizer a n-word\n\n"; */

    Solucao teste = Solucao();

    cout << "------------------------------------------------------------------------" << endl;

    for(auto a = teste.discSol.begin(); a != teste.discSol.end(); a++){
        
        for(auto s = a->second->sala.begin(); s != a->second->sala.end(); s++) (*s)->print();
        for(auto s = a->second->lab.begin(); s != a->second->lab.end(); s++) (*s)->print();
        cout << endl << endl;
    }
}