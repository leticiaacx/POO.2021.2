#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

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

class DickyVigarista : public Inconsistente{
public: 
    DickyVigarista() : Inconsistente( "DickyVigarista" ){}
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
    float distancia { 0 };

public:

    Corrida(float distancia) : distancia(distancia){}
    void addCorredores(Corredor *corredor){
        corrida.push_back(corredor);
    }

    void correr() {
        for(int i = 0; i<distancia; i++){
            for(auto corredor : corrida){
                corredor->correr();
            }
        }
    }

// wrapper -> é um empacotador
    bool acabou(){
        for(auto corredor : corrida){
            if(corredor->getX() >= distancia){
                auto answer = dynamic_cast<DickyVigarista*>(corredor);// o cast dinamico é feito pra tentar
                // tranformar dinamicamento o "corredor" ser o dickyVigarista e ele vai me retornar um objeto
                // do tipo que eu desejo ou nullptr
                if(answer){
                    cout << "Dicky Vigarista ganhou!" << endl;
                    return true;
                }
                distancia = corredor->getX() + 1;
            }
        }
        return false;
    }

    void imprimir() {
        for(auto corredor : corrida){
            cout << corredor->getName() << " : " << corredor->getX() << endl;
        }
    }
};

int main()
{  
    srand(time(NULL));
    Corrida corrida(10);
    Consistente jao("Joao");
    Inconsistente pedro("Pedro");
    Progressivo lia("Lia", 0.1);
    DickyVigarista vigarista;
    corrida.addCorredores(&jao);
    corrida.addCorredores(&pedro);
    corrida.addCorredores(&lia);
    corrida.addCorredores(&vigarista);
    corrida.correr();
    return 0;

}