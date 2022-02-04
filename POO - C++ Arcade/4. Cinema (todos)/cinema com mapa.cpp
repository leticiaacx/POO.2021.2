#include <iostream>
#include <memory>
#include <map>

using namespace std;

class Client
{
private:
    string fone;
    string id;

public:
    Client(string fone = "", string id = "") : fone{fone}, id{id}{}

    string getFone() const{
        return this->fone;
    }

    string getId() const{
        return this->id;
    }

    friend std::ostream &operator<<(std::ostream &os, Client cliente){
        os << "Telefone:" << cliente.fone << " Id:" << cliente.id << '\n';
        return os;
    }
};

class Sala{
private:
    map<int, shared_ptr<Client>> cadeiras;
    const int qtdCadeiras;
    int assistindo;

public:
    Sala(int qtdCadeiras) : qtdCadeiras{qtdCadeiras}, assistindo{0}{
    } // Construtor

    void reservar(string name, string fone, int indice){ // nesse aqui vou verificar se a cadeira ta ou não ocupada
        if (qtdCadeiras == assistindo){
            cout << "Cadeira ocupada" << endl; // aqui vai me retornar quando a cadeira estiver ocupada
            return;
        }

        if (indice < 0 || indice >= qtdCadeiras){
            cout << "Id invalido" << endl; // aqui vai me retornar quando ele considerar o id invalido
            return;
        }

        if (cadeiras[indice] != nullptr){
            cout << "Cadeira revervada" << endl;
            return; // vai me retornar quando a cadeira estiver reversada
        }

        auto cliente = make_shared<Client>(name, fone);
        cadeiras[indice] = cliente;
        // client
        this->assistindo++;
    }

    void cancelar(string id){ // pra cancelar a reversa
        for (auto& [indice, client] : cadeiras){
            if (client->getId() == id){
                cadeiras.erase(indice); // cadeira na posição i for igual a nuulptr é pq a reserva foi cancelada
                cout << "Reserva cancelada" << endl;
                cout << id << " foi embora da sala de cinema" << endl;
                break;
            }
        }
    }

    friend ostream &operator<<(ostream &os, const Sala &s){
        for (int i = 0; i < s.qtdCadeiras; i++)
        {
            auto cadeira = s.cadeiras.find(i);
            os << i << ":";
            if (cadeira != s.cadeiras.end())
                os << "[ " << cadeira->first << " - " << cadeira->second->getId() << " ]" << endl;
            else
                os << "*****";
            os << " // ";
        }
        return os;
    }
};

int main()
{ // testes
    Sala cinema(6);

    cinema.reservar("Joao", "382", 2);
    cinema.reservar("Maria", "32809", 1);
    cout << "\n";

    cinema.cancelar("Joao");
    cout << "\n";

    cout << cinema << endl;
    cout << "\n";
}