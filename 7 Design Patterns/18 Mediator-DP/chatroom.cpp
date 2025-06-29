#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Forward declaration
class User;

// Mediator Interface
class ChatRoomMediator
{
public:
    virtual void showMessage(User* user, const string& message) = 0;
    virtual void registerUser(User* user) = 0;
    virtual ~ChatRoomMediator() {}
};

// Colleague (User)
class User {
protected:
    string name;
    ChatRoomMediator* mediator;

public:
    User(string name, ChatRoomMediator* mediator)
        : name(name), mediator(mediator) {}

    string getName() const { return name; }

    virtual void send(const string& message) {
        mediator->showMessage(this, message);
    }

    virtual void receive(const string& sender, const string& message) {
        cout << "[" << name << " received from " << sender << "]: " << message << endl;
    }
};

// Concrete Mediator
class ChatRoom : public ChatRoomMediator {
private:
    unordered_map<string, User*> users;

public:
    void registerUser(User* user) override {
        users[user->getName()] = user;
    }

    void showMessage(User* sender, const string& message) override {
        for (auto& pair : users) {
            if (pair.first != sender->getName()) {
                pair.second->receive(sender->getName(), message);
            }
        }
    }
};
