//
// Created by ivasp on 6/5/2023.
//
#include<iostream>
#include<cstring>
using namespace std;

// вашиот код треба да биде тука
class Transport{
protected:
    char destinacija[20];
    int cena,rastojanie;

public:
    Transport(char *destinacija="",int cena=0,int rastojanie=0){
        strcpy(this->destinacija,destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }

    virtual int cenaTransport(){
        return cena;
    }

    bool operator<(Transport &t) {
        return getRastojanie()<t.getRastojanie();
    }

    char *getDestinacija(){
        return destinacija;
    }

    int getRastojanie(){
        return rastojanie;
    }
};

class AvtomobilTransport : public Transport{
private:
    bool shofer;

public:
    AvtomobilTransport(char *destinacija="",int cena=0,int rastojanie=0,bool shofer=false)
            : Transport(destinacija,cena,rastojanie){
        this->shofer=shofer;
    }

    int cenaTransport(){
        if(shofer){
            return cena*1.2;
        }else
            return cena;
    }
};

class KombeTransport : public Transport{
private:
    int lugje;

public:
    KombeTransport(char *destinacija="",int cena=0,int rastojanie=0,int lugje=0)
            : Transport(destinacija,cena,rastojanie){
        this->lugje=lugje;
    }

    int cenaTransport(){
        return cena-lugje*200;
    }
};

void pecatiPoloshiPonudi(Transport **ponudi,int n,AvtomobilTransport a){
    Transport **tmp=new Transport * [n];
    int k=0;
    for(int i=0;i<n;i++){
        if(ponudi[i]->cenaTransport()>a.cenaTransport()){
            tmp[k++]=ponudi[i];
        }
    }

    for(int i=0;i<k-1;i++){
        for(int j=0;j<k-i-1;j++){
            if(*tmp[j+1]<*tmp[j]){
                Transport *t=tmp[j];
                tmp[j]=tmp[j+1];
                tmp[j+1]=t;
            }
        }
    }

    for(int i=0;i<k;i++){
        cout<<tmp[i]->getDestinacija()<<" "<<tmp[i]->getRastojanie()<<" "<<tmp[i]->cenaTransport()<<endl;
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}