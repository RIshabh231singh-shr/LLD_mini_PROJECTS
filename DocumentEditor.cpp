#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;


class documentElement{
    public :
    virtual string render() = 0;
};

class textElement : public documentElement{
    private:
    string text;
    public: 
    //text client se lena hai na
    //constructor bna kr 
    textElement(string text){
        this->text = text;
    }
    string render() override{
        return text;
    }
};

class imageElement : public documentElement{
    private : 
    string imagePath;

    public :
    imageElement(string imagePath){
        this->imagePath = imagePath;
    }

    string render() override{
        return "[Image: " + imagePath + "]";
    }
};

class newLineElement : public documentElement{
    public : 
    string render() override{
        return "\n";
    }
};

class tabElement : public documentElement{
    public :
    string render() override{
        return "\t";
    }
};

//making a virtual persistance class to save 
class persistence{
    public : 
    virtual void save(string data) = 0;
};

class fileStorage : public persistence{
    public :

    void save(string data) override{
        ofstream outFile("document.txt");
        if (outFile) {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

class MongoStorage : public persistence{
    public:
    void save(string) override{
        cout<<"Saved to MongoDB";
    }
};


//ye document hai jo documentElements ke help se render ko call krega
class document{
    private:
    vector <documentElement*> documentElements;
    public:
    //adding or initializing element sin documentElements
    void addDocumentElements(documentElement* element){
        documentElements.push_back(element);
    }

    string render(){
        string result;
        for(auto element : documentElements){
            result = result + element->render();
        }
        return result;
    }

};

class documentEditor{
    private:
    document* docs;
    persistence* storage;
    string renderedDocument;

    public:
    //ye constructor bna rhe hai initialize krne ke liye 
    documentEditor(document* docs,persistence* storage){
        this->docs = docs;
        this->storage = storage;
    }

    //Making function for adding text
    void addText(string text){
        docs->addDocumentElements(new textElement(text));
    }

    void addImage(string path){
        docs->addDocumentElements(new imageElement(path));
    }
    
    void addnewLine(){
        docs->addDocumentElements(new newLineElement());
    }

    void addTabSpace(){
        docs->addDocumentElements(new tabElement());
    }

    string renderDocument(){
        if(renderedDocument.empty()) {
            renderedDocument = docs->render();
        }
        return renderedDocument ;
    }

    void savedocument(){
        storage->save(renderDocument());
    }
};


int main(){
    document* docs = new document();

    persistence* storage = new fileStorage();
   documentEditor* editor = new documentEditor(docs, storage);

    // Simulate a client using the editor with common text formatting features.
    editor->addText("Hello, world!");
    editor->addnewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addnewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addnewLine();

    // Render and display the final document.
    cout << editor->renderDocument() << endl;

    editor->savedocument();

    return 0;
}