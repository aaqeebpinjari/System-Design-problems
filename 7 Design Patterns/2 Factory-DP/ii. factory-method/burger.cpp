#include <iostream>

using namespace std;

// Product Class and subclasses
class Burger {
public:
    virtual void prepare() = 0;  // Pure virtual function
    virtual ~Burger() {}  // Virtual destructor
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Wheat Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};


/*All implementation are similar to simple factory,just here diff here  
factory act as abstract class and having concrete class as singh and king burger
and based on return type, they return their burger.*/
class BurgerFactory
{
    public:
    virtual Burger* createBurger(string& type) = 0;//pure abstract class..
};

//concrete classes
class SinghBurger : public BurgerFactory
{
    public:
    Burger* createBurger(string& type) override
    {
        if (type == "basic")
        {
            return new BasicBurger();
        } else if (type == "standard")
        {
            return new StandardBurger();
        } else if (type == "premium")
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

class KingBurger : public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicWheatBurger();
        } else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PremiumWheatBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }
};

int main() {
    int brandChoice, typeChoice;
    BurgerFactory* factory = nullptr;

    while (true)
    {
        cout << "\n*********  Welcome to Burger Order System  *********\n";
        cout << "Choose Burger Brand:\n";
        cout << "1. SinghBurger (Regular buns)\n";
        cout << "2. KingBurger (Wheat buns)\n";
        cout << "0. Exit\n";
        cout << "Enter your brand choice: ";
        cin >> brandChoice;

        if (brandChoice == 0)
        {
            cout << "Exiting... Thank you!\n";
            break;
        }

        switch (brandChoice)
        {
            case 1:
                factory = new SinghBurger();
                break;
            case 2:
                factory = new KingBurger();
                break;
            default:
                cout << "Invalid brand choice! Try again.\n";
                continue;
        }

        cout << "\nChoose Burger Type:\n";
        cout << "1. Basic\n";
        cout << "2. Standard\n";
        cout << "3. Premium\n";
        cout << "Enter your type choice: ";
        cin >> typeChoice;

        string burgerType;
        switch (typeChoice)
        {
            case 1:
                burgerType = "basic";
                break;
            case 2:
                burgerType = "standard";
                break;
            case 3:
                burgerType = "premium";
                break;
            default:
                cout << "Invalid type choice! Try again.\n";
                delete factory;
                continue;
        }

        Burger* burger = factory->createBurger(burgerType);
        if (burger) {
            burger->prepare();
            delete burger;
        } else {
            cout << "Burger creation failed.\n";
        }

        delete factory;
        factory = nullptr;
    }
    return 0;
}
