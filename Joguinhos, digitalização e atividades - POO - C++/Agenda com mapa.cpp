#include <iostream>
#include <vector>
#include <memory>
#include <map>

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
    
    static bool validate(string number){ //validade de numero
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

    friend ostream &operator<<(ostream &os, Fone &fone){
        os << fone.id << ": " << fone.number << "]" << endl;
        return os;
    }
};

class Contact{
public:
    string name;
    vector<Fone> fones;
protected:
    string prefix = "-";

private:
    bool foneRepetido(Fone fone){ // aqui ele verifica se há números repetidos
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
            if (foneRepetido(fone) == 1){ // aqui vai verifcar se o numero ja existe
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

class Agenda{
private:
    map<string, Contact> contatos;
    
public:
    Agenda(){};

    Contact getContact(string name){
        return this->contatos[name];
    }

    void addContact(Contact contato){
        auto it = contatos.find(contato.name);
        if(it == contatos.end()){
            contatos[contato.name] = contato;
        } else{
            it ->second.addFone(contato.fones[0]);
        }
    }

    void rmContact(string name){
        auto it = contatos.find(name);

        if (it != contatos.end()) {
            contatos.erase(it);
        } else {
            cout << "Contato " << name << " nao existe" << endl;
        }
    }

    void rmContact(string name, int index){
        auto it = contatos.find(name);

        if (it != contatos.end())
        {
            it->second.rmFone(index);
        } else {
            cout << "Contato selecionado nao existe na agenda" << endl;
        }
    }

    void search(string s){
        for (auto cont : contatos){
            size_t found = cont.second.getName().find(s);
            if (found != string::npos){
                cout << cont.second << endl;
            }
        }
        cout << '\n';
    }

    friend ostream &operator<<(ostream &os, Agenda &a){
        os << '\n';

        for (auto cont : a.contatos){
            os << cont.second << '\n';
        }
        return os;
    }
};

int main()
{
    cout << "---AGENDA INICIALIZADA---" << endl;
    Agenda agenda;

    cout << "Adicionando contatos...." << endl;
    Contact Joao{"Joao"};
    Contact Lara{"Lara"};
    Contact Ana{"Ana"};

    Joao.addFone(Fone{"oi", "888"});
    Lara.addFone(Fone{"tim", "788"});
    Lara.addFone(Fone{"claro", "138"});
    Ana.addFone(Fone{"vivo", "246"});

    cout << "Lista de contatos...." << endl;
    agenda.addContact(Joao);
    agenda.addContact(Lara);
    agenda.addContact(Ana);

    cout << agenda << endl;

    cout << "Removendo contatos...." << endl;
    agenda.rmContact("Ana");
    agenda.rmContact("Lara", 1);

    cout << "Procurando contatos...." << endl;
    agenda.search("88");
    cout << agenda << endl;
}