//
// Created by ivasp on 6/3/2023.
//
#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
private:
    char ime[50];
    int godina;
    char zemja[50];

public:
    Delo(char *ime="",int godina=0,char *zemja=""){
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }

    bool operator==(const Delo &d){
        return strcmp(this->ime,d.ime)==0;
    }

    char *getIme(){
        return ime;
    }

    int getGodina(){
        return godina;
    }

    char *getZemja(){
        return zemja;
    }
};

class Pretstava{
protected:
    Delo d;
    int brojProdadeni;
    char data[15];

public:
    Pretstava(Delo d=0, int brojProdadeni=0,char *data=""){
        this->d=d;
        this->brojProdadeni=brojProdadeni;
        strcpy(this->data,data);
    }

    virtual int cena(){
        int m,n;
        int vek=(d.getGodina()/100)+1;
        if(vek==20 || vek==21){
            m=50;
        }else if(vek==19){
            m=75;
        }else{
            m=100;
        }

        if(strcmp("Italija",d.getZemja())==0){
            n=100;
;        }else if(strcmp("Rusija",d.getZemja())==0){
            n=150;
        }else{
            n=80;
        }
        return m+n;
    }

    Delo getDelo(){
        return d;
    }

    int getBrojProdadeni(){
        return brojProdadeni;
    }
};

class Balet : public Pretstava{
private:
    static int CENA;

public:
    Balet(Delo d=0, int brojProdadeni=0,char *data="")
    : Pretstava(d,brojProdadeni,data){}

    static void setCenaBalet(int C){
        CENA=C;
    }

    int cena(){
        return Pretstava::cena()+CENA;
    }
};

int Balet::CENA=150;

class Opera : public Pretstava{
public:
    Opera(Delo d=0, int brojProdadeni=0,char *data="")
    : Pretstava(d,brojProdadeni,data){}

    int cena(){
        return Pretstava::cena();
    }
};

float prihod(Pretstava **p,int n){
    float sum=0;
    for(int i=0;i<n;i++){
        sum+=p[i]->cena()*p[i]->getBrojProdadeni();
    }
    return sum;
}

int brojPretstaviNaDelo(Pretstava **p,int n,Delo d){
    int counter=0;
    for(int i=0;i<n;i++){
        if(p[i]->getDelo()==d){
            counter++;
        }
    }
    return counter;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}