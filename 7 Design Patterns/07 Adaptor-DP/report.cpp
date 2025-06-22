#include <iostream>
#include <string>
using namespace std;

// 1. Target interface expected by the client
class IReports
{
    public:
    // now takes the raw data string and returns JSON
    virtual string getJsonData(const string& data) = 0;
    virtual ~IReports() {}
};
// 2. Adaptee: provides XML data from a raw input or simply it is 3rd party
class XmlDataProvider
{
    public:
    // Expect data in "name:id" format (e.g. "Alice:42")
    string getXmlData(const string& data)
    {
        size_t sep1 = data.find(':');
        size_t sep2 = data.find(':', sep1 + 1);

        string name = data.substr(0, sep1);
        string id = data.substr(sep1 + 1, sep2 - sep1 - 1);
        string salary = data.substr(sep2 + 1);

        return "<user>"
            "<name>" + name + "</name>"
            "<id>" + id + "</id>"
            "<salary>" + salary + "</salary>"
            "</user>";
    }
};
// 3. Adapter: implements IReports by converting XML → JSON.
class XmlDataProviderAdapter : public IReports
{
    private:
    XmlDataProvider* xmlProvider;
    
    public:
    XmlDataProviderAdapter(XmlDataProvider* provider)
    {
        this->xmlProvider = provider;
    }

    string getJsonData(const string& data) override
    {
        string xml = xmlProvider->getXmlData(data);

        size_t startName = xml.find("<name>") + 6;
        size_t endName = xml.find("</name>");
        string name = xml.substr(startName, endName - startName);

        size_t startId = xml.find("<id>") + 4;
        size_t endId = xml.find("</id>");
        string id = xml.substr(startId, endId - startId);

        size_t startSalary = xml.find("<salary>") + 8;
        size_t endSalary = xml.find("</salary>");
        string salary = xml.substr(startSalary, endSalary - startSalary);

        return "{\"name\":\"" + name + "\", \"id\":" + id + ", \"salary\":" + salary + "}";
    }
};

// 4. Client code works only with IReports
class Client
{
    public:
    void getReport(IReports* report, string rawData)
    {
        cout << "Processed JSON: "
        << report->getJsonData(rawData)
        << endl;
    }
};
int main()
{
    string name, id, salary;
    cout << "Enter First Name: "<<endl;
    cin >> name;
    cout << "Enter ID: "<<endl;; 
    cin >> id;
    cout << "Enter Salary: "<<endl;
    cin >> salary;
    // Combine the data in "name:id:salary" format
    string rawData = name + ":" + id + ":" + salary;

    XmlDataProvider* xmlProv = new XmlDataProvider();
    IReports* adapter = new XmlDataProviderAdapter(xmlProv);

    Client* client = new Client();
    client->getReport(adapter, rawData);
    // → Processed JSON: {"name":"Alice", "id":42, "salary":50000}

    delete adapter;
    delete xmlProv;
    delete client;
    return 0;
}
