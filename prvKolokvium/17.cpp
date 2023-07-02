//
// Created by ivasp on 4/10/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

enum Tip{LINUX,UNIX,WINDOWS};

class OperativenSistem{
private:
    char *ime;
    float verzija;
    Tip t;
    float golemina;

    void copy(const OperativenSistem & o){
        this->ime=new char [strlen(o.ime)+1];
        strcpy(this->ime,o.ime);
        this->verzija=o.verzija;
        this->t=o.t;
        this->golemina=o.golemina;
    }

public:
    OperativenSistem(char *ime="",float verzija=0.0,Tip t=LINUX,float golemina=0.0){
        this->ime=new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->t=t;
        this->golemina=golemina;
    }

    OperativenSistem(const OperativenSistem & o){
        copy(o);
    }

    OperativenSistem & operator=(const OperativenSistem & o){
        if(this!=&o){
            delete [] ime;
            copy(o);
        }
        return *this;
    }

    ~OperativenSistem(){
        delete [] ime;
    }

    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<t<<" Golemina:"<<golemina<<"GB"<<endl;
    }

    bool ednakviSe(const OperativenSistem &os){
        return strcmp(this->ime,os.ime)==0 && this->golemina==os.golemina && this->t==os.t && this->verzija==os.verzija;
    }

    int sporediVerzija(const OperativenSistem &os){
        if(this->verzija==os.verzija){
            return 0;
        }else if(this->verzija<os.verzija){
            return -1;
        }else
            return 1;
    }

    bool istaFamilija(const OperativenSistem &sporedba){
        return (strcmp(this->ime,sporedba.ime)==0 && this->t==sporedba.t);
    }
};

class Repozitorium{
private:
    char ime[20];
    OperativenSistem *os;
    int n;

    void copy(const Repozitorium & r){
        strcpy(this->ime,r.ime);
        this->n=r.n;
        this->os=new OperativenSistem [this->n];
        for(int i=0;i<this->n;i++){
            this->os[i]=r.os[i];
        }
    }

public:
    Repozitorium(char ime[20]=""){
        strcpy(this->ime,ime);
        this->n=0;
        this->os=new OperativenSistem [this->n];
    }
    Repozitorium(const Repozitorium & r){
        copy(r);
    }
    ~Repozitorium(){
        delete [] os;
    }

    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<this->ime<<endl;
        for(int i=0;i<n;i++){
            os[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &izbrisi){
        int idx=-1;
        for (int i=0;i<n;i++) {
            if (os[i].ednakviSe(izbrisi)){
                idx = i;
                break;
            }
        }

        if (idx!=-1) {
            OperativenSistem * tmp = new OperativenSistem[n-1];
            int j = 0;
            for (int i=0;i<n;i++){
                if (i!=idx){
                    tmp[j++] = os[i];
                }
            }
            n=j;
            delete [] os;
            os = tmp;
        }
    }

    void dodadi(const OperativenSistem &nov){
        for(int i=0;i<n;i++){
            if(os[i].istaFamilija(nov) && os[i].sporediVerzija(nov)==-1){
                os[i]=nov;
                return;
            }
        }

        OperativenSistem *tmp=new OperativenSistem[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=os[i];
        }
        tmp[n++]=nov;
        delete [] os;
        os=tmp;

    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}