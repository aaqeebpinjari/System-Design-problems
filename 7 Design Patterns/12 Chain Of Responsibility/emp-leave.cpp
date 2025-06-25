#include <iostream>
#include <string>
using namespace std;

// Request Class
class LeaveRequest
{
    public:
    string employeeName;
    int leaveDays;

    LeaveRequest(string name, int days) : employeeName(name), leaveDays(days) {}
};

// Handler Interface
class Approver
{
    protected:
    Approver* nextApprover;

    public:
    void setNext(Approver* next)
    {
        nextApprover = next;
    }

    virtual void processRequest(LeaveRequest request) = 0;
    virtual ~Approver() = default;
};

// Concrete Handler 1: Team Lead
class TeamLead : public Approver
{
    public:
    void processRequest(LeaveRequest request) override 
    {
        if (request.leaveDays <= 2) {
            cout << "[Team Lead] Approved " << request.leaveDays << " day(s) leave for " << request.employeeName << endl;
        } else if (nextApprover != nullptr) {
            nextApprover->processRequest(request);
        } else {
            cout << "[Team Lead] Cannot handle the request. No further approver.\n";
        }
    }
};
// Concrete Handler 2: Manager
class Manager : public Approver
{
    public:
    void processRequest(LeaveRequest request) override 
    {
        if (request.leaveDays <= 5) {
            cout << "[Manager] Approved " << request.leaveDays << " day(s) leave for " << request.employeeName << endl;
        } else if (nextApprover != nullptr) {
            nextApprover->processRequest(request);
        } else {
            cout << "[Manager] Cannot handle the request. No further approver.\n";
        }
    }
};
// Concrete Handler 3: Director
class Director : public Approver
{
    public:
    void processRequest(LeaveRequest request) override {
        if (request.leaveDays <= 10) {
            cout << "[Director] Approved " << request.leaveDays << " day(s) leave for " << request.employeeName << endl;
        } else {
            cout << "[Director] Rejected leave for " << request.employeeName << ". Exceeds approval limit.\n";
        }
    }
};
// Main
int main() 
{
    // Create approvers
    Approver* teamLead = new TeamLead();
    Approver* manager = new Manager();
    Approver* director = new Director();

    // Chain the handlers
    teamLead->setNext(manager);
    manager->setNext(director);

    // Example leave requests
    LeaveRequest r1("Alice", 1);
    LeaveRequest r2("Bob", 4);
    LeaveRequest r3("Charlie", 8);
    LeaveRequest r4("Dave", 15);

    // Process requests
    teamLead->processRequest(r1);
    teamLead->processRequest(r2);
    teamLead->processRequest(r3);
    teamLead->processRequest(r4);

    // Clean up
    delete teamLead;
    delete manager;
    delete director;

    return 0;
}
