#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include <utility>
#include <set>

using namespace std;

class Message{
private:
    int id;
    string username;
    string msg;
    set<string> likes;// Using a Set would eliminate duplicates
    int getId();
    //Initialize all attributes
public:
    Message(int id = 0, string username = " ", string msg = " "):
        id{id}, username{username}, msg{msg}{}
    
    //add username to likes collection
    virtual void like(string username){
        if(likes.find(username) == likes.end()){
            likes.insert(username);
            return;
        }
        throw runtime_error("fail: user " + username + " curtiu");
    }

    int getId(){
        return this->id;
    }

        // mount output string
    friend iostream &operator<<(iostream &os, Message& msg){
        os << msg.id << ":" << msg.username << " ( " << msg.msg << " )";
        int msg = msg.likes.size();
        if (msg.likes.size() > 0){
            int count = 0;
            os << "[ ";
            for (auto user : msg.likes){
                if (count >= msg){
                    os << user;
                    break;
                }
                os << user << ", ";
                count++;
            }
            os << " ]";
        }
        return os;
    }
};

class Inbox {
private:
    map<int, Message*> unread; //store unread tweets
    map<int, Message*> allMsgs; // store read tweets

    vector<shared_ptr<Message>> message(auto messages){
        vector<Message> cont;
        for(auto i : messages){
            cont.push_back(*i.second);
        }
        return cont;
    }

public: 
    Inbox(){}
    //stores message both in unread as in allMsgs
    void receiveNew(Message* tweet){
        auto pairTweet = std::make_pair(tweet->getId(), tweet);
        allMsgs.insert(pairTweet);
        unread.insert(pairTweet);
    }

    //stores message as a readed Message
    void store(Message* tweet){
        if (unread.count(tweet->getId()) == 1){
            unread.erase(tweet->getId());
            return;
        }
    }

    //return unread and clean unread Msgs
    map<int, Message *> getUnread(){
        return this->unread;
    }
    //return all messages
    map<int, Message *> getAllMsg(){
        return this->allMsgs;
    }
    //search for a tweet with this id and return it or throw a MessageException
    Message getTweet(int id){
        auto it = this->getUnread().find(id);
        if (it == unread.end()){
            throw runtime_error("fail: tweet nao existe");
        }
        return *it->second;
    }

    //return allMsgs
   friend iostream& operator<<(iostream& os, Inbox inbox) {
       for (auto i : inbox.getAllMsg()){
           os << i << '\n';
       }
       return os;
    }
};

class User{
private:
    string username;
    Inbox inbox;
    map<string, User *> followers;
    map<string, User *> following;

public:

    User(const string &username) : 
    username{username}, inbox{}, followers{}, following{} {}

    void sendTweet(Message *msg){
        for (auto i : followers){
            i.second->inbox.receiveNew(msg);
        }
    }
 
    void follow(User *other){
        auto it = other->followers.find(username);
        if (it == other->followers.end()){
            following[other->username] = other;
            other->followers[username] = this;
            return;
        }
        throw runtime_error("fail: usuario nao encotrado");
    }

    void unfollow(string* username){
        auto it = following.find(username);
        if (it != following.end()){
            it->second->followers.erase(it->second->followers.find(this->username));
            following.erase(it);
            return;
        }
        throw runtime_error("fail: usuario nao encotrado");
    }

    void like(int twId){
        inbox.getTweet(twId)->like(username);
    }

    Inbox &getInbox(){
        return this->inbox;
    }

    friend ostream &operator<<(ostream &os, const User &user){
        os << user.username << endl;
        os << " following [";
        int count{1};
        for (auto i : user.following){
            if (count >= (int)user.following.size()){
                os << i.second->username;
                count = 1;
                break;
            }
            os << i.second->username << ", " << endl;
            count++;
        }
        os << " ] " << endl;
        os << " followers [";
        for (auto i : user.followers){
            if (count >= (int)user.followers.size()){
                os << i.second->username;
                break;
            }
            os << i.second->username << ", " << endl;
            count++;
        }
        os << " ] "<< endl;
        return os;
    }
    
};

class Controller{
private:
    map<std::string, User *> users;
    map<int, Message *> tweets;
    int nextTwId;

    Message *createTweet(string username, string msg){
        Message *tweet = new Message(nextTwId, username, msg);
        this->tweets.insert(make_pair(nextTwId, tweet));
        nextTwId++;
        return tweet;
    }

public:
    Controller() : users{}, tweets{}, nextTwId{0} {}

    ~Controller(){}

    void addUser(string &username){
        if (this->users.find(username)->first != username){
            User *user = new User(username);
            this->users.insert(std::make_pair(username, user));
            return;
        }
    }

    User *getUser(const string &username){
        if (this->users.find(username)->first == username){
            return this->users.find(username)->second;
        }
        throw runtime_error("fail: usuario nao encontrado");
    }

    void sendTweet(const string &username, const string &msg){
        this->getUser(username)->sendTweet(this->createTweet(username, msg));
    }

    friend std::ostream &operator<<(std::ostream &os, const Controller &ctrl){
        for (auto it : ctrl.users){
            os << *it.second;
        }
        return os;
    }
};

int main(){
    Controller controle;

    while (true){
        string line{}, cmd{};
        getline(std::cin, line);
        stringstream ss(line);
        ss >> cmd;
        cout << "$" << line << endl;
        cout << endl;

        if (cmd == "end") {
            break;
        } else if (cmd == "addUser") {
            std::string name;
            ss >> name;
            controle.addUser(name);
            std::cout << std::endl;
        } else if (cmd == "show") {
            cout << controle;
            cout << endl;
        } else if (cmd == "follow") {
            string following, follower;
            ss >> following;
            ss >> follower;
            
            try {
                controle.getUser(follower)->follow(controle.getUser(following));
            }

            catch (char const *error){
                cout << "User not found" << endl;
            }
            cout << endl;
        } else if (cmd == "twittar") {
            string tweet, user;
            ss >> user;
            tweet = ss.str();
            controle.sendTweet(user, tweet);
            cout << endl;
        } else if (cmd == "unread") {
            string username;
            ss >> username;
            controle.getUser(username);
            cout << endl;
        } else if (cmd == "timeline") {
            string username;
            ss >> username;
            controle.getUser(username);
            cout << std::endl;
        } else if (cmd == "like"){
            string username;
            int twId;
            ss >> username;
            ss >> twId;
            controle.getUser(username)->like(twId);
            cout << std::endl;
        } else if (cmd == "unfollow") {
            string unfollow, unfollower;
            ss >> unfollow;
            ss >> unfollower;
            controle.getUser(unfollower)->unfollow(controle.getUser(unfollow));
            cout << endl;
        } else {
            cout << "Comando invalido" << endl;
            cout << endl;
        }
    }
        
}
