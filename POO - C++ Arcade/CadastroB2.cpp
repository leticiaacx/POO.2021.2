#include <iostream>
#include<vector>
#include<map>
#include<memory>

using namespace std;

class Account{
protected: 
    int id;
    float balance{0};
    string clientId;
    string type;

public:
    Account(int id, string clientId) : id(id), clientId(clientId){
    };

    virtual void monthlyUpdate() = 0;

    virtual void withdraw(float valor){//saque
        if (valor <= 0){ //se o valor for menor que 0, valor invalido
            cout << "Valor invalido" << endl;
        }

        if (this->balance < valor){ // se o valor for menor que balance, saldo insuficiente
            cout << "Saldo insuficiente" << endl;
        }

        this->balance -= valor; // tirar o valor do balance 
    }

    virtual void deposit(float valor){// deposito
        if (valor <= 0){ // quando o valor for menor que 0, valor invalido
            throw "Valor invalido";
        }

        this->balance += valor;// depositar o dinheiro
    }

    virtual void transfer(shared_ptr<Account> other, float valor){// tranferir o dinheiro
        this->withdraw(valor);
        other->deposit(valor);
    }

    virtual int getId() const{
        return this->id;
    }

    virtual float getBalance() const{
        return this->balance;
    }

    virtual string getClientId() const{
        return this->clientId;
    }

    virtual string getType() const{
        return this->type;
    }

    friend std::ostream &operator<<(std::ostream &os, const Account &a){
        os << a.id << ": " << a.clientId << ": " << a.balance << ": " << a.type << endl;
        return os;
    }
};

class CheckingAccount : public Account{
public:
    CheckingAccount(int id, string clientId) : Account{id, clientId}{
        this->type = "CC";// inicializando a conta.type com CC
    };

    virtual void monthlyUpdate(){
        this->balance -= 20;// retirar um saldo de 20 reais
    }
};

class SavingsAccounts : public Account{
public:
    SavingsAccounts(int id, string clientId) : Account{id, clientId}{
    };

    virtual void monthlyUpdate(){
        this->balance += this->balance * 0.01;//aumentando o saldo em 1%
    }
};

class Client{

    string clientId;
    vector<shared_ptr<Account>> accounts;

public:
    Client(string clientId) : clientId{clientId} {//construtor
    };

    virtual void addAccount(const shared_ptr<Account> &account){
        this->accounts.push_back(account);
    }

    virtual string getClientId() const{
        return this->clientId;
    }

    virtual vector<shared_ptr<Account>> getAccounts() const{
        return this->accounts;
    }

    virtual void setClientId(string newClientId){
        this->clientId = newClientId;
    }

    virtual void setAccounts(vector<shared_ptr<Account>> accounts){
        this->accounts = accounts;
    }

    friend std::ostream &operator<<(std::ostream &os, const Client &b){
        os << b.clientId << " [ " << endl;
        for (int i = 0; i < (int)b.accounts.size(); i++){
            os << b.accounts[i]->getId() << ((i + 1 < (int)b.accounts.size()) ? "," : "");
        }
        os << " ]" << endl;

        return os;
    }
};

class Bank{
private:
    map<string, shared_ptr<Client>> clients;
    map<int, shared_ptr<Account>> accounts;
    int nextAccountId{0};

    virtual shared_ptr<Account> getAccount(int id){ 
        auto it = this->accounts.find(id);
        if (it == this->accounts.end()){
            cout << "Conta nao encontrada no sistema" << endl;
        }

        return it->second;
    }

public:
    Bank(){};

    virtual void addAccount(string clientId){ 
        auto it = this->clients.find(clientId);
        if (it != this->clients.end()){
            cout << "Voce ja e nosso client" << endl;
        }

        Client c{clientId};

        SavingsAccounts sa{this->nextAccountId, clientId};
        c.addAccount(make_shared<SavingsAccounts>(sa));
        this->accounts[this->nextAccountId] = make_shared<SavingsAccounts>(sa);

        this->nextAccountId++;

        CheckingAccount cc{this->nextAccountId, clientId};
        c.addAccount(make_shared<CheckingAccount>(cc));
        this->accounts[this->nextAccountId] = make_shared<CheckingAccount>(cc);

        this->clients[clientId] = make_shared<Client>(c);
        this->nextAccountId++;
    }

    virtual void withdraw(int idConta, float value){
        shared_ptr<Account> conta{getAccount(idConta)};
        conta->withdraw(value);
    }

    virtual void deposit(int idConta, float value){
        shared_ptr<Account> conta{getAccount(idConta)};
        conta->deposit(value);
    }

    virtual void transfer(int contaDe, int contaPara, float value){
        shared_ptr<Account> conta{getAccount(contaDe)};
        shared_ptr<Account> conta2{getAccount(contaPara)};

        conta->transfer(conta2, value);
    }

    virtual void monthlyUpdate(){
        for (auto it = this->accounts.begin(); it != this->accounts.end(); ++it){
            it->second->monthlyUpdate();
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Bank& c){
        os << "Clientes: " << endl;
        for (auto it = c.clients.begin(); it != c.clients.end(); ++it){
            os << *it->second;
        }

        os << "Contas: " << endl;

        for (auto it = c.accounts.begin(); it != c.accounts.end(); ++it){
            os << *it->second;
        }

        return os;
    }
};

int main()
{
    Bank banco;
    banco.addAccount("Leticia");
    banco.addAccount("Maria");
    banco.addAccount("Joao");
    cout << banco << endl;

    banco.deposit(0, 200);
    banco.deposit(1, 330);
    banco.deposit(2, 543);
    banco.withdraw(1, 5);
    cout << banco << endl;

    banco.transfer(2, 6, 110);
    cout << banco << endl;

    banco.monthlyUpdate();

    cout << banco << endl;
}