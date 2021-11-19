#include <iostream>
#include <vector>

enum class Label{
    ABERTURA,
    SAQUE,
    DEPOSITO,
    TARIFA,
    EXTORNO
};

std::string toString(Label op) {
    switch(op) {
        case Label::ABERTURA:
            return "Abertura";
        case Label::SAQUE:
            return "Saque";
        case Label::DEPOSITO:
            return "Deposito";
        case Label::TARIFA:
            return "Tarifa";
        case Label::EXTORNO:
            return "Extorno";
        default:
            return "";
    }
}

class Operacao {
public:
    Label label;
    int indice;
    int valor;
    int saldo;
    Operacao(Label label, int indice, int valor, int saldo) {
        this->label = label;
        this->indice = indice;
        this->valor = valor;
        this->saldo = saldo;
    }
    friend std::ostream& operator<<(std::ostream& os, const Operacao& op) {
        os << toString(op.label) << ":" << op.indice << ":" << op.valor << ":" << op.saldo;
        return os;
    }
};

class Conta {
    std::vector<Operacao> extrato;
    int saldo;
    int num;
    int nextId {0};

    public: 
    Conta(int num, int saldo) {
        this->num = num;
        this->saldo = saldo;
        extrato.push_back(Operacao(Label::ABERTURA, this->nextId++, saldo, saldo));
    }

    bool saque(int valor) {
        if (valor < 0) {
            std::cout << "Valor inválido\n";
            return false;
        }
        if (this->saldo < valor) {
            std::cout << "Saldo insuficiente\n";
            return false;
        }
        saldo -= valor;
        extrato.push_back(Operacao(Label::SAQUE, this->nextId++, -valor, saldo));
        return true;
    }

    bool deposito(int valor) {
        if (valor < 0) {
            std::cout << "Valor inválido\n";
            return false;
        }
        this->saldo += valor;
        this->extrato.push_back(Operacao(Label::SAQUE, this->nextId++, valor, saldo));
        return true;
    }

    void tarifa(int valor) {
        if (valor < 0) {
            std::cout << "Valor inválido\n";
            return;
        }
        this->saldo -= valor;
        this->extrato.push_back(Operacao(Label::TARIFA, this->nextId++, -valor, saldo));
    }

    void extornar(int indice) {
        for(auto& op : extrato){

        }
        //percorre o vetor procurando por uma operacao com esse indice
        //verifica se eh um tarifa
        //credita o valor dessa tarifa no fim do extrato
    }

};

int main() {
    std::cout << toString(static_cast<Label>(2));
    return 0;
}
