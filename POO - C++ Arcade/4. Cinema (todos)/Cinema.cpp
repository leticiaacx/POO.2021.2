#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>

using namespace std;

class Client{
private:
    string fone;
    string id;

public:
    Client(string fone = "", string id = "") :
    fone{fone}, id{id}{
    }

    string getFone(){
        return this->fone;
    }

    string getId(){
        return this->id;
    }

    friend std::ostream &operator<<(std::ostream &os, Client cliente){
        os << "Telefone:" << cliente.fone << " Id:" << cliente.id << '\n';
        return os;
    }
};

class Sala{
private:
    vector<shared_ptr<Client>> cadeiras;
    int capacidade;

public:
    Sala(int capacidade = 0) : cadeiras(capacidade, nullptr){
        this->capacidade = capacidade;
    } //Construtor

    void addClient(const shared_ptr<Client> client){
        cout << "cadeiras livres: " << endl;
        for (int i = 0; i < this->capacidade; i++){
            if (cadeiras[i] == nullptr)
                cout << "[ " << i << " ]" << " " << endl;
        }
    }

    void reservar(shared_ptr<Client> client, int ind){ //nesse aqui vou verificar se a cadeira ta ou não ocupada
        if (ind < 0 || ind >= this->capacidade){
            cout << "cadeira nao existente" << endl;
            addClient(client);
        }
        if (cadeiras[ind] != nullptr){// aqui ele vai imprimir dizendo que a cadeira esta ocupada
            cout << "cadeira ocupada" << endl;
            addClient(client);
        }

        cout << "cadeira reservada" << endl;// se nao entrar nos ifs, ele reservou a cadeira
        cadeiras[ind] = client;
    }

    void cancelar(string id){ // pra cancelar a reversa
        for (int i = 0; i < (int)this->cadeiras.size(); ++i){
            if (this->cadeiras[i] != nullptr && this->cadeiras[i]->getId() == id){
                this->cadeiras[i] = nullptr; // cadeira na posição i for igual a nuulptr é pq a reserva foi cancelada
                cout << "Reserva cancelada" << endl;
                break;
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Sala &s){
        for (int i = 0; i < (int)s.cadeiras.size(); i++){
            auto &cadeira = s.cadeiras[i];
            os << i << ":";
            if (cadeira != nullptr)
                os << cadeira;
            else
                os << "-----";
            os << " // ";
        }
        return os;
    }
};

int main()
{   //testes
    system("cls");
    Sala cinema(3);

    cinema.reservar(make_shared<Client>(5, 14589), 3);
    cinema.reservar(make_shared<Client>(6, 123459), 8);
    cinema.reservar(make_shared<Client>(7, 16789), 6);

    cinema.cancelar("3");

    cout << cinema << endl;
    return 0;   
}