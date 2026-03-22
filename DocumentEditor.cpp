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
        this->
    }

};


int main(){

}