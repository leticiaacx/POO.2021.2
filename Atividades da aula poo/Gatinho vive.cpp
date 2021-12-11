#include <iostream>

using namespace std;

class Animal{
    bool isAlive {true}; // já defini o parametro default aqui
    string type;

public:
    Animal (string type = "Bacteria"): type(type) {
        cout << this->type << " animal created successfully" << endl;
    }

    ~Animal (){
        cout << this->type << " animal destroyed successfully" << endl;
    }

    bool islive () const {
        return isAlive;
    }

    void die (){
        isAlive = false;
    }

    string getType() const{
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

    ~PET(){
        cout << this->name << " destroyed" << endl;
    }

    void play() const{
        cout << this->name << " playing"<< endl;
    }

    string getName() const{
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
    ~Cat(){
    }
    void meow() const{
        cout << this->getName() << " meowing" << endl;
    }
    void die() const{
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
    cout << cat << endl;
}
