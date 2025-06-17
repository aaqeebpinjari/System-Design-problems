#include <iostream>
#include <vector>
#include <string>
#include<fstream>
using namespace std;

//In this, we have a layer of abstraction for supporting new features
//acting as an interface.
// Abstraction for document elements
class DocumentElement 
{
    public:
    virtual string render() = 0; //pure method, knows about how to render
    //will be called by other concrete class such as textelemt, bold,
    //space,italic and so on.
};

// Concrete implementation for text elements
class TextElement : public DocumentElement
{
    private:
    string text;
    
    public:
    TextElement(string text)
    {
        this->text = text;
    }

    string render() override
    {
        return text;
    }
};

// Concrete implementation for image elements
class ImageElement : public DocumentElement
{
    private:
    string imagePath;
    
    public:
    ImageElement(string imagePath)
    {
        this->imagePath = imagePath;
    }

    string render() override
    {
        return "[Image: " + imagePath + "]";
    }
};

// NewLineElement represents a line break in the document.
class NewLineElement : public DocumentElement
{
    public:
    string render() override
    {
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document.
class TabSpaceElement : public DocumentElement
{
    public:
    string render() override
    {
        return "\t";
    }
};

// Document class responsible for holding a collection of elements
class Document
{
    private:
    vector<DocumentElement*> documentElements;
    
    public:
    void addElement(DocumentElement* element)
    {
        documentElements.push_back(element);
    }

    // Renders the document by concatenating the render output of 
    //all elements.
    string render()
    {
        string result;
        for (auto element : documentElements)
        {
            result += element->render();
        }
        return result;
    }
};

// Persistence abstraction for having multiple options for
//saving into to db either by sql, mongo so on.
class Persistence {
public:
    virtual void save(string data) = 0;
};

// FileStorage implementation of Persistence
class FileStorage : public Persistence
{
    public:
    void save(string data) override
    {
        ofstream outFile("document.txt");
        if (outFile) 
        {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else 
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// Placeholder DBStorage implementation
class DBStorage : public Persistence
{
    public:
    void save(string data) override
    {
        // Save to DB
    }
};

// DocumentEditor class managing client interactions
class DocumentEditor {
private:
    Document* document;
    Persistence* storage;
    string renderedDocument;

public:
    DocumentEditor(Document* document, Persistence* storage) {
        this->document = document;
        this->storage = storage;
    }

    void addText(string text) {
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath) {
        document->addElement(new ImageElement(imagePath));
    }

    // Adds a new line to the document.
    void addNewLine() {
        document->addElement(new NewLineElement());
    }

    // Adds a tab space to the document.
    void addTabSpace()
    {
        document->addElement(new TabSpaceElement());
    }

    string renderDocument()
    {
        if(renderedDocument.empty())
        {
            return document->render();
        }
        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
};

// Client usage example, modified by me...
int main()
{
    Document* document = new Document();
    Persistence* persistence = new FileStorage();
    DocumentEditor* editor = new DocumentEditor(document, persistence);

    int choice;
    string input;

    do {
        cout << "\n--- Document Editor Menu ---\n";
        cout << "1. Add Text\n";
        cout << "2. Add New Line\n";
        cout << "3. Add Tab Space\n";
        cout << "4. Add Image\n";
        cout << "5. Render Document\n";
        cout << "6. Save Document\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        switch (choice)
        {
            case 1:
                cout << "Enter text to add: ";
                getline(cin, input);
                editor->addText(input);
                cout << "text Added. \n";
                break;
            case 2:
                editor->addNewLine();
                cout << "New line added.\n";
                break;
            case 3:
                editor->addTabSpace();
                cout << "Tab space added.\n";
                break;
            case 4:
                cout << "Enter image path: ";
                getline(cin, input);
                editor->addImage(input);
                cout << input<< ", added.\n";
                break;
            case 5:
                cout << "\n--- Rendered Document ---\n";
                cout << editor->renderDocument() << endl;
                break;
            case 6:
                editor->saveDocument();
                cout << "Document saved, check the document in the folder !.\n";
                break;
            case 0:
                cout << "Exiting Document Editor.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    delete editor;
    delete persistence;
    delete document;

    return 0;
}
