#include <iostream>
using namespace std;

// Command Interface
class Command
{   
    public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};
// Receivers
class Light
{
    public:
    void on() { 
        cout << "Light is ON" << endl; 
    }
    void off()
    { 
        cout << "Light is OFF" << endl;
    }
};
class Fan
{
    public:
    void on() { 
        cout << "Fan is ON" << endl; 
    }
    void off()
    { 
        cout << "Fan is OFF" << endl; 
    }
};
// Concrete Command for Light
class LightCommand : public Command
{
    private:
    Light* light;

    public:
    LightCommand(Light* l){ 
        light = l; 
    }

    void execute(){ 
        light->on(); 
    }

    void undo(){ 
        light->off(); 
    }
};
// Concrete Command for Fan
class FanCommand : public Command
{
    private:
    Fan* fan;

public:
    FanCommand(Fan* f){ 
        fan = f; 
    }
    void execute(){ 
        fan->on(); 
    }
    void undo(){ 
        fan->off(); 
    }
};
// Invoker: Remote Controller with static 2D array of 6 buttons (3 rows, 2 cols)
class RemoteController {
    private:
    static const int numButtons = 4;
    Command* buttons[numButtons];
    bool buttonPressed[numButtons];

    public:
    RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            buttons[i] = nullptr;
            buttonPressed[i] = false;  // false = off, true = on
        }
    }

    void setCommand(int idx, Command* cmd)
    {
        if (idx >= 0 && idx < numButtons)
        {
            if (buttons[idx] != nullptr)
                delete buttons[idx];
            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    void pressButton(int idx)
    {
        if (idx >= 0 && idx < numButtons && buttons[idx] != nullptr) {
            if (buttonPressed[idx] == false)
            {
                buttons[idx]->execute();
            } else {
                buttons[idx]->undo();
            }
            buttonPressed[idx] = !buttonPressed[idx];
        } else {
            cout << "No command assigned at button " << idx << endl;
        }
    }
    ~RemoteController()
    {
        for (int i = 0; i < numButtons; i++)
        {
            if (buttons[i] != NULL)
                delete buttons[i];
        }
    }
};

int main() {
    Light* livingRoomLight = new Light();
    Fan* ceilingFan = new Fan();
    RemoteController* remote = new RemoteController();

    // Assign commands to remote buttons
    remote->setCommand(0, new LightCommand(livingRoomLight));  // Button 0 = Light
    remote->setCommand(1, new FanCommand(ceilingFan));         // Button 1 = Fan

    int choice;

    while (true) {
        cout << "\n=== Remote Controller Menu ===\n";
        cout << "0. Toggle Light (Button 0)\n";
        cout << "1. Toggle Fan   (Button 1)\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 0:
            case 1:
                remote->pressButton(choice);
                break;
            case 2:
                cout << "Exiting...\n";
                delete remote;
                delete livingRoomLight;
                delete ceilingFan;
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;  // not reachable, but syntactically correct
}
