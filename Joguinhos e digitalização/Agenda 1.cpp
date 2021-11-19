#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <list>

using namespace std;

class Fone{
private:
    string id;
    string number;

public:
    Fone(string id = "", string number = "") : id{id}, number{number}{
    }

    string getId(){
        return this->id;
    }

    string getNumber(){
        return this->number;
    }
    
    static bool validate(string number){
        int sun = 0;
        for (int i = 0; i < 9; i++){
            sun += number[i] * (10 - 1);
        }
        if (sun % 11 == 0 || sun % 11 == 1){
            if (number[9] == 0){
                return true;
            }else {
                return false;
            }
        }else {
            if (number[9] == (11 - (sun % 11))){
                return true;
            }else {
                return false;
            }
        }
    }

    friend ostream &operator<<(ostream &os, Fone &fone)
    {
        os << fone.id << ": " << fone.number << "]" << endl;
        return os;
    }
};

class Contact{
private:
    string name;
    vector<Fone> fones;

protected:
    string prefix = "-";

private:
    bool foneRepetido(Fone fone){
        for (int i = 0; i < (int)this->fones.size(); i++){
            if ((this->fones[i].getId() == fone.getId()) && (this->fones[i].getNumber() == fone.getNumber())){
                return true;
            }
        }
        return false;
    }

public:
    Contact(string name = "") : name{name} {};

    void addFone(Fone fone){
        if (fone.validate != nullptr){ // vai verificar se é diferente de zero, ent vai pro outro if
            if (foneRepetido(fone)){ // aqui vai verifcar se o numero ja existe
                cout << "Numero de telefone ja existente" << endl;
                return; // vai imprimir isso
            }
            this->fones.push_back(fone); // dps de verificar se existe ou nao e continuar, ele vai pegar o fone e adicionar
            cout << "Fone adicionado" << '\n';
        }else {
            cout << "Numero de telefone invalido" << endl; // aq vai rodar caso seja 0 e o numero seja invalido
        }
    }

    void rmFone(int index){
        if (index < 0 || index >= (int)this->fones.size()){
            return;
        }
        this->fones.erase(fones.begin() + index);
        cout << "Fone apagado" << endl;
        return;
    }

    vector<Fone> getFones(){
        return this->fones;
    }

    string getName(){
        return this->name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Contact &cont){
        os << cont.prefix << " ";
        os << cont.name << " ";
        for (int i = 0; i < (int)cont.fones.size(); i++){
            auto fone = cont.fones[i];
            os << "[" << i << ":" << fone << endl;
        }
        return os;
    }
};

int main()
{
    Contact contato("Joao");
    contato.addFone(Fone("oi", "9183"));
    contato.addFone(Fone("casa", "328948"));
    cout << "\n";

    Contact contato2("Maria");
    contato2.addFone(Fone("claro", "9183"));
    cout << "\n";

    Contact contato3("Leo");
    contato3.addFone(Fone("casa", "9123"));
    contato3.rmFone(0);
    cout << "\n";

    cout << contato << endl;
    cout << contato2 << endl;
    cout << contato3 << endl;
}