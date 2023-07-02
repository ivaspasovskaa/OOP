//
// Created by ivasp on 4/10/2023.
//
#include<iostream>
#include<cstring>
using namespace std;

enum Extension{txt,pdf,exe};

class File{
private:
    char *imeDatoteka;
    Extension tip;
    char *imeSopstvenik;
    int golemina;

    void copy(const File & f){
        this->imeDatoteka=new char [strlen(f.imeDatoteka)+1];
        strcpy(this->imeDatoteka,f.imeDatoteka);
        this->tip=f.tip;
        this->imeSopstvenik=new char [strlen(f.imeSopstvenik)+1];
        strcpy(this->imeSopstvenik,f.imeSopstvenik);
        this->golemina=f.golemina;
    }
public:
    //File(){}
    File(char *imeDatoteka="",char *imeSopstvenik="", int golemina=0, Extension tip=txt){
        this->imeDatoteka=new char [strlen(imeDatoteka)+1];
        strcpy(this->imeDatoteka,imeDatoteka);
        this->tip=tip;
        this->imeSopstvenik=new char [strlen(imeSopstvenik)+1];
        strcpy(this->imeSopstvenik,imeSopstvenik);
        this->golemina=golemina;
    }
    File(const File & f){
        copy(f);
    }
    File & operator=(const File & f){
        if(this!=&f){
            delete [] imeDatoteka;
            delete [] imeSopstvenik;
            copy(f);
        }
    }
    ~File(){
        delete [] imeDatoteka;
        delete [] imeSopstvenik;
    }

    void print(){
        cout<<"File name: "<<imeDatoteka;
        switch (tip) {
            case 1:
                cout<<".txt"<<endl; break;
            case 2:
                cout<<".exe"<<endl; break;
            default:
                cout<<".pdf"<<endl; break;
        }
        cout<<"File owner: "<<imeSopstvenik<<endl;
        cout<<"File size: "<<golemina<<endl;
    }

    bool equals(const File & f){
        return (strcmp(imeDatoteka,f.imeDatoteka)==0 && strcmp(imeSopstvenik,f.imeSopstvenik)==0 && tip==f.tip);
    }

    bool equalsType(const File & that){
        return (strcmp(imeDatoteka,that.imeDatoteka)==0 && tip==that.tip);
    }
};

class Folder{
private:
    char *ime;
    int n;
    File *files;

    void copy(const Folder & f){
        this->ime=new char [strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->n=f.n;
        this->files=new File [this->n];
        for(int i=0;i<this->n;i++){
            this->files[i]=f.files[i];
        }
    }

public:
    Folder(char *ime=""){
        this->ime=new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->n=0;
        this->files=new File [this->n];
    }
    Folder(const Folder & f){
        copy(f);
    }
    Folder & operator=(const Folder & f){
        if(this!=&f){
            delete [] ime;
            delete [] files;
            copy(f);
        }
        return *this;
    }
    ~Folder(){
        delete [] ime;
        delete [] files;
    }

    void print(){
        cout<<"Folder name: "<<this->ime<<endl;
        for(int i=0;i<n;i++){
            files[i].print();
        }
    }

    void remove(const File & f){
        int j=0;
        File *tmp=new File [n-1];
        for(int i=0;i<n;i++){
            if(!files[i].equals(f)){
                tmp[j++]=files[i];
            }
        }
        n=j;
        delete [] files;
        files=tmp;
    }

    void add(const File & f){
        File *tmp=new File [n+1];
        for(int i=0;i<n;i++){
            tmp[i]=files[i];
        }
        tmp[n++]=f;
        delete [] files;
        files=tmp;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}