#include<iostream>
#include<string>
using namespace std;

/*Inheritance: It involves using access modifiers such as private, public and protected
and child inherting the parent class using this to maintain the security, let me make it simple
there are methods and data members in the parent and we can access them by child derived from it using 
access specifers and note that 
abstraction: we have methods whihc will be overriden since it hides implementaion
inhertiance: we can access parents class and we create object of derived class not like
abstraction where we create object of parent and pointing it to the child class */


class Car{
    protected:
    string brandOfCar;
    string modelOfCar;
    bool isEngineOn;
    int currentSpeed;

    public:
    Car(string b, string m){
        this->brandOfCar = b;
        this->modelOfCar = m;
        isEngineOn= false;
        currentSpeed=0; 
    }

    void startEngine(){
        isEngineOn= true;
        cout<<"The car "<<brandOfCar<<", Having Model "<<modelOfCar<<" : Engine started ! "<<endl;
    }

    void stopEngine(){
        if(isEngineOn == true)
        {
            isEngineOn= false;
            cout<<"The car "<<brandOfCar<<", Having Model "<<modelOfCar<<" : Engine Stopped! "<<endl;
        }

        else{
            cout<<"The Engine is already off , Please Start the Engine !!!"<<endl;
        }
    }

    void accelerate()
    {
        if (!isEngineOn ){
            cout<<"Sorry, but car can't be accelerated, As Engine is Off! ";
        }
        else{
            currentSpeed +=70;
            cout<<"The car "<<brandOfCar<<", Having Model "<<modelOfCar<<" : Engine has been accelerated by "<<currentSpeed<<"ratttta rattta rattta rattta rattta "<<endl;
        }
    }

    void brake()
    {
        if (isEngineOn==true and currentSpeed >10)
        {
            currentSpeed -= 50;
            cout<< "Applied brakes, the speed was reduced by "<<currentSpeed<<"km/hr"<<endl;
        }

        else{
            cout<<"Either speed is already low or Engine is Off! "<<endl;
        }
    }

    virtual ~Car() {};

};

/*there are two types of car, manual and electric will be inherting all the properties of the parent class Car
and this child class can extends its properties too by their own*/

class Electric_Car: public Car
{
    private:
    int batteryLevel =80;

    public:

    Electric_Car(string b, string m) : Car(b, m) 
    {
        batteryLevel = 80;  // default battery level
    }
    void display()
    {
        cout<<"The car "<<brandOfCar<<", Having Model "<<modelOfCar<<" : is Having battery level "<<batteryLevel<<" % "<<endl;

    }
};

class Manual_Car: public Car
{
    private:
    int current_gear;

    public:
    Manual_Car(string b, string m):Car(b,m){
        current_gear =0;
    }

    //assigning gear shift
    void shiftgear(int gear)
    {
        if (!isEngineOn )
        {
            cout<<"Sorry brother, Engine Is off , and tu gear badalra !!! "<<endl;
        }
        else if( gear<=7 and gear >0)
        {
            current_gear= gear;
            cout<<" ye hue naa baat, shifted the gear to "<< current_gear<<"ratttta rattta rattta rattta rattta "<<endl;
        }
    }
};

int main() {
    bool exitProgram = false;

    while (!exitProgram) {
        int carChoice;
        cout << "\n--- Select Your Car ---" << endl;
        cout << "1. Manual Car" << endl;
        cout << "2. Electric Car" << endl;
        cout << "0. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> carChoice;

        if (carChoice == 1) 
        {
            //creted object of derived class and based on the access we use the parent class 
            // data members...
            Manual_Car* myCar = new Manual_Car("Toyota", "Supra");
            bool running = true;
            while (running)
            {
                int choice;
                cout << "\n--- Manual Car Control Menu ---" << endl;
                cout << "1. Start Engine" << endl;
                cout << "2. Accelerate" << endl;
                cout << "3. Apply Brake" << endl;
                cout << "4. Shift Gear" << endl;
                cout << "5. Stop Engine" << endl;
                cout << "6. Back to Car Selection" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1: myCar->startEngine(); break;
                    case 2: myCar->accelerate(); break;
                    case 3: myCar->brake(); break;
                    case 4:
                        int gear;
                        cout << "Enter gear number: ";
                        cin >> gear;
                        myCar->shiftgear(gear);
                        break;
                    case 5: myCar->stopEngine(); break;
                    case 6:
                        running = false;
                        cout << "Returning to car selection..." << endl;
                        break;
                    default: cout << "Invalid choice!" << endl;
                }
            }
            delete myCar;
        }
        else if (carChoice == 2)
        {
            //creted object of derived class and based on the access we use the parent class 
            // data members...
            Electric_Car* electricCar = new Electric_Car("Tesla", "Model S");
            bool running = true;
            while (running)
            {
                int choice;
                cout << "\n--- Electric Car Control Menu ---" << endl;
                cout << "1. Start Engine" << endl;
                cout << "2. Accelerate" << endl;
                cout << "3. Apply Brake" << endl;
                cout << "4. Show Battery Level" << endl;
                cout << "5. Stop Engine" << endl;
                cout << "6. Back to Car Selection" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1: electricCar->startEngine(); break;
                    case 2: electricCar->accelerate(); break;
                    case 3: electricCar->brake(); break;
                    case 4: electricCar->display(); break;
                    case 5: electricCar->stopEngine(); break;
                    case 6:
                        running = false;
                        cout << "Returning to car selection..." << endl;
                        break;
                    default: cout << "Invalid choice!" << endl;
                }
            }
            delete electricCar;
        }
        else if (carChoice == 0) 
        {
            exitProgram = true;
            cout << "Exiting program. Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid selection. Try again." << endl;
        }
    }
    return 0;
}

