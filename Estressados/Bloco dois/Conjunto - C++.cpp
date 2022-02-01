#include <iostream>
#include <vector>

using namespace std;

//{1, 3, 4, 3, -1, -2, -2} -> {1, 3, 4, -1, -3}
vector<int> exclusivos(const vector<int>& v)
{
    vector<int> repetido; 
    bool flag; //se eu encontro ou não um numero igual, num indice antes ou depois de i
    for(int i = 0; i < v.size(); i++){
        flag = false;//ate o momento eu nao encontro o elemento q esta repetido a esquerda ou direita
        for(int j = 0; j < i; j++){
            if(v[i] == v[j]){
                flag = true;//encontrei igual
                break;
            }
        }
        if(flag == false){
            repetido.push_back(v[i]);
        }
    } 
    return repetido;
}

//{1, 3, 4, 3, -1, -2, -2} -> {1, 3, 4}
vector<int> diferentes(const vector<int>& v)
{
    vector<int> rep {};
    bool flag = false;
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < rep.size(); j++){
            if (v[i] == rep[j] || v[i] * -1 == rep[j]){
                flag = true;
                break;
            }
        }
        if (flag == true){
            flag = false;
            continue;
        } else {
            if (v[i] < 0){
                rep.push_back(v[i] * -1);
            }else{
                rep.push_back(v[i]);
            }
        }
    }
    return rep;
}

//{1, 3, 4, 3, -1, -2, -2} -> {3, -2}
vector<int> abandonados(const vector<int>& v)
{
    vector<int> v2{};
    vector<int> v3{};
    bool flag =  false;
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v2.size(); j++){
            if (v[i] == v2[j]){
                flag = true;
                v3.push_back(v[i]);
                break;
            }
        }
        if (flag == true){
            flag = false;
            continue;
        } else {
            v2.push_back(v[i]);
        }
    }
    return v3;
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

    vector<int> repetido = exclusivos(vetor);
    cout << "Lista dos valores que aparecem na fila sem repeticao: " << repetido << endl;

    vector<int> dif = diferentes(vetor);
    cout << "A lista dos diferentes niveis de stress que aparecem: " << dif << endl;

    vector<int> ab = abandonados(vetor);
    cout << "Pessoas ficaram na fila apos remover um exemplar de cada valor: " << ab << endl;
}