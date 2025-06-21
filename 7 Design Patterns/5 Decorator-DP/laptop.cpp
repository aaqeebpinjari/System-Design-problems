#include <iostream>
#include <string>
using namespace std;

//  ================= Step 1: Base Interface =================
class Laptop
{
public:
    virtual string getDescription() = 0; // Return laptop description
    virtual int getPrice() = 0;          // Return total price
    virtual ~Laptop() {}
};


// ================= Step 2: Concrete Component =================
class BasicLaptop : public Laptop {
public:
    string getDescription() override
    {
        return "Basic Laptop";
    }

    int getPrice() override
    {
        return 40000; // ₹40,000
    }
};


// ================= Step 3: Decorator Base Class =================
class LaptopDecorator : public Laptop
{
    protected:
    Laptop* laptop; // Composition: wraps another Laptop
public:
    LaptopDecorator(Laptop* l) : laptop(l) {}
    virtual ~LaptopDecorator()
    {
        delete laptop;
    }
};
//================= Step 4: Concrete Decorators =================
// 1. RAM Upgrade
class RAMUpgrade : public LaptopDecorator {
public:
    RAMUpgrade(Laptop* l) : LaptopDecorator(l) {}
    string getDescription() override {
        return laptop->getDescription() + " + 8GB RAM";
    }
    int getPrice() override {
        return laptop->getPrice() + 5000; // ₹5,000 for 8GB RAM
    }
};
// 2. SSD Upgrade
class SSDUpgrade : public LaptopDecorator
{
    public:
    SSDUpgrade(Laptop* l) : LaptopDecorator(l) {}

    string getDescription() override {
        return laptop->getDescription() + " + 512GB SSD";
    }

    int getPrice() override {
        return laptop->getPrice() + 4000; // ₹4,000 for SSD
    }
};
// 3. Graphics Card Upgrade
class GraphicsCardUpgrade : public LaptopDecorator
{
    public:
    GraphicsCardUpgrade(Laptop* l) : LaptopDecorator(l) {}

    string getDescription() override
    {
        return laptop->getDescription() + " + NVIDIA Graphics";
    }

    int getPrice() override
    {
        return laptop->getPrice() + 15000; // ₹15,000 for GPU
    }
};
// 4. Extended Warranty
class WarrantyExtension : public LaptopDecorator
{
    public:
    WarrantyExtension(Laptop* l) : LaptopDecorator(l) {}

    string getDescription() override {
        return laptop->getDescription() + " + 2-Year Extended Warranty";
    }

    int getPrice() override {
        return laptop->getPrice() + 2000; // ₹2,000 for warranty
    }
};

// ================= Step 5: Main Function =================
int main() {
    Laptop* myLaptop = new BasicLaptop(); // Base laptop

    cout << "Customize your laptop:\n";
    cout << "1. Add RAM Upgrade (+ Rs.5000)\n";
    cout << "2. Add SSD Upgrade (+ Rs.4000)\n";
    cout << "3. Add Graphics Card (+ Rs.15000)\n";
    cout << "4. Add Extended Warranty (+ Rs.2000)\n";
    cout << "Enter options one by one (e.g. 1 2 4), end with 0: ";

    int option;
    while (cin >> option && option != 0) {
        switch (option) {
            case 1: myLaptop = new RAMUpgrade(myLaptop); break;
            case 2: myLaptop = new SSDUpgrade(myLaptop); break;
            case 3: myLaptop = new GraphicsCardUpgrade(myLaptop); break;
            case 4: myLaptop = new WarrantyExtension(myLaptop); break;
            default: cout << "Invalid option!\n"; break;
        }
    }

    cout << "\n===== Final Laptop Config =====\n";
    cout << "Description: " << myLaptop->getDescription() << endl;
    cout << "Total Price: Rupess " << myLaptop->getPrice() << endl;

    delete myLaptop;
    return 0;
}