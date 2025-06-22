#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// Base interface for files and folders
class FileSystemItem
{
    public:
    virtual ~FileSystemItem() {}
    virtual void ls(int indent = 0) = 0; //adds space      
    virtual void openAll(int indent = 0) = 0;    //open all file   
    virtual int getSize() = 0;//size of each file
    virtual FileSystemItem* cd(const string& name) = 0; 
    virtual string getName() = 0;
    virtual bool isFolder() = 0;
};

// Leaf: File
class File : public FileSystemItem
{
    string name;
    int size;

    public:
    File(const string& n, int s)
    {
        name = n;
        size = s;
    }

    void ls(int indent = 0) override 
    {
        cout << string(indent, ' ') << name << "\n";
    }

    void openAll(int indent = 0) override
    {
        cout << string(indent, ' ') << name << "\n";
    }

    int getSize() override
    {
        return size;
    }
//since file is end point so, nullptr to folder...
    FileSystemItem* cd(const string&) override
    {
        return nullptr;
    }

    string getName() override
    {
        return name;
    }

    //false for the folder since no folder is there.
    bool isFolder() override
    {
        return false;
    }
};

class Folder : public FileSystemItem
{
    string name;
    vector<FileSystemItem*> children;

    public:
    Folder(const string& n)
    {
        name = n;
    }

    ~Folder()
    {
        for (auto c : children) delete c;
    }

    void add(FileSystemItem* item)
    {
        children.push_back(item);
    }

    void ls(int indent = 0) override
    {
        for (auto child : children)
        {
            if (child->isFolder())
            {
                cout <<string(indent, ' ') << "+ " << child->getName() << "\n";
            }
            
            else
            {
                cout <<string(indent, ' ') <<child->getName() << "\n";
            }
        }
    }

    void openAll(int indent = 0) override 
    {
        cout << string(indent, ' ') << "+ " << name << "\n";
        for (auto child : children)
        {
            child->openAll(indent + 4);
        }
    }

    int getSize() override 
    {
        int total = 0;
        for (auto child : children)
        {
            total += child->getSize();
        }
        return total;
    }

    FileSystemItem* cd(const string& target) override
    {
        for (auto child : children)
        {
            if (child->isFolder() && child->getName() == target)
            {
                return child;
            }
        }
        // not found or not a folder
        return nullptr;
    }

    string getName() override 
    {
        return name;
    }
    bool isFolder() override 
    {
        return true;
    }
};

int main()
{
    // Build file system
    Folder* root = new Folder("root");
    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 4));
    root->add(new File("file3.txt", 3));
    root->add(new File("file4.txt", 6));
    root->add(new File("file5.txt", 2));
    root->add(new File("file6.txt", 8));



    Folder* docs = new Folder("docs");
    docs->add(new File("resume.pdf", 125));
    docs->add(new File("notes.txt", 12));
    docs->add(new File("imp.docs", 14));
    docs->add(new File("gate.pdf", 17));
    docs->add(new File("intern.pdf", 21));
    root->add(docs);

    Folder* images = new Folder("images");
    images->add(new File("photo1.jpg", 2));
    images->add(new File("photo2.jpg", 4));
    images->add(new File("photo3.jpg", 6));
    images->add(new File("photo4.jpg", 8));
    root->add(images);

    cout<<"-----------------------------------------------------"<<endl;

    cout<<"Structure Of entire root folder is "<<endl;
    root->openAll();

    cout<<"-----------------------------------------------------"<<endl;

    cout<<"List of entire files in root  is "<<endl;
    root->ls();

    cout<<"-----------------------------------------------------"<<endl;

    cout<<"list of  entire files in images is  "<<endl;
    images->ls();


    cout<<"-----------------------------------------------------"<<endl;

    cout<<"list of entire files in docs  is "<<endl;
    docs->ls();

    cout<<"-----------------------------------------------------"<<endl;
    
    cout<<"list of entire files in docs is "<<endl;
    FileSystemItem* cwd = root->cd("docs");
    if (cwd != nullptr)
    {
        cwd->ls();
    } 
    
    else
    {
        cout << "\n Could not cd into docs \n";
    }

    cout<<"-----------------------------------------------------"<<endl;
    
    
    cout<<"Total Size of the entire root directory is "<<root->getSize()<<endl;


    cout<<"-----------------------------------------------------"<<endl;

    // Cleanup for heap allocation
    delete docs;
    delete images;
    delete root;
    return 0;
}