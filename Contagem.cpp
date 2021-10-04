#include <iostream>
#include <vector>

using namespace std;

float stressMedio(vector<int> vec, int tam)
{
    float soma = 0, media = 0;
    for(int i = 0; i < vec.size(); ++i){
        if(vec[i] < 0){
            vec[i] *= -1; // o abs pega o modulo dos numeros
        } 
        soma = vec[i] + soma;
    }
    media = soma/tam;
    return media;
}

char mHomemOuMulher(vector<int> vec)
{
    int Homem = 0, Mulher = 0, Empate = 0;
    for(int i = 0; i < vec.size(); ++i){
        if(vec[i] > 0){
            Homem++;
        } else if(vec[i] < 0){
            Mulher++;
        } 
    }
    if (Homem > Mulher && Mulher < Homem){
        return 'H';
    }else if (Homem < Mulher && Mulher > Homem){
        return 'M';
    }else if (Homem == Mulher){
        return 'E';
    }
}

float maisEstressados(vector<int> vec, int size)
{
    float metade = vec.size()/2;
    float somaP = 0, somaS= 0;
    for(int i = 0; i < metade; ++i){
           if(vec[i] < 0){
               vec[i] *= -1;
           }
         somaP = vec[i] + somaP;
    }

    for (int x = metade; x < vec.size(); ++x){
        if (vec[x] < 0){
            vec[x] *= -1;
        }
        somaS = vec[x] + somaS;
    }

    if (somaP > somaS && somaS< somaP){
        return 1;
    }else if (somaP< somaS && somaS > somaP){
        return 2;
    }else if (somaP == somaS){
        return -1;
    }
}

float homensMaisMulher(vector<int> vec)
{
    float somaH = 0, somaM, mediaH = 0, mediaM = 0;
    int contH = 0, contM = 0;
    for (int i = 0; i < vec.size(); ++i){
        if(vec[i] < 0){
            vec[i] *= -1;
            somaM = vec[i] + somaM;
            contM++;
        } else if(vec[i] > 0){
            somaH = vec[i] + somaH;
            contH++;
        }
        
    }
    mediaH = somaH/contH;
    mediaM = somaM/contM;

    if(mediaH > mediaM){
        return mediaH;
    } else{
        return -1;
    }
}

int  main()
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
    
    char HouM = mHomemOuMulher(vetor);
    cout << "Na fila existem mais homens ou mulheres: "<< HouM << endl;

    float maisStress = maisEstressados(vetor, tam);
    cout << "Qual metade da fila eh mais estressada (1)(2) ou (-1, para empate)? " << maisStress << endl;

    float mediaHM = homensMaisMulher(vetor);
    cout << "A media do stress dos homens e maior que a das mulheres? "<< mediaHM << endl;
}