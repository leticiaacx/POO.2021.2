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

int main()
{   
    
   PET dog("Zeca", "Dog");
   cout << dog << endl;
   dog.play();
   cout << "Zeca esta " << dog << endl;

}
