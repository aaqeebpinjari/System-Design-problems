#include<iostream>
#include<string>
using namespace std;

class Person
{
    protected:
    string name;
    int Age;

    public:

    Person(){};
    Person(string n, int age)
    {
        name =n;
        Age =age;
    }

    virtual void displaydetail() = 0;
    virtual ~Person(){};// destructor for base class,then automatically, derived class destructors are called
};

class Employee: public Person
{
    protected:
    int salary;

    public:

    Employee(){

    };

    Employee(string n,int age, int s):Person(n,age), salary(s) {}

    //overiding abstract function..
    void displaydetail(){
        cout<<"Employee name "<<name<<endl;
        cout<<"Employee Age "<<Age<<endl;
        cout<<"Employee Salary "<<salary<<endl;
    }
};

class Manager: public Employee
{
    protected:
    string Department;

    public:
    Manager(string n, int age, int s, string department):Employee(n,age,s), Department(department){}

    void displaydetail(){
        cout<<"Manager name "<<name<<endl;
        cout<<"Manager Age "<<Age<<endl;
        cout<<"Manager Salary "<<salary<<endl;
        cout<<"Manager Department "<<Department<<endl;

    }
};

int main()
{
    Person* p= new Manager("sani",26,60000,"SDE");
    p->displaydetail();
    cout<<"---------------------------------------------------"<<endl;
    delete p; // good practice

    p= new Employee("Ali",28, 90000);
    
    p->displaydetail();
    cout<<"---------------------------------------------------"<<endl;

    delete p; //free the allocated memory..
    
    return 0;
}