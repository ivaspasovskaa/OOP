//
// Created by ivasp on 4/11/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class WebPage{
private:
    char url[100];
    char *content;
public:
    WebPage(char url[100]="",char *content=""){
        strcpy(this->url,url);
        this->content=new char [strlen(content)+1];
        strcpy(this->content,content);
    }
    WebPage(const WebPage & w){
        strcpy(this->url,w.url);
        this->content=new char [strlen(w.content)+1];
        strcpy(this->content,w.content);
    }
    ~WebPage(){
        delete [] content;
    }

    char *getURL(){
        return url;
    }

    char *getContent(){
        return content;
    }

    bool equals(WebPage & w){
        return strcmp(url,w.url)==0;
    }
};

class WebServer{
private:
    char name[30];
    WebPage *pages;
    int n;

    void copy(const WebServer & w){
        strcpy(this->name,w.name);
        this->n=w.n;
        this->pages=new WebPage [this->n];
        for(int i=0;i<this->n;i++){
            this->pages[i]=w.pages[i];
        }
    }
public:
    WebServer(char name[30]=""){
        strcpy(this->name,name);
        this->n=0;
        this->pages=new WebPage [this->n];
    }

    WebServer(const WebServer & w){
        copy(w);
    }

    WebServer & operator=(const WebServer & w){
        if(this!=&w){
            delete [] pages;
            copy(w);
        }
        return *this;
    }

    ~WebServer(){
        delete [] pages;
    }

    void addPage(WebPage wp){
        for(int i=0;i<n;i++){
           if(pages[i].equals(wp)){
               return;
           }
        }

        WebPage *tmp=new WebPage[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=pages[i];
        }
        tmp[n++]=wp;
        delete [] pages;
        pages=tmp;
    }

    void deletePage(WebPage & wp){
        int ind=-1;
        for(int i=0;i<n;i++){
            if(pages[i].equals(wp)){
                ind=i;
                break;
            }
        }

        if(ind!=-1){
            WebPage *tmp=new WebPage[n-1];
            int j=0;
            for(int i=0;i<n;i++){
                if(i!=ind){
                    tmp[j++]=pages[i];
                }
            }
            n=j;
            delete [] pages;
            pages=tmp;
        }
    }

    void listPages(){
        cout<<"Number: "<<n<<endl;
        for(int i=0;i<n;i++){
            cout<<pages[i].getURL()<<" "<<pages[i].getContent()<<endl;
        }
    }
};

int main(){
    WebPage wp1 ("http://www.google.com", "The search engine");
    WebPage wp2 ("http://www.finki.ukim.mk", "FINKI");
    WebPage wp3 ("http://www.time.mk", "Site vesti");

    WebServer ws(" Server ");

    ws.addPage(wp1) ;
    ws.addPage(wp2);
    ws.addPage(wp3) ;

    ws.listPages ();

    cout << "\nAfter delete: \n";
    ws.deletePage(wp3);

    ws.listPages ();
    return 0;
}