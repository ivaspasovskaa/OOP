//
// Created by ivasp on 6/4/2023.
//
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Image{
protected:
    char *name;
    char username[51];
    int w,h;

    void copy(const Image & i){
        this->name=new char [strlen(i.name)+1];
        strcpy(this->name,i.name);
        strcpy(this->username,i.username);
        this->w=i.w;
        this->h=i.h;
    }

public:
    Image(char *name="untitled",char *username="unknown",int w=800,int h=800){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->username,username);
        this->w=w;
        this->h=h;
    }

    Image(const Image & i){
        copy(i);
    }

    ~Image(){
        delete [] name;
    }

    virtual int fileSize() const{
        return w*h*3;
    }

    friend ostream & operator<<(ostream & out,const Image & i){
        return out<<i.name<<" "<<i.username<<" "<<i.fileSize()<<endl;
    }

    bool operator>(Image & i){
        return fileSize()>i.fileSize();
    }
};

class TransparentImage : public Image{
private:
    bool tl;

public:
    TransparentImage(char *name="untitled",char *username="unknown",int w=800,int h=800,bool tl=true)
    : Image(name,username,w,h){
        this->tl=tl;
    }

    int fileSize() const{
        if(tl){
            return w*h*4;
        }else{
            return w*h+w*h/8;
        }
    }

    friend ostream & operator<<(ostream & out,const TransparentImage & i){
        return out<<i.name<<" "<<i.username<<" "<<i.fileSize()<<endl;
    }

    bool operator>(TransparentImage & i){
        return fileSize()>i.fileSize();
    }
};

class Folder{
private:
    char name[255];
    char user_name[51];
    Image *images[100];
    int n;

public:
    Folder(char *name="untitled", char *username="unknown"){
        strcpy(this->name,name);
        strcpy(this->user_name,username);
        this->n=0;
    }

    int folderSize() const{
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=images[i]->fileSize();
        }
        return sum;
    }

    Image *getMaxFile(){
        Image *max=images[0];
        for(int i=1;i<n;i++){
            if(*images[i]>*max){
                max=images[i];
            }
        }
        return max;
    }

    Folder & operator+=(Image & im){
        TransparentImage *t=dynamic_cast<TransparentImage *>(&im);
        if(t){
            images[n++]=new TransparentImage(*t);
        }else{
            images[n++]=new Image(im);
        }
        return *this;
    }

    friend ostream & operator<<(ostream & out,const Folder & f){
        out<<f.name<<" "<<f.user_name<<endl<<"--"<<endl;
        for(int i=0;i<f.n;i++){
            TransparentImage *t=dynamic_cast<TransparentImage *>(f.images[i]);
            if(t){
                out<<*t;
            }else{
                out<<*f.images[i];
            }
        }
        out<<"--"<<endl<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }

    Image * operator[](int i){
        if(i>=0 && i<n){
            return images[i];
        }else{
            return NULL;
        }
    }
};

Folder max_folder_size(Folder *f,int n){
    Folder max=f[0];
    for(int i=1;i<n;i++){
        if(max.folderSize()<f[i].folderSize()){
            max=f[i];
        }
    }
    return max;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};