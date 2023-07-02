//
// Created by ivasp on 4/7/2023.
//
#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
    char relacija[50];
    float km;
    int brNaPatnici;
};
typedef struct Voz Voz;

void readVoz(Voz &v){
    cin>>v.relacija>>v.km>>v.brNaPatnici;
}

struct ZeleznickaStanica{
    char grad[20];
    Voz vozovi[30];
    int brNaVozovi;
};
typedef struct ZeleznickaStanica ZeleznickaStanica;

void readZeleznickaStanica(ZeleznickaStanica & z){
    cin>>z.grad>>z.brNaVozovi;
    for(int i=0;i<z.brNaVozovi;i++){
        readVoz(z.vozovi[i]);
    }
}

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
    int indeks1=0,indeks2=0;
    for(int i=0;i<n;i++){
        if(strcmp(grad,zs[i].grad)==0){
            indeks1=i;
            float min=zs[i].vozovi[0].km;
            for(int j=0;j<zs[i].brNaVozovi;j++){
                if(min>=zs[i].vozovi[j].km){
                    min=zs[i].vozovi[j].km;
                    indeks2=j;
                }
            }
        }
    }

    cout<<"Najkratka relacija: "<<zs[indeks1].vozovi[indeks2].relacija<<" ("<<zs[indeks1].vozovi[indeks2].km<<" km)"<<endl;
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        readZeleznickaStanica(zStanica[i]); //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}