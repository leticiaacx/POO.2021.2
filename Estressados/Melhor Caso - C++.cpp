#include <iostream>
#include <vector>

using namespace std;

int procMenor(vector<int> vec)
{
    int menor = 100;
    for (int i = 0; i < vec.size(); ++i){
        if(vec[i] < menor){ //aqui ele vai percorrer o vetor e verificar se o vetor na posição i é menor q o vetor
            menor = vec[i]; // na posição i, caso for, ele vai retornar vetor na posição i
        }
    }
    return menor;
}

int procMenorPos(vector<int> vec)
{
    int menor = 100;
    int posMenor = -1;
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] < menor){ //aqui ele vai percorrer o vetor e verificar se o vetor na posição i é menor q o vetor
            menor = vec[i];
            posMenor = i; // na posição i, caso for, ele vai retornar vetor na posição i
        }
    }
    return posMenor;
}

int procMenorPosApartir(vector<int> vec, int inicio)
{
    int menor = 100;
    int  posMenor = -1;
    for(int i = inicio + 1; i < vec.size(); ++i){
        if (vec[i] < menor){
            menor = vec[i];
            posMenor = i;
        }
    }
    return posMenor;
}

int procurarMelhorSe(vector<int> vec)
{
    int menor = 100;
    int posMenor = -1;
    for(int i = 0; i < vec.size(); ++i){
        if (vec[i] > 0 && vec[i] < menor){
            menor = vec[i];
            posMenor = i;
        }
    }
    return posMenor;
}
int main()
{
    int tam = 0;
    cout << "Digite o tamanho do vetor: " << endl;
    cin >> tam;


    vector <int> vetor{};

    int a;
    for (int i = 0; i < tam; ++i){
        cout << "Digite um numero ao vetor: " << endl;
        cin >> a;
        vetor.push_back(a);
    }

    int menor = procMenor(vetor);
    cout << "O menor numero da fila: " << menor << endl;
     
    int menorPos = procMenorPos(vetor);
    cout << "Posicao do menor valor da lista: " << menorPos << endl;
    
    int inicial;
    cout << "Digite posicao para iniciar a busca: " << endl;
    cin >> inicial;

    int procMPA = procMenorPosApartir(vetor, inicial);
    cout << "Qual a proxima posicao em que aparece X: " << procMPA << endl;

    int melhorSe = procurarMelhorSe(vetor);
    cout << "Posicao do HOMEM mais calmo: " << melhorSe << endl;

}
