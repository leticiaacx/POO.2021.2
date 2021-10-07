#include <iostream>
#include <vector>
#include<ctime>

using namespace std;

//retorna um novo vetor com os dados invertidos
vector<int> inverterCopia(const vector<int>& v)
{   
    vector<int> novoV;
    for (int i = v.size() - 1; i >= 0; i--){
        novoV.push_back(v[i]);
    }
	return novoV;
}

//inverte os valores do vetor de entrada sem uso de vetor auxiliar
void reverterInplace(vector<int>& vet)
{
    int aux;
    int tam = vet.size();
    for (int i = 0; i < tam / 2; i++){
        aux = vet[i];
        vet[i] = vet[(tam - 1) - i];
        vet[(tam - 1) - i] = aux;
    }
    return;
}

//retorna aleatoriamente um elemento do vetor
int sortear(const vector<int>& vet)
{
    int tamanho = vet.size();
    int sorte = rand() % tamanho;
    
    int num = vet[sorte];
    
    return num;
}

//embaralha o vetor original
void embaralhar(vector<int>& vet)
{
    for (int i = 0; i < vet.size(); i++){
        int r = rand() % vet.size();

        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}

//ordena o vetor original
void ordenar(vector<int>& v)
{
    for(int i = 0; i  < v.size(); i++){
        for(int x = i; x < v.size(); x++){
            if(v[i] > v[x]){
                int aux = v[i];
                v[i] = v[x];
                v[x] = aux;
            }
        }
    }
}

template <typename T>
ostream &operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

int main()
{
    int tam = 0;
    cout << "Digite o tamanho do vetor: " << endl;
    cin >> tam;

    vector<int> vetor{};
    int a;
    for (int i = 0; i < tam; ++i){
        cout << "Digite um numero ao vetor: " << endl;
        cin >> a; 
        vetor.push_back(a);
    }

    vector<int> invertido = inverterCopia (vetor);
    cout << "Um novo vetor com os dados invertidos " << invertido << endl;

    reverterInplace(vetor);
    cout << "Invertendo os valores do vetor sem uso de vetor auxiliar: " << vetor << endl;

    srand(time(0));
    int sorteado = sortear(vetor);
    cout << "Numero aleatoriamente sorteado do vetor: "<< sorteado << endl;

    embaralhar(vetor);
    cout << "Embaralharmento do vetor original: " << vetor << endl;

    ordenar(vetor);
    cout << "Ordenacao do vetor original: " << vetor << endl;
}
