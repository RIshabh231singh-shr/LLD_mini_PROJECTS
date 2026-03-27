#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class DocumentEditor{
    private :
    vector<string>documentElements;
    string renderedDocument;
    public:
    //implementing Add text 
    void addText(string text){
        documentElements.push_back(text);
    }

    //implementing AddImage
    void addImage(string path){
        documentElements.push_back(path);
    }

    //implementing rendering of Document
    string renderDocument(){
        if(renderedDocument.empty()){
            string result;
            for(auto element : documentElements){
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" ||
                 element.substr(element.size() - 4) == ".png")) {
                    result += "[Image: " + element + "]" + "\n";
                } else {
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    //implementing save to file

    void saveToFile(){
        DocumentEditor Editor;
        ofstream file("document.txt");
        if(file.is_open()){
            file<<renderDocument();
            file.close();
            cout<<"Document is save in document.txt";
        }
        else{
            cout<<"Unable to open document.txt";
        }
    }
};


    int main(){
        DocumentEditor editor;
        editor.addText("Hello World");
        editor.addText("This is a document editor.");
        cout << editor.renderDocument() << endl;
        editor.saveToFile();
        return 0;
    }

