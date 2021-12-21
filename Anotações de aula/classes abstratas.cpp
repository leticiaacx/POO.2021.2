#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Corredor{
protected:
    string name;
    float x { 0 };

public: 

    Corredor(string name) : name(name){
    }
    // função virtual pura
    virtual void correr() = 0;
    float getX() { return x; }
    string getName(){
        return name;
    }
};

class Consistente : public Corredor{
public:

    Consistente(string name) : Corredor(name){
    }
 // esse override é uma marcação que explicita que esse metodo ta sendo sobre
//escrito do metodo corredor
    void correr() override {
        x++;
    }
};

class Inconsistente : public Corredor{
public:

    Inconsistente(string name) : Corredor(name){
    }

    void correr() override {
        if(rand() % 2)
        x += 2;
    }
};

class Progressivo : public Corredor{
protected:
    float inc { 0.1 }; 

public:
    
    Progressivo(string name, float inc) : Corredor(name),inc( inc ){
    }
    void correr() override { 
        x -= inc;
        inc *= 2;
    }
};

class Corrida {
    vector<Corredor*> corrida;
    float instancia { 0 };

public:

    Corrida(float instancia) : instancia(instancia){}
    void addCorredores(Corredor *corredor){
        corrida.push_back(corredor);
    }

    void correr() {
        for(int i = 0; i<instancia; i++){
            for(auto corredor : corrida){
                corredor->correr();
            }
        }
    }

    void imprimir() {
        for(auto corredor : corrida){
            cout << corredor->getName() << " : " < corredor->getX() << endl;
        }
    }


};

int main()
{  


}