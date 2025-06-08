#include<iostream>
#include<vector>
#include<string>
using namespace std;

//Product items in the list
class Product{

    public:
    string name;
    double price;

    Product(string n, double amt){
        name = n;
        price = amt;
    }
};

//Shopping cart only related to business logic, can consist of more than one function
// kaam ek he kerna usne yaad rakh..

class shoppingCart{
    private:

    vector<Product*>products;//heap allocated prod list

    public:
    void addProducts(Product* p){
        products.push_back(p);
    }

    const vector<Product*> &getProducts()
    {
        return products;
    }

    //Calculates total price in cart.
    double calculateTotal()
    {
        double total = 0;
        for (auto p : products) {
            total += p->price;
        }
        return total;
    }
};

//another class for printing invoice
class shoppingCartPrinter{
    private:
    shoppingCart* cart;

    public:
    shoppingCartPrinter(shoppingCart* cart){
        this->cart = cart;
    }

    void printInvoice()
    {
        cout<<"--------------------------------------"<<endl;

        //get products for storing result and
        // looping for all 
        for(auto x: cart->getProducts())
        {
            cout << x->name << " - Rs " << x->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotal() << endl;
    }
};

//3. seperate class for saving to database
class ShoppingCartStorage{
    private:
    shoppingCart* cart;

    public:
    ShoppingCartStorage(shoppingCart* cart){
        this->cart= cart;
    }

     void saveToDatabase() {
        cout << "Saving shopping cart to database..." << endl;
        cout << "Saved to Database..."<<endl;
    }
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

    shoppingCartPrinter* printer = new shoppingCartPrinter(cart);
    printer->printInvoice();
    cout<<"------------------------------"<<endl;

    delete printer;

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToDatabase();
    cout<<"------------------------------"<<endl;

    delete db;

    delete cart;
    return 0;
}
