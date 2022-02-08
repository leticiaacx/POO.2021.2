#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

using namespace std;

class Grafite { //criando o grafite
public:
    float calibre;
    int tamanho;
    string dureza;

    Grafite(float calibre, int tamanho, string dureza) : 
        calibre{calibre}, tamanho{tamanho}, dureza{dureza} {
    }// objeto grafite criado

    ~Grafite() {}// destrutor do Grafite

    int papel(){ // dureza do grafite
        if (this->dureza == "HB"){
            return 1;
        } else if (this->dureza == "2B") {
            return 2;
        } else if (this->dureza == "4B") {
            return 3;
        } else if (this->dureza == "6B"){
            return 4;
        } else {
            cout << "Invalido" << endl;
            return 0;
        }
    }

    float getCalibre(){
        return this->calibre;
    }

    int getTamanho(){
        return this->tamanho;
    }

    string getDureza(){
        return this->dureza;
    }

    friend ostream& operator<<(ostream& os, const Grafite& grafite) { // impressão 
        os << "Calibre: " << grafite.calibre << "mm, " << endl;
        os << "Tamanho: " << grafite.tamanho << "mm, " << endl;
        os << "Dureza: " << grafite.dureza << "." << endl;
        return os;
    }
};

class Lapiseira { // lapiseira 
public:
    shared_ptr<Grafite> bico; // o bico, onde todos os graficos estão 
    list<shared_ptr<Grafite>> tambor;  // usando a lista para usar os metodos de push para inserir grafite
    float calibre{0};

    Lapiseira(float dureza = 0) :
        calibre{calibre} {} // contrutor 

    ~Lapiseira(){} // destrutor

    bool inserirGrafite(const shared_ptr<Grafite> grafite){// inserir grafite
        if (grafite->calibre != this->calibre){ 
            cout << "O calibre inserido nao e compativel" << endl;
            return false;
        }

       tambor.push_back(grafite);// inserindo o grafite no final da lista 
        return true;
    }

    bool puxarGrafite(){ 
        if (this->bico != nullptr){ //
            cout << "remova primeiro o grafite!!" << endl;// avisando que precisa remover o grafite primeiro
            return false;
        }

        this->bico = this->tambor.front(); // imprime
        this->tambor.pop_front(); // retira   
        return true;
    }

    bool removerGrafite(int indice){
        if (indice < 0 || indice >= this->tambor.size()) { // verificando a existencia
            cout << "Grafite nao existe" << endl;
            return false;
        }
        if (this->bico == nullptr){ // nullptr pq ta vazio
            cout << "Bico sem grafite" << endl;
            return false;
        }
        this->bico = nullptr;// removendo
        return true;
    }

    void escrever(){ // escrevendo
        if (this->bico == nullptr){ 
            cout << "Nao tem grafite na lapiseira" << endl;
        } else if (this->bico->tamanho <= 10) { //grafite menor que 10 
            cout << "Nao pode mais escrever! Grafite insuficiente  " << endl;
        } else {
            this->bico->papel();
            cout << "Escrevendo..." << endl;
        }
    }

    friend ostream &operator<<(ostream &os, const Lapiseira &lapiseira){
        os << "Grafite no bico: ; " << endl;// Mostrar grafite
        for (int i = 0; i < (int)lapiseira.bico->tamanho; i++){
            auto &it = lapiseira.bico;
            os << i << " : ";
            if (it != nullptr) {
                os << *it;
            }
        }
        os << "Grafite no tambor:  " << endl;
        for (auto tambor : lapiseira.tambor){
            os << *tambor << " ";
        }
        return os;
    }
};


int main () { //testes

    Lapiseira lapiseira;

    cout << lapiseira << endl;
    lapiseira.inserirGrafite(make_shared<Grafite>(0.5, 20, "4B"));
    lapiseira.inserirGrafite(make_shared<Grafite>(1, 50, "HB"));
    lapiseira.inserirGrafite(make_shared<Grafite>(0.5, 20, "6B"));
    lapiseira.escrever();

    lapiseira.puxarGrafite();
    cout << lapiseira;
    lapiseira.puxarGrafite();
    cout << "\n";

    lapiseira.removerGrafite(1);
    lapiseira.removerGrafite(0);

    cout << lapiseira << endl;

    return 0;
}