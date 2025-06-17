#include <iostream>
using namespace std;

// --- Strategy Interface for Walk ---
class WalkableRobot
{
    public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {}
};

// --- Concrete Strategies for walk ---
class NormalWalk : public WalkableRobot
{
    public:
    void walk() override 
    { 
        cout << "Walking normally..." << endl; 
    }
};

class NoWalk : public WalkableRobot
{
    public:
    void walk() override
    { 
        cout << "Cannot walk." << endl; 
    }
};


// --- Strategy Interface for Talk ---
class TalkableRobot
{
    public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// --- Concrete Strategies for Talk ---
class NormalTalk : public TalkableRobot
{
    public:
    void talk() override
    { 
        cout << "Talking normally..." << endl; 
    }
};

class NoTalk : public TalkableRobot
{
    public:
    void talk() override
    { 
        cout << "Cannot talk." << endl; 
    }
};

// --- Strategy Interface for Fly ---
class FlyableRobot
{
    public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {}
};

class NormalFly : public FlyableRobot
{
    public:
    void fly() override
    { 
        cout << "Flying normally..." << endl; 
    }

    virtual ~NormalFly(){};
};

class NoFly : public FlyableRobot
{
    public:
    void fly() override 
    { 
        cout << "Cannot fly." << endl; 
    }

    
};

// --- Robot Base Class ---
class Robot
{
    protected:
    WalkableRobot* walkBehavior;
    TalkableRobot* talkBehavior;
    FlyableRobot* flyBehavior;


    public:
    
    Robot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
    {
        this->walkBehavior = w;
        this->talkBehavior = t;
        this->flyBehavior = f;
    }
       
    void walk() { 
        walkBehavior->walk(); 
    }
    void talk() { 
        talkBehavior->talk(); 
    }
    void fly() { 
        flyBehavior->fly(); 
    }

    void setWalkBehavior(WalkableRobot* w) {
        delete walkBehavior;
        walkBehavior = w;
    }

    void setTalkBehavior(TalkableRobot* t) {
        delete talkBehavior;
        talkBehavior = t;
    }

    void setFlyBehavior(FlyableRobot* f) {
        delete flyBehavior;
        flyBehavior = f;
    }


    virtual void projection() = 0; // Abstract method for subclasses

    ~Robot() {};
};

// --- Concrete Robot Types ---
class CompanionRobot : public Robot
{
    public:
    CompanionRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
        : Robot(w, t, f) {}

    void projection() override {
        cout << "Displaying friendly companion features..." << endl;
    }
};

class WorkerRobot : public Robot
{
    public:
    WorkerRobot(WalkableRobot* w, TalkableRobot* t, FlyableRobot* f)
        : Robot(w, t, f) {}

    void projection() override {
        cout << "Displaying worker efficiency stats..." << endl;
    }
};

// ------ Main Function for Client -------
int main() {
    Robot* robot = nullptr;
    int robotType;

    cout << "Choose Robot Type:\n";
    cout << "1. Companion Robot\n";
    cout << "2. Worker Robot\n";
    cin >> robotType;

    if (robotType == 1)
    {
        robot = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    } 
    
    else if (robotType == 2)
    {
        robot = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());
    } 
    
    else {
        cout << "Invalid choice.\n";
        return 1;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Walk\n";
        cout << "2. Talk\n";
        cout << "3. Fly\n";
        cout << "4. Projection\n";
        cout << "5. Change Fly Behavior to Normal\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                robot->walk();
                break;
            case 2:
                robot->talk();
                break;
            case 3:
                robot->fly();
                break;
            case 4:
                robot->projection();
                break;
            case 5:
                robot->setFlyBehavior(new NormalFly());
                cout << "Fly behavior changed to Normal.\n";
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    delete robot;
    return 0;
}
