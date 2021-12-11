#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
/* 1. Usar o vector é melhor, pois ele é mais economico e o acesso a memoria é muito mais simples.
   o processador irá trabalhar melhor se vc estiver trabalhando com o vector
*/
using namespace std;

int main()
{  
    /*vector<int> vet;
    vet.reserve(10);// Quero que vc aloque memoria suficiente para guardar 10 elementos

    list<int> list{10, 100, 110, 120, 130, 140};
    auto iterator = list.begin();
    advance(iterator, 2);
    // o advance faz a propria variavel andar, aqui eu faço manualmente

    iterator = next(iterator, 3);// pulou do 0, 10, pro 3, o 120
    // o next ele anda e retorna o novo elemento

    cout << *iterator << endl;*/

    /*unordered_set<int> set; // isso é um conjunto, tempo constante
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(2);

    for (auto it = set.begin(); it != set.end(); ++it){
        cout << *it << endl;
    }

    auto it = set.find(3);
    if (it == set.end()){
        cout<< "No element" << endl;
    } else{
        cout << "Found 3" << endl; 
        set.erase(it);  
    }*/

    unordered_map<string, int> amigos;// operação com mapa 
    amigos.insert(make_pair("Joao", 33));// sintaxe tupla, nova do c++, aqui ta explicito
    amigos.insert({"Rafa", 39});// mesma coisa, aqui ta implicito
    amigos.insert({"Jose", 40});  
    amigos.insert({"Ana", 37});

    auto it = amigos.find("Rafa");
    if(it == amigos.end()){
        cout << "Rafa nao existente" <<  endl;
    } else{ 
        it->second = 44;
        cout << "Rafa existente" << endl;
        amigos.erase(it);
    }

    for(auto& [name, age] : amigos){
        cout << name << " " << age << endl;
    }
    
}