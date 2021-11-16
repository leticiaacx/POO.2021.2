#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>
#include<list>

class Client{
private:
   string id;
   string fone;

public:
    Client(string id, string fone) : id{id}, fone{fone}{
    }

    string id(){
        return this-> id;
    }
    
    void setId(string id){
        this->id;
    }

    string getFone(){
        return this-> fone;
    }

    void setFone(string fone){
        this-> fone;
    }
};