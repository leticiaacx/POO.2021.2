#include <iostream>
#include<vector>
#include<map>
#include<memory>

using namespace std;

class Account{
protected: 
    int id;
    float balance{0};// saldo
    string clientId;
    string type; //conta corrente/poupança

public:
    Account(int id, string clientId) : id(id), clientId(clientId){
    };

    virtual void monthlyUpdate() = 0; // metodo para att mensal

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

class CheckingAccount : public Account{// conta corrente
public:
    CheckingAccount(int id, string clientId) : Account{id, clientId}{
        this->type = "CC";// inicializando a conta.type com CC
    };

    virtual void monthlyUpdate(){//atualizações mensais 
        this->balance -= 20;// retirar um saldo de 20 reais
    }
};

class SavingsAccounts : public Account{// conta poupança
public:
    SavingsAccounts(int id, string clientId) : Account{id, clientId}{
        this->type = "CP";
    };

    virtual void monthlyUpdate(){// atualizações mensais 
        this->balance += this->balance * 0.01;//aumentando o saldo em 1%
    }
};

class Client{

    string clientId;
    vector<shared_ptr<Account>> accounts; //varias contas

public:
    Client(string clientId) : clientId{clientId} {//construtor
    };

    virtual void addAccount(const shared_ptr<Account> &account){
        this->accounts.push_back(account); // add contas no final do vector
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
    map<string, shared_ptr<Client>> clients; //mapa com os clientes
    map<int, shared_ptr<Account>> accounts; // mapa com as contas
    int nextAccountId{0};

    virtual shared_ptr<Account> getAccount(int id){ // busca pela conta
        auto it = this->accounts.find(id);
        if (it == this->accounts.end()){
            cout << "Conta nao encontrada no sistema" << endl;
        }

        return it->second;
    }

    bool searchClient(string client){
        auto it = clients.find(client);//procurar dentro do cliente
        if (it != clients.end()){// achou, existente
            return true;
        } else {
            cout << "Cliente nao registrado" << endl;
            return false;
        }
    }
    
public:
    Bank(){};

    virtual void addAccount(string clientId){ // add cliente
        auto it = this->clients.find(clientId);// procurando conta
        if (it != this->clients.end()){// achou
            cout << "Voce ja e nosso client" << endl;// caso ja exista o cliente
        }

        Client c{clientId}; // criando novo cliente

        SavingsAccounts contaP{this->nextAccountId, clientId}; //criando uma conta poupança
        c.addAccount(make_shared<SavingsAccounts>(contaP)); // add a contaP como conta poupança
        this->accounts[this->nextAccountId] = make_shared<SavingsAccounts>(contaP);

        this->nextAccountId++;

        CheckingAccount cc{this->nextAccountId, clientId};//criando uma conta corrente
        c.addAccount(make_shared<CheckingAccount>(cc));// add a cc como conta corrente
        this->accounts[this->nextAccountId] = make_shared<CheckingAccount>(cc);

        this->clients[clientId] = make_shared<Client>(c);
        this->nextAccountId++;
    }

    virtual void withdraw(int idConta, float value){//saque
        shared_ptr<Account> conta{getAccount(idConta)};
        conta->withdraw(value);
    }

    virtual void deposit(int idConta, float value){//deposito
        shared_ptr<Account> conta{getAccount(idConta)};
        conta->deposit(value);
    }

    virtual void transfer(int contaDe, int contaPara, float value){//tranferencia
        shared_ptr<Account> conta{getAccount(contaDe)};
        shared_ptr<Account> conta2{getAccount(contaPara)};

        conta->transfer(conta2, value);
    }

    virtual void monthlyUpdate(){// atualizações mensais
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