#include <iostream>

using namespace std;

//throw para dispara uma execessao
//try cache para pegar a execessao
void funcao1(){
    cout << "tal coisa" << endl;
    throw 5;// quebra a função aqui e vai la pro catch
    cout << "fiz outra coisa " << endl;// se eu tivesse um try aqui, ele executaria e printaria isso, dps seria o fim da função3

}

void funcao2(){
    funcao1();// trata erro de conexão, ele ja quebra aqui

}
 
void funcao3(){
    try { // começa aqui
        funcao2(); // vai pra função 2, que vai pra função 1, na função1
        // ele vai executar ate chegar no throw, vai ver que tem um inteiro e vai voltar pra ca
        // executar o catch que tem um inteiro
    }   catch (int e) {
        cout << "funcao3 pegou o erro: " << e << endl;
    }
    cout << "Fim da funcao3()" << endl;
}

int main(){
    funcao3();
}
