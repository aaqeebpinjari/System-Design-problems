#include<iostream>

using namespace std;

class Singleton
{
    private:
    static Singleton* instance;

    Singleton()
    {
        cout << "Singleton Constructor called" << endl;
    }

//problem is, if two thread tries to enter at same time in first time,
//both gets enter at same time,since it was nullptr
    public:
    static Singleton* getInstance()
    {
        if(instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout << (s1 == s2) << endl;
}