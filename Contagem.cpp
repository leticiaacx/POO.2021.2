#include <iostream>
#include <vector>

using namespace std;

float stressMedio(vector<int> vec, int tam)
{
    float soma = 0;
    for(int i : vec){
        soma++;
    }

    return (tam > 0) ? (soma / tam) : 0; // para definir uma condição e escolher por um dentre dois valores.
}

char mHomemOuMulher(vector<int> vec, int tam)
{
    int homem = 0;
    int Mulher = 0;
    for(int i : vec){
        (i > 0) ? homem++ : Mulher++; //novamente para definir uma condição e escolher por um dentre dois valores.
    }

    if(tam > 0){
        return (homem > Mulher) ? 'H' : 'M';
    } else{
        return '-';
    }

}

int maisEstressados(vector<int> vec, int tam)
{

}

int main()
{   
    int tam = 0;
    cout << "Digite o tamanho do vetor: " << endl;
    cin >> tam;


    vector <int> vetor{};
    int a;
    float media;

    for (int i = 0; i < tam; ++i){
        cout << "Digite um numero ao vetor: " << endl;
        cin >> a;
        vetor.push_back(a);
    }

    media = stressMedio(vetor, tam);
    cout << "A media de stress da fila: "<< media << endl;
    
    char HouM = mHomemOuMulher(vetor, tam);
    cout << "Na fila existem mais homens ou mulheres: "<< HouM << endl;
}