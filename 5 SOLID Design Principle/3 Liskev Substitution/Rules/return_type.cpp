#include <iostream>

using namespace std;

/*Return Type Rule :  Subtype or child having parent method is override then its return type should be either similar to original method of the parent or narrower then the parent method's return type This is also called as return type covariance. default in C++ */


// Base Animal class
class Animal {
public:
    virtual void speak() {
        cout << "Animal is barking" << endl;
    }
    virtual ~Animal() {} // Virtual destructor
};

// Derived Dog class
class Dog : public Animal {
public:
    void speak() override {
        cout << "Dog is barking bow bow" << endl;
    }
};

// Parent class
class Parent {
public:
    virtual Animal* getAnimal() {
        cout << "Parent : Returning Animal instance" << endl;
        return new Animal();
    }
    virtual ~Parent() {}
};

// Child class
class Child : public Parent {
public:
    Animal* getAnimal() override {
        cout << "Child : Returning Dog instance" << endl;
        return new Dog();
    }
};

// Client class
class Client {
private:
    Parent* p;

public:
    Client(Parent* p) {
        this->p = p;
    }

    void takeAnimal() {
        Animal* a = p->getAnimal(); // Runtime polymorphism
        a->speak();                 // Will call Dog's speak() if Child is used
        delete a;                   // Free the memory
    }
};

int main() {
    Parent* parent = new Parent();
    Child* child = new Child();

    // Use child to return Dog
    Client* client = new Client(child);
    client->takeAnimal(); // Will output: Child : Returning Dog instance + Dog is barking bow bow

    // Optional: test with Parent
    Client* client2 = new Client(parent);
    client2->takeAnimal(); // Will output: Parent : Returning Animal instance + Animal is barking

    delete parent;
    delete child;
    delete client;
    delete client2;
    return 0;
}
