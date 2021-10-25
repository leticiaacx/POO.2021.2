#include <iostream>
#include <algorithm>

using namespace std;

struct Person{
    string name;
    int age;

    Person(string nome = "", int idade = 0) :
        name{nome}, age{idade}{
    }

    friend ostream &operator<<(ostream &os, const Person &pessoa)
    {
        os << "Name: " << pessoa.name << ", ";
        os << "Age: " << pessoa.age << " years old\n";
    }
};

void nomedaCrianca(Person &kid)
{
    cout << kid.name << " is " << kid.age<< " years old" << endl;
}

struct Motorcycle
{
    Person* person;
    int power{1};
    int time {0};

    Motorcycle(int power, int time, Person* person = nullptr) :
        power{power}, time{time}, person{person}{
    }

    friend ostream &operator<<(ostream &os, const Motorcycle &moto)
    {
        os << "Power: " << moto.power << "\n";
        os << "Time: " << moto.time << "\n";
    }

    bool inPerson(Person *person)
    {
        if (this->person != nullptr)
        {
            cout << "There's a kid on the motorcycle" << endl;
            return false;
        }
        this->person = person;
        return true;
    }

    Person *outPerson()
    {
        if (this->person == nullptr)
        {
            cout << "There's no kid on the bike" << endl;
            return nullptr;
        }

        Person* person = this->person;
        this->person = nullptr;
        return person;
    }

    void buy(int tempo)
    {
        int buyTime;
        if (this->time == 0)
        {
            cout << "Time's up! Get more time!\n";
    
        }
        else
        {
            this->time += tempo;
            cout << "Time added successfully!\n";
        }
        
        cout << this->time << " minutes\n";
    }

    void drive(int tempo)
    {
         if(this->time > 0) {
             cout << "Time's not over yet, keep driving!\n";
        } else {
            cout << "The ride is over!\n";
        }
    }

    Person* honk()
    {
        if (this->power == 1)
        {
            cout << "Pem\n";
        }
        else
        {
            cout << "Peeeem\n";
        }
    }
};

int main()
{
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