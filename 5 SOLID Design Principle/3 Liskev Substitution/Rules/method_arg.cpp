#include <iostream>
using namespace std;

// Method Argument Rule : 
// Subtype method arguments can be identical or wider than the supertype
// C++ enforces this by requiring identical signatures for overrides

class Parent {
public:
    virtual void print(string msg) {
        cout << "Parent: " << msg << endl;
    }
};

class Child : public Parent {
public:
    void print(string msg) override { 
        cout << "Child: " << msg << endl;
    }
};

// Client that uses a Parent pointer
class Client {
private:
    Parent* p;

public:
    Client(Parent* p) {
        this->p = p;
    }

    void printMsg() {
        p->print("Hello");
    }

    ~Client(){};
};

int main() {
    Parent* parent = new Parent();
    Parent* child = new Child(); // Polymorphic behavior

    Client* client = new Client(child); // Works with subclass

    client->printMsg();                 // Calls Child::print

    parent->print("From Parent directly"); 

    // Cleanup (optional for this small program)
    delete parent;
    delete client;
    delete child;

    return 0;
}
