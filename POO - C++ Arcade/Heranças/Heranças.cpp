#include <iostream>

using namespace std;

class vehicle{
private:
    string name;
    string color;

public:
    int speed;
    int wheel;

    vehicle(string name, string color, int speed, int wheel): name(name), color(color), speed(speed), wheel(wheel){
        cout << this->name << " created and is " << this->color << endl;
    }

    virtual ~vehicle(){
        cout << this->name << " destroyed" << endl;
    }

    virtual void setName(string name){
        this->name = name;
    }

    virtual string getName(){
        return name;
    }

    virtual void setColor(string color){
        this->color = color;
    }

    virtual string getColor(){
        return color;
    }

    virtual void setSpeed(int speed){
        this->speed = speed;
    }

    virtual int getSpeed(){
        return speed;
    }

    virtual void setWheel(int wheel){
        this->wheel = wheel;
    }

    virtual int getWheel() {
        return wheel;
    }

    friend ostream& operator<<(ostream& os, vehicle& v){
        os << v.name << " : "<< v.color << " : " << v.speed << " : " << v.wheel << " : " << endl;
        return os;
    }
};

class car : public vehicle{
    string plate;
    string brand;

public:
    bool numDoors{true};

    car(string plate, string brand, bool numDoors, string name, string color, int speed, int wheel): vehicle(name, color, speed, wheel){

    }

    virtual ~car(){
        cout << this->plate << " destroyed" << endl;
    }

    virtual bool getnumDoors() const{
        return numDoors;
    }
    virtual string getplate() const{
        return plate;
    }

    virtual string getBrand() const{
        return brand;
    }

    friend ostream& operator<<(ostream& os, const car& v){
        os << v.getplate() << " : " << v.getBrand() << " : " << (v.numDoors ? "two" : "for");
        return os;
    }
};

class motorcycle : public vehicle{
    int plates;
    string brands;

public:
    motorcycle(int plates, string brands, string name, string color, int speed, int wheel): vehicle(name, color, speed, wheel){

    }

    virtual ~motorcycle(){
        cout << this->plates << " destroyed" << endl;
    }

    virtual int getplate() const{
        return plates;
    }

    virtual string getBrand() const{
        return brands;
    }

    friend ostream &operator<<(ostream &os, const motorcycle& m){
        os << m.getplate() << " : " << m.getBrand() << endl;
        return os;
    }
};

int main()
{
    car car("p342", "palio", 4, "Fiat", "preto", 120, 4);
    cout << car << endl;

    motorcycle moto(233234, "x360", "Honda", "azul", 180, 2);
    cout << moto << endl;

}