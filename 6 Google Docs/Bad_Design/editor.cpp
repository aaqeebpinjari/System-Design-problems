#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//within same class we will put all functions as design in the figure
//violating SOLID design principles..

class DocumentEditor
{
private:
    vector<string> documentElements;
    string renderedDocument;

public:
    // Adds text as a plain string
    void addText(string text)
    {
        documentElements.push_back(text);
    }

    // Adds an image represented by its file path
    void addImage(string imagePath)
    {
        documentElements.push_back(imagePath);
    }

    // Renders the document by checking the type of each element at runtime
    ///varies as per business logic, so we have made it as per our requiremnt
    string renderDocument()
    {
        if(renderedDocument.empty())
        {
            string result;
            for (auto element : documentElements) 
            {
                //checking the input given by the user is image(checking end of the file, jpg/png) 
                //then, that image is saved and 
                // and element as path is saved in result...
                if (element.size() > 4 and
                (element.substr(element.size() - 4) == ".jpg" ||
                 element.substr(element.size() - 4) == ".png")) 
                {
                    result += "[Image: " + element + "]" + "\n";
                } 
                //if its text then store that in result
                else
                {
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    void saveToFile() 
    {
        ofstream file("document.txt");
        if (file.is_open())//open the file
        {
            file << renderDocument();// made changes
            file.close();//close it
            cout << "Document saved to document.txt" << endl;
        }
        
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

int main() {
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("welcome_to_editor.jpg");
    editor.addText("This is a document editor.");

    cout << editor.renderDocument() << endl;

    editor.saveToFile();
    
    return 0;
}