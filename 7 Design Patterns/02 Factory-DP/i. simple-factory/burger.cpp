#include <iostream>
using namespace std;

//remember, simple factory is the desing principle, not a design pattern
//rest two of them are desing principles...
class Burger {
public:
    virtual void prepare() = 0;  // Pure virtual function
    virtual ~Burger() {}  // destructor
};

class BasicBurger : public Burger
{
    public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger
{
    public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger
{
    public:
    void prepare() override
    {
        cout << "Preparing Premium Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};


//this is return class, in which based on type, we return the result
//now we create a object pointing to parent class and instanting the child derived from it
class BurgerFactory {
public:
    Burger* createBurger(string& type)
    {
        if (type == "basic") 
        {
            return new BasicBurger();
        } 
        
        else if (type == "standard")
        {
            return new StandardBurger();
        } 
        
        else if (type == "premium")
        {
            return new PremiumBurger();
        } 
        
        else
        {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }
};

int main()
{
    string type;
    cout << "Enter burger type (basic / standard / premium): ";
    cin >> type;

    BurgerFactory myBurgerFactory;

    Burger* burger = myBurgerFactory.createBurger(type);

    if (burger)
    {
        burger->prepare();
        delete burger;  // Free the allocated memory
    } 
    
    else
    {
        cout << "Burger creation failed due to invalid input." << std::endl;
    }

    delete burger;
    return 0;
}
