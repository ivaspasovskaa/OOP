//
// Created by ivasp on 6/2/2023.
//
#include<iostream>
#include<string.h>
using namespace std;

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    // дополниете ја класата

    Karticka(const Karticka & k){
        strcpy(this->smetka,k.smetka);
        this->pin=k.pin;
        this->povekjePin=k.povekjePin;
    }

    virtual int tezinaProbivanje(){
        int counter=0;
        int tmp=pin;
        while(tmp>0){
            counter++;
            tmp/=10;
        }
        return counter;
    }

    friend ostream &operator<<(ostream &os, Karticka &karticka) {
        os<<karticka.smetka<<": "<<karticka.tezinaProbivanje();
        return os;
    }

    bool getDopolnitelenPin(){
        return povekjePin;
    }

    char *getSmetka(){
        return smetka;
    }
};

class OutOfBoundException{
public:
    void showMessage(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

//вметнете го кодот за SpecijalnaKarticka
class SpecijalnaKarticka : public Karticka{
private:
    int n;
    int *pinKodovi;
    const static int MAX=4;

public:
    SpecijalnaKarticka(char* smetka,int pin) : Karticka(smetka,pin){
        this->povekjePin=true;
        this->n=0;
        this->pinKodovi=new int [0];
    }

    SpecijalnaKarticka(const SpecijalnaKarticka & s) : Karticka(s){
        this->povekjePin=true;
        this->n=s.n;
        this->pinKodovi=new int [s.n];
        for(int i=0;i<s.n;i++){
            this->pinKodovi[i]=s.pinKodovi[i];
        }
    }

    int tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+n;
    }

    SpecijalnaKarticka & operator+=(int pin){
        if(n>=MAX){
            throw OutOfBoundException();
        }
        int *tmp=new int[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=pinKodovi[i];
        }
        tmp[n++]=pin;
        delete [] pinKodovi;
        pinKodovi=tmp;
        return *this;
    }

};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата
    static void setLIMIT(int l){
        LIMIT=l;
    }

    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++){
            if(karticki[i]->tezinaProbivanje()<=LIMIT){
                cout<<*karticki[i]<<endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for(int i=0;i<broj;i++){
            if(karticki[i]->getDopolnitelenPin()){
                if(strcmp(karticki[i]->getSmetka(), smetka) == 0){
                    *dynamic_cast<SpecijalnaKarticka *>(karticki[i]) += novPin;
                }
            }
        }
    }
};

int Banka::LIMIT=7;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
        try{
            komercijalna.dodadiDopolnitelenPin(smetka,pin);
        }
        catch (OutOfBoundException & e) {
            e.showMessage();
        }
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}