#include <iostream>

using namespace std;

class Animal{
    bool isAlive {true}; // já defini o parametro default aqui
    string type;

public:
    Animal (string type = "Bacteria"): type(type) {
        cout << this->type << " animal created successfully" << endl;
    }

   virtual ~Animal (){
        cout << this->type << " animal destroyed successfully" << endl;
    }

    virtual bool islive () const {
        return isAlive;
    }   

    //esse virtual serve pra caso exista essa mesma função la na frente, so que mais evoluida, substituir 
    virtual void die (){ // se eu chamar ele na main, ele vai verificar se existe outro die em outro lugar e rodar aquele
        isAlive = false;
    }

    virtual string getType() const{
        return type;
    }
    
   friend ostream& operator<<(ostream& os, const Animal& animal){
        os<< animal.type << ": " << (animal.isAlive ? "alive" : "dead" ) << endl;
        return os;
   }
};

class PET : public Animal{ // nesse escopo, o pet é um animal
    string name;
    
public:
    PET (string name, string type): Animal(type), name(name) {
        cout << this->name << " pet created successfully" << endl;
    }

    virtual ~PET(){
        cout << this->name << " destroyed" << endl;
    }

    virtual void play() const{
        if(this->islive()){
        cout << this->name << " playing"<< endl;
        } else {
            cout << this->name << " is dead" << endl;
        }
    }

    virtual string getName() const{
        return name;
    }

    friend ostream& operator<<(ostream& os, const PET& pet){
        os<< pet.name << ":" << pet.getType() << ":" << (pet.islive() ? "alive" : "dead");
    }
};

class Cat : public PET{
    int lives {9};

public:
    Cat (string name, int lives = 9): PET(name, "cat"), lives (lives){
    }
    virtual ~Cat(){
    }

    virtual void meow() const{
        cout << this->getName() << " meowing" << endl;
    }

    virtual void play() const{
        cout << this->getName() << " playing" << endl;
    }

    virtual void die() const{
        if(this->lives() == 0){
            cout << this->getName() << " died" << endl;
        } else if(this->lives > 1);{
            this->lives--;
            cout<< " still alive!! Try again later" << endl;
        } else {
            cout << "RIP" << endl;
            this->PET:: die();
        }
    }

    friend ostream& operator<<(ostream& os, const Cat& cat){
        os << cat.getName() << ": " << cat.getType() << ": " << (cat.islive() ? "alive" : "dead");
        return os;
   }
};

int main()
{   
    Cat cat("Cat", 9);
    cout << cat << endl;
    cat.play();
    cat.meow();
    cout << cat << endl;
}
