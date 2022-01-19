#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <map>

using namespace std;

template <typename T>
using ptr = shared_ptr<T>;

// guardar texto e usuario
class Msg{
public:
    virtual string getSender() = 0;
    virtual string getText() = 0;
    virtual ~Msg () {}

    friend iostream& operator<<(iostream& os, Msg& msg);
};

ostream& operator<<(ostream& os, Msg& msg){
    os << msg.getSender() << ": " << msg.getText() << endl;
    return os;
}

class Imsg : public Msg{
    string sender;
    string text;

public:
    Imsg(string sender, string text){
        this-> sender = sender;
        this-> text = text;
    }

    virtual ~Imsg(){}

    virtual string getSender() override{
        return sender;
    }

    virtual string getText() override{
        return text;
    }
};

//guardar, recuperar e enviar as msgs
class User{
    string username;
    vector<ptr<Msg>> inbox;
    vector<ptr<Msg>> sent;

public:
    User(string username) : username(username){}
    virtual ~User(){}

    void sendMsg(User& receiver, string text){
        auto msg = make_shared<Imsg>(this->username, text);
        receiver.inbox.push_back(msg);
        this->sent.push_back(msg);
    }

    string getInbox(){
        stringstream ss;
        for(auto msg : this->inbox)
            ss << msg <<endl;
            this->inbox.clear();
            return ss.str();
    }

    string getSender(){
        stringstream ss;
        for(auto msg : this->sent)
            ss << msg <<endl;
        return ss.str();
    }
};

// encontrar e gerenciar os usuários
class UserMsg{
    map<string, ptr<User>> users;

public:
    UserMsg(){}

    void addUser(string username){
        if(users.find(username) == users.end()){
            users[username] = make_shared<User>(username);
        } else{
            throw runtime_error("User already exists");
        }
    }

    string getUsername(){
        string result;
        for(auto& it : users){
            result += it.first + " ";
        }
    }

//ponteiro
    User* findUser(string username){
        auto it = users.find(username);
        if(it == users.end()){
            throw runtime_error("User " + username + " not found");
        }
        return it->second.get();
    }

    void sendMsg(string sender, string receiver, string text){
        auto senderUser = findUser(sender);
        auto receiverUser = findUser(receiver);
        senderUser->sendMsg(*receiverUser, text);
    }
};

int main(){
    UserMsg um;
    while(true){
        string line{}, cmd{};
        getline(cin, line);
        stringstream ss(line);
        ss >> cmd; 
        cout << " $ " << line << endl;
        if(cmd == "end"){
            break;
        } else if(cmd == "show") {
            cout << um.getUsername() << endl;
        } else if (cmd == "add") {
            string username{};
            ss >> username;
            um.addUser(username);
        } else if (cmd == "send") {
            string sender{}, receiver{}, text{};
            ss >> sender >> receiver;
            getline(ss, text);
            um.sendMsg(sender, receiver, text.substr(1));
        } else if (cmd == "sent") { 
            string senderUser{};
            ss >> senderUser;
            cout << um.findUser(senderUser)->getSender() << endl;
        } else if (cmd == "inbox") {
            string username{};
            ss >> username;
            cout << um.findUser(username)->getInbox() << endl;
        } else {
            cout << "falil: comando invalido" << endl;
            }
    }
}
