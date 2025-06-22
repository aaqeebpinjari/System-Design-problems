#include <iostream>
using namespace std;

// 1. Template - Abstract Class
class OrderProcess {
public:
    // Template Method (fixed sequence)
    void processOrder() {
        selectItem();
        makePayment();
        deliverItem();
        if (customerWantsFeedback())
        {
            giveFeedback();
        }
    }

    // Fixed step with default implementation
    void selectItem() {
        cout << "Item selected by customer\n";
    }

    // Steps to be defined by subclass
    virtual void makePayment() = 0;
    virtual void deliverItem() = 0;

    // Hook method (optional override)
    virtual bool customerWantsFeedback() {
        return true; // default behavior
    }

    virtual void giveFeedback() {
        cout << "Collecting customer feedback...\n";
    }

    virtual ~OrderProcess() {}
};

// 2. Concrete Class: Pizza Order
class PizzaOrder : public OrderProcess {
    void makePayment() override {
        cout << "Payment made using Credit Card for Pizza\n";
    }

    void deliverItem() override {
        cout << "Pizza delivered to customer in 30 minutes\n";
    }

    bool customerWantsFeedback() override {
        return true; // Pizza order always asks for feedback
    }
};

// 3. Concrete Class: Book Order
class BookOrder : public OrderProcess {
    void makePayment() override {
        cout << "Payment made using Net Banking for Book\n";
    }

    void deliverItem() override {
        cout << "Book shipped via courier service\n";
    }

    bool customerWantsFeedback() override {
        return false; // Books don't require feedback in our case
    }
};

// 4. Client
int main() {
    cout << "Processing Pizza Order:\n";
    OrderProcess* order1 = new PizzaOrder();
    order1->processOrder();

    cout << "\nProcessing Book Order:\n";
    OrderProcess* order2 = new BookOrder();
    order2->processOrder();

    delete order1;
    delete order2;

    return 0;
}
