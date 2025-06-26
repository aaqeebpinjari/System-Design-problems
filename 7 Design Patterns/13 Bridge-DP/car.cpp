#include <iostream>
#include <string>

using namespace std;

// Implementation Hierarchy: Engine interface (LLP)
class Engine
{
    public:
    virtual void start() = 0;
    virtual ~Engine() {}
};

// Concrete Implementors (LLL)
class PetrolEngine : public Engine
{
    public:
    void start() override
    {
        cout << "Petrol engine starting with ignition!" << endl;
    }
};

class DieselEngine : public Engine {
public:
    void start() override {
        cout << "Diesel engine roaring to life!" << endl;
    }
};

class ElectricEngine : public Engine {
public:
    void start() override {
        cout << "Electric engine powering up silently!" << endl;
    }
};

// Abstraction Hierarchy: Car (HLL)
class Car
{
    protected:
    Engine* engine;
    
    public:
    Car(Engine* e)
    {
        engine = e;
    }

    virtual void drive() = 0;
};

// Refined Abstraction: Sedan
class Sedan : public Car 
{
    public:
    Sedan(Engine* e) : Car(e) {}

    void drive() override
    {
        engine->start();
        cout << "Driving a Sedan on the highway." << endl;
    }
};

// Refined Abstraction: SUV
class SUV : public Car
{
    public:
    SUV(Engine* e) : Car(e) {}

    void drive() override {
        engine->start();
        cout << "Driving an SUV off-road." << endl;
    }
};
int main() {
    int carChoice, engineChoice;
    cout << "Select Car Type:\n1. Sedan\n2. SUV\nChoice: ";
    cin >> carChoice;

    cout << "\nSelect Engine Type:\n1. Petrol\n2. Diesel\n3. Electric\nChoice: ";
    cin >> engineChoice;

    Engine* engine = nullptr;
    Car* car = nullptr;

    // Create Engine
    switch (engineChoice) {
        case 1: engine = new PetrolEngine(); break;
        case 2: engine = new DieselEngine(); break;
        case 3: engine = new ElectricEngine(); break;
        default:
            cout << "Invalid engine choice!" << endl;
            return 1;
    }

    // Create Car with selected Engine
    switch (carChoice) {
        case 1: car = new Sedan(engine); break;
        case 2: car = new SUV(engine); break;
        default:
            cout << "Invalid car choice!" << endl;
            delete engine;
            return 1;
    }

    // Drive the car
    cout << "\n--- Car Test Drive ---" << endl;
    car->drive();

    // Clean up
    delete car;

    return 0;
}