#include <cstdlib>
#include <iostream>

using namespace std; // com isso aqui no começo, basta botar "cout << ..."

bool existe(int vetor[], int tam, int X) // Primeira função
{
    for (int i = 0; i < tam; ++i){
        if (vetor[i] == X){
            return true; // true = 1
        }
    }
    return false; // false = 0
}

int contar(int vetor[], int tam, int X)
{
    int contador = 0;

    for (int i = 0; i < tam; ++i){
        if (vetor[i] == X){
            contador++; //vai contar toda vida que o vetor for igual a X
        }
    }
    return contador;
}

int procurarValor(int vetor[], int tam, int X)
{
    for (int i = 0; i < tam; ++i){
        if (vetor[i] == X){
            return i; // vai retornar quando x estiver na posição i
        }
    }
    return -1; // vai retornar -1 quando ele nao estiver na fila
}

int proValorApartir(int vetor[], int tam, int X, int pos)
{
    for(int i = pos + 1; i < tam; ++i){
        if (vetor[i] == X){
            return i; 
        }
    }
    return -1;
}

int main()
{
    int tam = 0;
    cout << "Digite o tamanho do vetor: "<< endl;
    cin >> tam;

    int vetor[tam];
    int x, cont, procV, procVP;

    for (int i = 0; i < tam; ++i){
        cout << "Digite um numero ao vetor: "<< endl;
        cin >> vetor[i];
    }

    cout << "Agora digite um numero para ser verificado: "<< endl;
    cin >> x;

    bool ext = existe(vetor, tam, x);
    cout << "Existe: " << ext << endl;

    cont =  contar(vetor, tam, x);
    cout << "Quantidade de vezes que aparece: " << cont << endl;

    procV = procurarValor(vetor, tam, x);
    cout << "Aparece X pela primeira vez em: " << procV << endl;

    int pos;
    cout << "Digite posicao para iniciar a busca: "<< endl;
    cin >> pos;

    procVP = proValorApartir(vetor, tam, x, pos);
    cout << "Qual a proxima posicao em que aparece X: " << procVP << endl;
}