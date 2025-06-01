#include<iostream>
#include<string>
using namespace std;


class Car
{
    public:
        virtual void startEngine()=0;
        virtual void shiftGear(int gear) =0;
        virtual void accelerate() =0;
        virtual void brake()=0;
        virtual void stopEngine()=0;
        virtual void Speed()=0;
        virtual ~Car(){};
};

class sportsCar: public Car
{
    public:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;

        public:
        sportsCar(string brandname, string modelname)
        {
            this ->brand = brandname;
            this ->model = modelname;
            isEngineOn =0;
            currentSpeed=0;
            currentGear=0; 
        }

        void startEngine(){
            if (!isEngineOn)
            {
                isEngineOn=true;
                cout<<"The name of car brand is "<<brand<<" having model "<<model<<" : Engine starts with a roar! "<<endl;
            }
            else
            {
                cout<<"Car is On, Engine has already started bro!, give the raise rattttttaaa rattttttaaaa !!!"<<endl;
            }
        }

        void shiftGear(int gear)
        {
            if (isEngineOn)
            {
                 if( gear>0 and gear <9 )
                {
                    currentGear= gear;
                    cout<<"The name of car brand is "<<brand<<" having model "<<model<<": shifted the gear to "<<currentGear<<endl;
                }
                else{
                    cout<<"This gear is not possible, Jaake Rocket Uda !"<<endl;
                }
            }
            else
            {
                cout<<"This gear is not possible bro, start the engine !..."<<endl;
            }
            
        }      

        void accelerate()
        {
            if (!isEngineOn)
            {
                cout<<"The name of car brand is "<<brand<<" having model "<<model<<" : Engine is off, can't Accelerate, Turn On the Engine bro !"<<endl;
            }

            else
            {
                currentSpeed+=100;
                cout<<"The name of car brand is "<<brand<<" having model "<<model<<" : Accelerated the car by "<<currentSpeed<<"km/hr "<<endl;
            }            
        }

        
        void brake()
        {
            if (isEngineOn)
            {
                currentSpeed -=50;
                cout<<"Applied brakes and speed of the "<<model<<" Reduced by 50"<<endl;
                cout<<"Current Speed of "<<model<< " is "<<currentSpeed<<endl;
            }

            else{
                cout<<"Can't Apply the brakes, Turn On the Engine Stupid ! ..."<<endl;
            }
        }

        void Speed()
        {
            cout<<"The current Speed of "<<model<<" is "<<currentSpeed<<"km/hr"<<endl;
        }

        void stopEngine()
        {
            isEngineOn= false;
            currentGear =0;
            currentSpeed =0;
            cout<<"The name of car brand is "<<brand<<" having model "<<model<<" : Turn off the Engine!"<<endl;
        }

};
int main()
{
    Car* myCar = new sportsCar("Toyota","Supra");
    bool running = true;
    int choice;

    while (running)
    {
        cout << "\n--- Select the choice ---" << endl;
        cout << "1. Start Engine" << endl;
        cout << "2. Shift Gear" << endl;
        cout << "3. Accelerate" << endl;
        cout << "4. Brake" << endl;
        cout << "5. Current Speed"<<endl;
        cout << "6. Stop Engine (Exit)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                myCar->startEngine();
                break;
            case 2:
                int gear;
                cout << "Enter gear to shift: ";
                cin >> gear;
                myCar->shiftGear(gear);
                break;
            case 3:
                myCar->accelerate();
                break;
            case 4:
                myCar->brake();
                break;

            case 5:
                myCar -> Speed();
                break;
            case 6:
                myCar->stopEngine();
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    delete myCar; // free the allocated memory
    return 0;
}