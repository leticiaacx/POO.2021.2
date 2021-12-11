#include<iostream>
#include <vector>

using namespace std;

class CPF{
private:
    string number;

    // apenas uma função que realiza uma logica
    static vector<int> filter(string cpf)
    {
        vector<int> number; // transformando a string em vetor
        for (char i : cpf)
        {
            if (i != '.')
            {
                number.push_back(i - '0');
            }
        }
        return number;
    }

public:
    CPF(string number){
        this->number = number;
    }

    void setCPF(string number){
        this->number = number;
    }

    string getCPF(){
        return this->number;
    }

    bool isValid(){
        return CPF::validate(CPF::filter(this->number));
    }

    static bool validate(vector<int> v){
        int sun = 0;
        for (int i = 0; i < 9; i++){
            sun += v[i] * (10 - 1);
        }
        if (sun % 11 == 0 || sun % 11 == 1){
            if (v[9] == 0){
                return true;
            }else {
                return false;
            }
        }
        else {
            if (v[9] == (11 - (sun % 11))){
                return true;
            }else {
                return false;
            }
        }
    }

    static bool valiDate(string cpf){
        return CPF::validate(CPF::filter(cpf));
    }

    /*bool isValid() {
        vector<int> vet;
        for(int i = 0; i < number.size(); i++){
            vet.push_back(number[i] - '0');
        }
        if(vet.size() != 11){
            return false;
        }
        return validateCPF(vet);
    }*/
};


int main()
{
    vector<int> vet = {0, 8, 1, 0, 4, 3, 6, 2, 3, 0, 5};// pensando enquanto função
    cout << CPF::validate(vet) << endl; 

    CPF meucpf("081.043.623.05");// pensando enquanto orientação a objetos
    cout << meucpf.isValid() << endl;
} 