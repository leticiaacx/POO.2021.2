#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>
#include<list>

using namespace std;

class Kid{
private:
    int age;
    string name;

public:
    Kid(string name, int age){
        this->name;
        this->age;
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
private:
    vector<shared_ptr<Kid>> waiting;
    list<shared_ptr<Kid>>   playing;

public:
    bool cheio(int cheio){
        return cheio >= 0 && cheio < playing.size();
    }

    Trampoline(int qtdBrinquedos) : playing(qtdBrinquedos, nullptr){
    }

    void arrive(const shared_ptr<Kid>& kid){
        this->waiting.push_back(kid);
    }

    void in(){
        if (this->waiting.size() == 0){
            return;
        }
        this->playing.push_back(this->waiting.front());
        this->waiting.begin();
    }

    void out(){
        if (this->playing.size() == 0){
            cout << "Trampolim fechado" << endl;
            return;
        }
        this->waiting.push_back(this->playing.front());
        this->playing.erase(this->playing.begin());
    }

    bool remove(int out)
    {
        if (out < 0 || out >= this->playing.size())
        {
            cout << "Trampolim indiposnivel" << endl;
            return false;
        }

        auto iterator = *next(this->playing.begin(), out);
        if (iterator = nullptr)
        {
            cout << "Trampolim vazio" << endl;
            return false;
        }

        cout << "a pessoa " << iterator->getName() << " saiu do trampolim" << endl;
        this->waiting.push_back(iterator);
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
    trampoline.arrive(make_shared<Kid>("Ana", 8));
    trampoline.arrive(make_shared<Kid>("Rafa", 7));
    trampoline.arrive(make_shared<Kid>("Leo", 7));

    trampoline.in();
    trampoline.in();
    trampoline.in();
    trampoline.in();
    trampoline.in();
    trampoline.in();
    trampoline.in();

    trampoline.out();
    trampoline.out();

    trampoline.remove(0);
    trampoline.remove(3);


    cout << trampoline << endl;
}
