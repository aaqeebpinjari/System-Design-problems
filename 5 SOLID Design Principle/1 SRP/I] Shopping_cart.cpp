#include<iostream>
#include<string>
#include<vector>
using namespace std;

//Product class for particular Ecommerse website
class Product{
    public:
    string name;
    double price;

    Product(string name, double amt){
        this->name = name;
        this->price = amt;
    }
    
    
    ~Product(){};
};

//Voilating cond for SRP: single class can only do one thing

class shoppingCart{
    private:
    vector<Product*>products;

    public:
    void addProducts(Product *p){
        products.push_back(p);
    }

    const vector<Product*> &getProducts()
    { 
        return products;
    } 

    //till here, all good, because we SRP is maintain here

    // 1. Calculates total price in cart.
    double calculateTotal() 
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }
        return total;
        cout<<"---------------------------------------------------------"<<endl;
    }

    // 2. Violating SRP - Prints invoice (Should be in a separate class)
    void printInvoice()
    {
        cout<<"---------------------------------------------------------"<<endl;
        cout << "Shopping Cart Invoice:\n";
        for (auto p : products)
        {
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << calculateTotal() << endl;
        
        cout<<"---------------------------------------------------------"<<endl;
    }

    // 3. Violating SRP - Saves to DB (Should be in a separate class)
    void saveToDatabase()
    {
        cout << "Saving shopping cart to database..." << endl;

        cout<<"Saved to Database..."<<endl;

        cout<<"---------------------------------------------------------"<<endl;
    }

    ~shoppingCart(){};
};

int main() {
    shoppingCart* cart = new shoppingCart();

    cart->addProducts (new Product("Laptop", 50000));
    cart->addProducts (new Product("Mouse", 2000));
    cart->addProducts (new Product("Printer", 12000));
    cart->addProducts (new Product("keyboard", 2000));
    cart->addProducts (new Product("RAM", 10000));
    cart->addProducts (new Product("pendrive", 2000));
    cart->addProducts (new Product("other", 5000));

    cart->printInvoice();  
    cart->saveToDatabase();

    delete cart;
    return 0;
}