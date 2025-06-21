#include<iostream>
using namespace std;

class Transport
{
    public:
    virtual void deliver ()=0;
    virtual ~Transport(){};
};

class Car : public Transport
{
    public:
    void deliver () override {
        cout<<"good option brother, Deliver the box by car"<<endl;
    }
};

class Bus : public Transport
{
    public:
    void deliver () override
    {
        cout<<"nice option too, Deliver the box by Bus"<<endl;
    }
};

class Train : public Transport
{
    public:
    void deliver () override {
        cout<<"masha Allah, Deliver the box by train"<<endl;
    }
};

class Ship : public Transport
{
    public:
    void deliver () override {
        cout<<"Deliver the container by ship, seems like a big parcel"<<endl;
    }
};

class Delivery
{
    public:
    static Transport* Deliver(int choice)
    {
        switch (choice)
        {
            case 1: return new Car();
            case 2: return new Bus();
            case 3: return new Train();
            case 4: return new Ship();
            default: return nullptr;
        }
    }
};

int main()
{
    Delivery deliveryService;
    int choice;

    while (true) {
        cout << "\nSelect Delivery Method:\n";
        cout << "1. Car\n";
        cout << "2. Bus\n";
        cout << "3. Train\n";
        cout << "4. Ship\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0)
        {
            cout << "Exiting delivery program.\n";
            break;
        }

        Transport* transport = deliveryService.Deliver(choice);

        if (transport) {
            transport->deliver();
            delete transport; // free memory
        } else {
            cout << "Invalid option! Please try again.\n";
        }
    }
   return 0;
}