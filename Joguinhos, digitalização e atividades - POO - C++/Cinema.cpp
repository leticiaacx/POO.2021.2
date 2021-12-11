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

public:
    Sala(int capacidade) : cadeiras(capacidade, nullptr){
    } //Construtor

    bool reservar(shared_ptr<Client> client, int ind){ //nesse aqui vou verificar se a cadeira ta ou não ocupada
        if (this->cadeiras[ind] != nullptr || ind >= (int)this->cadeiras.size()){
            cout << "Cadeira ocupada" << endl; //aqui vai me retornar falso quando a cadeira estiver ocupada
            return false; 
        }

        this->cadeiras[ind] = client;
        cout << "Cadeira revervada" << endl; 
        return true; // vai me retornar true quando a cadeira estiver vazia e reversada por mim
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
                os << "*****";
            os << " // ";
        }
        return os;
    }
};

int main()
{   //testes
    Sala cinema(6);

    cinema.reservar(make_shared<Client>("287381","Davi"), 1);
    cinema.reservar(make_shared<Client>("381931" ,"Joao"), 2);
    cinema.reservar(make_shared<Client>("9328", "Maria"), 6);
    cout << "\n";

    cinema.cancelar("Joao");
    cout << "\n";

    cout << cinema << endl; 
    cout << "\n";
}