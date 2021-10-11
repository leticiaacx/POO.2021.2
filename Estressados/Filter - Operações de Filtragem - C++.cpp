#include <iostream>
#include <vector>

using namespace std;

vector<int> clone(const vector<int>& vet)
{
    vector<int> novoVetor;
    for(int i = 0; i < vet.size(); i++){
        novoVetor.push_back(vet[i]);
    }
    return novoVetor;
}

vector<int> pegarHomens(const vector<int>& vet)
{
    vector<int> pegueiHomem{};
    for (int i = 0; i <vet.size(); i++){
        if(vet[i] > 0){
            pegueiHomem.push_back(vet[i]);
        }
    }
    return pegueiHomem;
}

vector<int> pegarCalmos(const vector<int>& vet)
{
    vector<int> calmos{};
    for(int i = 0; i < vet.size(); i++){
        if(vet[i] > 0 && vet[i] < 10){
            calmos.push_back(vet[i]);
        }
    }
    return calmos;
}

vector<int> pegarMCalmas(const vector<int>& vet)
{
    vector<int> calmas{};
    for(int i = 0; i < vet.size(); i++){
        if(vet[i] < 0 && vet[i] > -10){
            calmas.push_back(vet[i]);
        }
    }
    return calmas;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
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
    for (int i = 0; i < tam; ++i)
    {
        cout << "Digite um numero ao vetor: " << endl;
        cin >> a; 
        vetor.push_back(a);
    }

    vector<int> recebido = clone(vetor);
    cout << "Clone: " << recebido << endl;

    vector<int> pegarH = pegarHomens(vetor);
    cout << "Lista com os homens (valores positivos): " << pegarH << endl;

    vector<int> calmos = pegarCalmos(vetor);
    cout << "Lista com as pessoas com stress menor que 10 (positivos menor que 10): " << calmos << endl;

    vector<int> calmas = pegarMCalmas(vetor);
    cout << "Lista com as mulheres com nivel de stress menor que 10 (negativos menor que 10): " << calmas << endl;
}