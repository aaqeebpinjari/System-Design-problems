#include <iostream>

using namespace std;

// Product 1 --> Burger
class Burger {
public:
    virtual void prepare() = 0;  // Pure virtual function
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

// Product 2 --> GarlicBread
class GarlicBread {
public:
    virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Basic Garlic Bread with butter and garlic!\n";
    }
};

class CheeseGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Cheese Garlic Bread with extra cheese and butter!\n";
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Basic Wheat Garlic Bread with butter and garlic!\n";
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        std::cout << "Preparing Cheese Wheat Garlic Bread with extra cheese and butter!\n";
    }
};

// Factory and its concretions
class MealFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
    virtual GarlicBread* createGarlicBread(string& type) = 0;
};

class SinghBurger : public MealFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "basic") {
            return new BasicGarlicBread();
        } else if (type == "cheese") {
            return new CheeseGarlicBread();
        } 
        else {
            cout << "Invalid Garlic bread type! " << endl;
            return nullptr;
        }
    }
};

class KingBurger : public MealFactory {
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

    GarlicBread* createGarlicBread(string& type) override {
        if (type == "basic") {
            return new BasicWheatGarlicBread();
        } else if (type == "cheese") {
            return new CheeseWheatGarlicBread();
        } 
        else {
            cout << "Invalid Garlic bread type! " << endl;
            return nullptr;
        }
    }
};

int main()
{
    int brandChoice, burgerChoice, breadChoice;
    while (true)
    {
        cout << "\n******   Meal Ordering System    ******\n";
        cout << "Select Meal Brand:\n";
        cout << "1. SinghBurger (Regular Bun + Garlic Bread)\n";
        cout << "2. KingBurger (Wheat Bun + Garlic Bread)\n";
        cout << "0. Exit\n";
        cout << "Enter brand choice: ";
        cin >> brandChoice;

        if (brandChoice == 0)
        {
            cout << "Exiting... Thank you!\n";
            break;
        }

        MealFactory* mealFactory = nullptr;
        switch (brandChoice)
        {
            case 1:
                mealFactory = new SinghBurger();
                break;
            case 2:
                mealFactory = new KingBurger();
                break;
            default:
                cout << "Invalid brand choice. Try again.\n";
                continue;
        }

        // --- Select Burger Type ---
        cout << "\nChoose Burger Type:\n";
        cout << "1. Basic\n";
        cout << "2. Standard\n";
        cout << "3. Premium\n";
        cout << "Enter burger choice: ";
        cin >> burgerChoice;

        string burgerType;
        switch (burgerChoice)
        {
            case 1: burgerType = "basic"; break;
            case 2: burgerType = "standard"; break;
            case 3: burgerType = "premium"; break;
            default:
                cout << "Invalid burger choice.\n";
                delete mealFactory;
                continue;
        }

        // --- Select Garlic Bread Type ---
        cout << "\nChoose Garlic Bread Type:\n";
        cout << "1. Basic\n";
        cout << "2. Cheese\n";
        cout << "Enter garlic bread choice: ";
        cin >> breadChoice;

        string breadType;
        switch (breadChoice)
        {
            case 1: breadType = "basic"; break;
            case 2: breadType = "cheese"; break;
            default:
                cout << "Invalid garlic bread choice.\n";
                delete mealFactory;
                continue;
        }

        // Create and prepare meal
        Burger* burger = mealFactory->createBurger(burgerType);
        GarlicBread* garlicBread = mealFactory->createGarlicBread(breadType);

        if (burger && garlicBread)
        {
            cout << "\n--- Your Meal ---\n";
            burger->prepare();
            garlicBread->prepare();
        } else
        
        {
            cout << "Error creating meal. Please try again.\n";
        }
        // Clean up memory
        delete burger;
        delete garlicBread;
        delete mealFactory;
    }
    return 0;
}
