#include<iostream>

using namespace std;

// troquei de struct para class, pois a class me permite dizer quem é publico ou privado
class Time{
private: // não quero q tenham acesso a elas
    int hora;
    int minuto; 
    int segundo;

    /*  FUNÇÃO PURA - só ultiliza os paramentros
    1. Muda esse atributo para esse valor, se o valor estiver dentro do intervalo [inferior, superior]
    2. Senão coloca 0
    3. O & no primeiro int é pq eu quero rceber a referencia, e nao a variavel original
    4. Se eu tirar, não vai funcionar pq eu estaria recebendo a copia da hora e passando a copia*/
    static void setIntervalo(int &atr, int value, int inf, int sup){ // função estatica
        if (value >= inf && value <= sup){
            atr = value;
        } else {
            atr = 0;
        }
    }

public:

    Time(int h, int m, int s) /*: hora(h), minuto(m), segundo(s) */{
        this->setHora(h);
        this->setMinuto(m);
        this->setSegundo(s);
    } /*construtor do tempo, inicializei as variaveis
    criei essa metodo que me permite mandar direto para o fluxo, to ensinando o cout imprimir um objeto*/
    
    int getHora(){// serve para eu acessar um atributo que eu teria acesso direto
        return this->hora;
    }

    void setHora(int value){//verificar os limites. Ta modificando a hora
        setIntervalo(this->hora, value, 0, 23);
       /* if(value>= 0 && value <23){
            this-> hora = value;
        }*/
    }

    void setMinuto(int value){ /* os set são contrutores, eles serão usados quando precisar alterar alguma coisa, caso
    não vá alterar nada, não precisa usá-los*/
        setIntervalo(this->minuto, value, 0, 59); // posso fazer assim ou
        /*if(value >= 0 && value <= 59){ assim
            this->minuto = value;
        } else {
            cout << "Minuto invalido"<< endl;
        }*/
    }

    void setSegundo(int value){
        setIntervalo(this-> segundo, value, 0, 59);
        /*if(value >= 0 && value <= 59){
            this->segundo = value;
        } else {
            cout<<"Segundo invalido"<< endl;
        } */
    }

    friend ostream& operator<<(ostream& os, Time tempo){
        os << tempo.hora << "h:" << tempo.minuto << "m:" << tempo.segundo << "s";
        return os;
    }
};



int main()
{
    Time t1(15, 22, 39);

    /*t1.setHora(22);
    t1.setMinuto(45);
    t1.setSegundo(56);*/

    cout<< t1 << endl;

}