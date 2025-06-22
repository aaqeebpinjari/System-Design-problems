#include <iostream>
using namespace std;

// 1. Abstract Base Class
class Beverage {
public:
    // Template method - defines the skeleton
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    virtual ~Beverage() {}

protected:
    void boilWater() {
        cout << "Boiling water\n";
    }

    void pourInCup() {
        cout << "Pouring into cup\n";
    }

    // These will be defined by subclasses
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
};

// 2. Concrete Class: Tea
class Tea : public Beverage {
protected:
    void brew() override {
        cout << "Steeping the tea\n";
    }

    void addCondiments() override {
        cout << "Adding lemon\n";
    }
};

// 3. Concrete Class: Coffee
class Coffee : public Beverage {
protected:
    void brew() override {
        cout << "Dripping coffee through filter\n";
    }

    void addCondiments() override {
        cout << "Adding sugar and milk\n";
    }
};

// 4. Client
int main() {
    Beverage* tea = new Tea();
    cout << "Making tea...\n";
    tea->prepareRecipe();

    cout << "\n";

    Beverage* coffee = new Coffee();
    cout << "Making coffee...\n";
    coffee->prepareRecipe();

    delete tea;
    delete coffee;
    return 0;
}
