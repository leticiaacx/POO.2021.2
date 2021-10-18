#include <iostream>
#include <vector>

using namespace std;

//{1, 3, 4, 3, -1, -3, -3} -> {4}
vector<int> sozinhos(const vector<int>& vet)
{
    vector<int> novoV, rep;
    bool repetido;
    for(int i = 0; i < vet.size(); i++) {
        repetido = false;
        for (int j = 0; j < vet.size(); j++)
        { //verifica se existem iguais apenas entre os anteriores
            if (abs(vet[j]) == abs(vet[i]) && i != j){
                repetido = true;
                novoV.push_back(vet[i]);
                break; //tem repetido, não precisa continuar com a procura
            }
        }
         if (repetido == true) {
            repetido = false;
            continue;
        } else {
             rep.push_back(vet[i]);
         }
    }
    return rep;
}

//{1, 3, 4, 5, -1, -5, -5} -> 3
int maisO(vector<int> vet, int num)
{
    int ocorrencias;
    for(int x: vet){
        if (vet[x] == num || abs(vet[x])){
            ocorrencias++;
        }
    }
    return ocorrencias;
}
int Ocorrencias(vector<int> v)
{
    int contador;
    int nivel = -1;
    for (int x : v){
        contador = maisO(v, v[x]);
        if (contador > nivel){
            nivel = contador;
        }
    }
    return nivel;
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
    for (int i = 0; i < tam; ++i){
        cout << "Digite um numero ao vetor: " << endl;
        cin >> a; 
        vetor.push_back(a);
    }

    vector<int> so = sozinhos(vetor);
    cout << "Pessoas eram as unicas representantes do seu nivel de stress na fila: " << so << endl;

    int oco = Ocorrencias(vetor);
    cout << "A maior quantidade de ocorrencias do mesmo nivel de stress: "<< oco << endl;
}