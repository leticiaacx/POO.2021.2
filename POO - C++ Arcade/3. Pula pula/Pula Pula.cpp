#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>
#include<list>

using namespace std;

class Kid{
public:
    int age;
    string name;

    Kid(string name = "", int age = 0) : name{name}, age{age}{
    }

    int getAge(){
        return this->age;
    }

    string getName(){
        return this->name;
    }

    void setAge(int age){
        this->age;
    }

    void setName(string name){
        this->name;
    }

    friend ostream &operator<<(ostream &os, const Kid &kid){
        os << "Nome: " << kid.name;
        os << "Idade: " << kid.age << " anos";
        return os;
    }
};

class Trampoline{
public:
    vector<shared_ptr<Kid>> waiting;
    list<shared_ptr<Kid>>   playing;

public:
    Trampoline(int qtdBrinquedos) : playing(qtdBrinquedos, nullptr){
    }

    void arrive(const shared_ptr<Kid>& kid){//fila de espera
        cout << "Na fila de espera aguardando a vez!" << endl;
        this->waiting.push_back(kid);
    }

    bool in(int espaco)//entrando
    {
        if (espaco < 0 || espaco >= this->playing.size())
        {
            cout << "Trampolim invalido" << endl;
            return false;
        }
        auto iterator = *next(this->playing.begin(), espaco);
        if (iterator != nullptr)
        {
            cout << "Trampolim ocupado" << endl;
            return false;
        }
        if (this->waiting.empty())
        {
            cout << "fila de espera vazia" << endl;
            return false;
        }
        cout << "a pessoa " << this->waiting.front()->name << " entrou no pula pula" << endl;
        iterator = this->waiting.front();
        this->waiting.erase(waiting.begin());
        return true;
    }

    void out(){// fechado
        if (this->playing.size() == 0){
            cout << "Trampolim fechado" << endl;
            return;
        }

        this->waiting.push_back(this->playing.front());
        this->playing.erase(this->playing.begin());
    }

    bool remove(int out) //saindo
    {
        if (out < 0 || out >= this->playing.size())
        {
            cout << "Trampolim indiposnivel" << endl;
            return false;
        }

        auto iterator = *next(this->playing.begin(), out);
        if (iterator == nullptr)
        {
            cout << "Trampolim vazio" << endl;
            return false;
        }

        cout << "a pessoa " << iterator->getName() << " saiu do trampolim" << endl;
        this->waiting.push_back(iterator);// voltou pra fila 
        iterator = nullptr;
        return true;
    }

    friend ostream &operator<<(ostream &os, const Trampoline &b){
        os << "Trampolim: ";
        for (auto playing : b.playing){
            os << playing << " ";
        }
        os << " Espera: ";
        for (auto playing : b.waiting){
            /* code */
        }
    }
};

int main()
{
    Trampoline trampoline(3);
    trampoline.arrive(make_shared<Kid>("Joao", 12));
    trampoline.arrive(make_shared<Kid>("Pedro", 6));
    trampoline.arrive(make_shared<Kid>("Maria", 11));
  
    trampoline.in(1);
    trampoline.in(0);
    trampoline.in(1);

    trampoline.out();
    trampoline.out();

    trampoline.remove(0);
    trampoline.remove(0);

    cout << trampoline << endl;
}
