#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Strategy Interface
class TransportStrategy
{
    public:
    virtual void travel(const string& from, const string& to, double distance) = 0;
    virtual double estimateCost(double distance) = 0;
    virtual double estimateTime(double distance) = 0;


    //destroying the class.
    virtual ~TransportStrategy() {}
};

// Concrete Strategy: Car
class CarTransport : public TransportStrategy
{
    public:
    void travel(const string& from, const string& to, double distance) override 
    {
        cout << "Traveling by Car from " << from << " to " << to << ".\n";
    }

    double estimateCost(double distance) override
    {
        return distance * 10;  // ₹10 per km
    }

    double estimateTime(double distance) override 
    {
        return distance / 60.0;  // 60 km/h
    }
};

// Concrete Strategy: Flight
class FlightTransport : public TransportStrategy
{
    public:
    void travel(const string& from, const string& to, double distance) override
    {
        cout << "Flying from " << from << " to " << to << ".\n";
    }

    double estimateCost(double distance) override 
    {
        return distance * 20;  // ₹20 per km
    }

    double estimateTime(double distance) override
    {
        return distance / 500.0;  // 500 km/h
    }
};

// Concrete Strategy: Train
class TrainTransport : public TransportStrategy
{
    public:
    void travel(const string& from, const string& to, double distance) override
    {
        cout << "Taking a Train from " << from << " to " << to << ".\n";
    }

    double estimateCost(double distance) override
    {
        return distance * 3;  // ₹3 per km
    }

    double estimateTime(double distance) override
    {
        return distance / 80.0;  // 80 km/h
    }
};

// Concrete Strategy: Bike
class BikeTransport : public TransportStrategy
{
    public:
    void travel(const string& from, const string& to, double distance) override 
    {
        cout << "Riding a Bike from " << from << " to " << to << ".\n";
    }

    double estimateCost(double distance) override
    {
        return distance * 5;  // ₹5 per km
    }

    double estimateTime(double distance) override
    {
        return distance / 40.0;  // 40 km/h
    }
};

class TransportService
{
    TransportStrategy* strategy;

    public:
    TransportService(TransportStrategy* strategy) : strategy(strategy) {}

    void setStrategy(TransportStrategy* newStrategy)
    {
        strategy = newStrategy;
    }

    void executeTravel(const string& from, const string& to, double distance)
    {
        strategy->travel(from, to, distance);
        cout << fixed << setprecision(2);
        cout << "Estimated Time: " << strategy->estimateTime(distance) << " hours\n";
        cout << "Estimated Cost: Rs. " << strategy->estimateCost(distance) << endl;
    }

    virtual ~TransportService(){};
};

// -------------------- Main Function for User --------------------
int main() {
    string from, to;
    double distance;
    int choice;

    cout << "Enter source: ";
    cin >> from;
    cout << "Enter destination: ";
    cin >> to;
    cout << "Enter distance (in km): ";
    cin >> distance;

    CarTransport car;
    FlightTransport flight;
    TrainTransport train;
    BikeTransport bike;

    TransportService* service = nullptr;

    do {
        cout << "\nChoose mode of transport:\n";
        cout << "1. Car\n";
        cout << "2. Flight\n";
        cout << "3. Train\n";
        cout << "4. Bike\n";
        cout << "5. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                service = new TransportService(&car);
                break;
            case 2:
                service = new TransportService(&flight);
                break;
            case 3:
                service = new TransportService(&train);
                break;
            case 4:
                service = new TransportService(&bike);
                break;
            case 5:
                cout << "Thank you for using Our planner, meet you Soon!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

        if (choice >= 1 && choice <= 4 && service) {
            service->executeTravel(from, to, distance);
            delete service;
        }

    } while (choice != 5);
    return 0;
}
