#include <iostream>
#include <memory>
using namespace std;


/*Instead of keeping all together in one class and overriding it, we created a seprate class for each and calling each as per requirement
nd if all in one class and calling sperately, will break LSP principle...*/

// Interfaces
class IPrinter {
public:
    virtual void print() = 0;
    virtual ~IPrinter() = default;
};

class IScanner {
public:
    virtual void scan() = 0;
    virtual ~IScanner() = default;
};

class IFax {
public:
    virtual void fax() = 0;
    virtual ~IFax() = default;
};

// Concrete classes
class BasicPrinter : public IPrinter {
public:
    void print() override {
        cout << "BasicPrinter: Printing document..." << endl;
        cout << "Document Printed..." << endl;
    }
};

class Scanner : public IScanner {
public:
    void scan() override {
        cout << "Scanner: Scanning document..." << endl;
         cout << "Document Scanned ..." << endl;
    }
};

class FaxMachine : public IFax {
public:
    void fax() override {
        cout << "FaxMachine: Faxing document..." << endl;
        cout<<"Document Fax..."<<endl;
    }
};

class MultiFunctionMachine : public IPrinter, public IScanner, public IFax 
{
    public:
    void print() override {
        cout << "MFM: Printing document..." << endl;
        cout << "Document Printed..." << endl;
    }
    void scan() override {
        cout << "MFM: Scanning document..." << endl;
        cout << "Document Scanned..." << endl;
    }
    void fax() override {
        cout << "MFM: Faxing document..." << endl;
        cout << "Document Faxed..." << endl;
    }
};

int main() {
    int choice;

    cout << "Choose device type:\n";
    cout << "1. Basic Printer\n";
    cout << "2. Scanner\n";
    cout << "3. Fax Machine\n";
    cout << "4. MultiFunction Machine\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            unique_ptr<IPrinter> printer = make_unique<BasicPrinter>();
            printer->print();
            break;
        }
        case 2: {
            unique_ptr<IScanner> scanner = make_unique<Scanner>();
            scanner->scan();
            break;
        }
        case 3: {
            unique_ptr<IFax> fax = make_unique<FaxMachine>();
            fax->fax();
            break;
        }
        case 4: {
            MultiFunctionMachine mfm;
            int subChoice;
            cout << "\nMultiFunction Options:\n";
            cout << "1. Print\n";
            cout << "2. Scan\n";
            cout << "3. Fax\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            switch (subChoice) {
                case 1: mfm.print(); break;
                case 2: mfm.scan(); break;
                case 3: mfm.fax(); break;
                default: cout << "Invalid option.\n"; break;
            }
            break;
        }
        default:
            cout << "Invalid device type selected." << endl;
    }

    return 0;
}
