#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Forward declaration
class IColleague;

// Mediator Interface
class IMediator {
public:
    virtual void sendAll(IColleague* from, const string& msg) = 0;
    virtual void sendTo(IColleague* from, const string& to, const string& msg) = 0;
    virtual void registerUser(IColleague* user) = 0;
    virtual void mute(const string& from, const string& to) = 0;
    virtual void unmute(const string& from, const string& to) = 0;
    virtual void listUsers() const = 0;
    virtual ~IMediator() {}
};

// Colleague Interface
class IColleague {
protected:
    IMediator* mediator;
public:
    virtual void sendAll(const string& msg) = 0;
    virtual void sendTo(const string& to, const string& msg) = 0;
    virtual void receive(const string& from, const string& msg) = 0;
    virtual string getName() const = 0;
    virtual void setMediator(IMediator* m) { mediator = m; }
    virtual ~IColleague() {}
};

// Concrete Colleague
class User : public IColleague {
    string name;
public:
    User(const string& name) : name(name) {}

    void sendAll(const string& msg) override {
        mediator->sendAll(this, msg);
    }

    void sendTo(const string& to, const string& msg) override {
        mediator->sendTo(this, to, msg);
    }

    void receive(const string& from, const string& msg) override {
        cout << "[Message to " << name << " from " << from << "]: " << msg << endl;
    }

    string getName() const override {
        return name;
    }
};

// Concrete Mediator
class ChatMediator : public IMediator {
    unordered_map<string, IColleague*> users;
    unordered_map<string, unordered_set<string>> muteMap;

public:
    void registerUser(IColleague* user) override {
        user->setMediator(this);
        users[user->getName()] = user;
        cout << user->getName() << " has joined the chat.\n";
    }

    void sendAll(IColleague* from, const string& msg) override {
        string sender = from->getName();
        for (const auto& [name, user] : users) {
            if (name != sender && muteMap[name].find(sender) == muteMap[name].end()) {
                user->receive(sender, msg);
            }
        }
    }

    void sendTo(IColleague* from, const string& to, const string& msg) override {
        string sender = from->getName();
        if (users.count(to) && muteMap[to].find(sender) == muteMap[to].end()) {
            users[to]->receive(sender, msg);
        } else {
            cout << "[Message failed] User \"" << to << "\" not found or muted you.\n";
        }
    }

    void mute(const string& from, const string& to) override {
        if (users.count(to)) {
            muteMap[to].insert(from);
            cout << from << " has been muted for " << to << ".\n";
        } else {
            cout << "User not found.\n";
        }
    }

    void unmute(const string& from, const string& to) override {
        if (muteMap[to].erase(from)) {
            cout << from << " has been unmuted for " << to << ".\n";
        } else {
            cout << from << " was not muted for " << to << ".\n";
        }
    }

    void listUsers() const override {
        cout << "--- Users in Chat ---\n";
        for (const auto& [name, _] : users) {
            cout << name << endl;
        }
    }
};

int main() {
    ChatMediator chat;

    User alice("Alice"), bob("Bob"), charlie("Charlie");
    chat.registerUser(&alice);
    chat.registerUser(&bob);
    chat.registerUser(&charlie);

    int choice;
    string sender, recipient, msg;

    do {
        cout << "\n==== MENU ====" << endl;
        cout << "1. Send to All\n2. Send to User\n3. Mute\n4. Unmute\n5. List Users\n0. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Sender: "; getline(cin, sender);
                cout << "Message: "; getline(cin, msg);
                if (sender == "Alice") alice.sendAll(msg);
                else if (sender == "Bob") bob.sendAll(msg);
                else if (sender == "Charlie") charlie.sendAll(msg);
                else cout << "Invalid sender.\n";
                break;

            case 2:
                cout << "Sender: "; getline(cin, sender);
                cout << "Recipient: "; getline(cin, recipient);
                cout << "Message: "; getline(cin, msg);
                if (sender == "Alice") alice.sendTo(recipient, msg);
                else if (sender == "Bob") bob.sendTo(recipient, msg);
                else if (sender == "Charlie") charlie.sendTo(recipient, msg);
                else cout << "Invalid sender.\n";
                break;

            case 3:
                cout << "Mute [From]: "; getline(cin, sender);
                cout << "Mute [To]: "; getline(cin, recipient);
                chat.mute(sender, recipient);
                break;

            case 4:
                cout << "Unmute [From]: "; getline(cin, sender);
                cout << "Unmute [To]: "; getline(cin, recipient);
                chat.unmute(sender, recipient);
                break;

            case 5:
                chat.listUsers();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
