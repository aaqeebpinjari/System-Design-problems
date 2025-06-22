#include<iostream>
#include <mutex>//lock for thread
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;

    Singleton() 
    { 
        cout << "Singleton Constructor Called!" << endl; 
    }
 
//lock is costly and now, so use it effectively...
public:
    // Double check locking..
    static Singleton* getInstance() 
    {

//initial checking, two thread enter, both enter
        if (instance == nullptr) 
        {  // First check (no locking) and now lock allows both
            lock_guard<mutex> lock(mtx);  // Lock only if needed
            //two thread enter
            if (instance == nullptr) 
            //only one enter now...
            {  // Second check (after acquiring lock)
                instance = new Singleton();
            }
        }
        return instance;
    }
};
 
// Initialize static members
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout << (s1 == s2) << endl;
}