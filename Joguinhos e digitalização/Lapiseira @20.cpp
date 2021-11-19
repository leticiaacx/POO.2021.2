#include <iostream>
#include <vector>
#include <list>
#include <memory>

using namespace std;

class Grafite {
public:
    float calibre;
    int tamanho;
    string dureza;

    Grafite(float calibre, int tamanho, string dureza) : 
        calibre{calibre}, tamanho{tamanho}, dureza{dureza} {
    }
      
    friend ostream& operator<<(ostream& os, const Grafite& grafite) {
        os << "Calibre: " << grafite.calibre << "mm, " << endl;
        os << "Tamanho: " << grafite.tamanho << "mm, " << endl;
        os << "Dureza: " << grafite.dureza << "." << endl;
        return os;
    }
};

class Lapiseira {
public:
    shared_ptr<Grafite> bico;
    list<shared_ptr<Grafite>> tambor; 
    float calibre;

    Lapiseira(){
        this->bico = nullptr;
    }

    bool inserirGrafite(shared_ptr<Grafite> grafite){
        if (grafite->calibre != this->calibre){
            cout << "O calibre inserido nao e compativel" << endl;
            return false;
        }

       tambor.push_back(grafite);
        return true;
    }

    bool puxarGrafite(){
        if (this->bico != nullptr){
            cout << "remova primeiro o grafite!!" << endl;
            return false;
        }
        return true;
    }

    bool removerGrafite(int indice)
        {
            if (indice < 0)
            {
                cout << "Grafite nao existe" << endl;
                return false;
            }
            if (this->bico == nullptr)
            {
                cout << "Bico sem grafite" << endl;
                return false;
            }
            this->bico = nullptr;
            return true;
        }

    friend ostream &operator<<(ostream &os, const Lapiseira &lapiseira){
            os << "\nGrafite no tambor: | " << endl;
            for (auto tambor : lapiseira.tambor)
            {
                os << *tambor << " " << endl;
            }
            return os;
        }
};


int main () {

    Lapiseira lapiseira;

    cout << lapiseira << endl;
    lapiseira.inserirGrafite(make_shared<Grafite>(0.5, 20, "4B"));
    lapiseira.inserirGrafite(make_shared<Grafite>(1, 50, "HB"));
    lapiseira.inserirGrafite(make_shared<Grafite>(0.5, 20, "6B"));

    lapiseira.puxarGrafite();
    cout << lapiseira;
    lapiseira.puxarGrafite();
    cout << "\n";

    lapiseira.removerGrafite(1);
    lapiseira.removerGrafite(0);


    return 0;
}