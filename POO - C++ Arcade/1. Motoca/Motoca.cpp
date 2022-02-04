#include <iostream>
#include <algorithm>

using namespace std;

class Person{
public:
    string name;
    int age;

    Person(string nome = "", int idade = 0) :
        name{nome}, age{idade}{
    }

    int getAge(){
        return this->age;
    }

    string &getName(){
        return this->name;
    }

    friend ostream &operator<<(ostream &os, const Person &pessoa)
    {
        os << "Name: " << pessoa.name << ", ";
        os << "Age: " << pessoa.age << " years old\n";
    }
};

class Motorcycle{
public:
    Person* person;
    int power{1};
    int time{0};

    Motorcycle(int power, int time, Person* person = nullptr) :
        power{power}, time{time}, person{person}{
    }

    Motorcycle(int power): power(power){} // motoca iniciada 

    bool inPerson(Person *person){// subir
        if (this->person != nullptr){
            cout << "There's a kid on the motorcycle" << endl; // tem uma criança na moto
            return false;
        } else {
            this->person = person;
            cout << "A child got on the bike" << endl; // uma criança subiu
            return true;
        }
    }

    Person *outPerson(){// descer
        if (this->person == nullptr){
            cout << "There's no kid on the bike" << endl;// ngm na moto pra descer
            return nullptr;
        }

        cout << "A child got off on the bike" << endl; // desceu da moto
        return exchange(this->person, nullptr);// nao perder o objto 
    }

    void buy(int tempo){//comprando tempo
        int buyTime;
        if (this->time == 0){
            cout << "Time's up! Get more time!\n";
    
        } else {
            this->time += tempo;
            cout << "Time added successfully!\n";
        }
        
        cout << this->time << " minutes\n";
    }

    void drive(int tempo){// dirigindo
        if (this->person != nullptr && this->person->age < 10){
           cout << "kid playing" << endl;
        } else if (this->time == 0){
            cout << "Time is up" << endl;
        } else if (this->time >= tempo){
            this->time -= tempo;
        } else {
            cout << "Time finalized" << endl;
        }
    }

    Person *honk(){// buzinando
        if (this->person != nullptr){
            cout << "pemmm" << endl;
        } else{
            cout << "The motorcycle is empty" << endl;
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const Motorcycle &motor){
        os << "Power: " << motor.power << ", ";
        os << "time: " << motor.time << ", ";;
        if (motor.person != nullptr)
            os << "Pessoa: "
               << "[" << motor.person->name << ":" << motor.person->age << "]"
               << "\n";
        else
        {
            os << "Person: null\n";
        }
        return os;
    }
};

int main(){

    Person person("Ana", 7);
    
    Motorcycle motorcycle(3, 5, &person);
    motorcycle.person->name = "Ana";
    motorcycle.person->age -= 1;

    
    motorcycle.inPerson(&person);
    motorcycle.drive(7);
    motorcycle.buy(7);
    motorcycle.honk();
    motorcycle.outPerson();
}