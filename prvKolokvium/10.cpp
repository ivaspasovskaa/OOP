//
// Created by ivasp on 4/7/2023.
//
#include <iostream>
using namespace std;

struct Igrac{
    char ime[15];
    int nivo;
    int poeni;
};
typedef struct Igrac Igrac;

void readIgrac(Igrac &i){
    cin>>i.ime>>i.nivo>>i.poeni;
}

struct KompjuterskaIgra{
    char ime[20];
    Igrac igraci[30];
    int brNaIgraci;
};
typedef struct KompjuterskaIgra KompjuterskaIgra;

void readIgra(KompjuterskaIgra &k){
    cin>>k.ime>>k.brNaIgraci;
    for(int i=0;i<k.brNaIgraci;i++){
        readIgrac(k.igraci[i]);
    }
}

void najdobarIgrac(KompjuterskaIgra *k, int n){
    int najgolemaPopularnost=0;
    int indeks1=0;
    for(int i=0;i<n;i++){
        if(k[i].brNaIgraci>najgolemaPopularnost){
            najgolemaPopularnost=k[i].brNaIgraci;
            indeks1=i;
        }
    }

    int najmnoguPoeni=0;
    int najgolemoNivo=0;
    int indeks2=0;
    for(int i=0;i<k[indeks1].brNaIgraci;i++){
        if(k[indeks1].igraci[i].poeni>najmnoguPoeni){
            najmnoguPoeni=k[indeks1].igraci[i].poeni;
            indeks2=i;
            najgolemoNivo=k[indeks1].igraci[i].nivo;
        }
        else if(najmnoguPoeni==k[indeks1].igraci[i].poeni && najgolemoNivo<k[indeks1].igraci[i].nivo){
            indeks2=i;
            najgolemoNivo=k[indeks1].igraci[i].nivo;
        }
    }

    cout<<"Najdobar igrac e igracot so korisnicko ime "<<k[indeks1].igraci[indeks2].ime<<" koj ja igra igrata "<<k[indeks1].ime;
}

int main(){
    int n;
    cin>>n;
    KompjuterskaIgra k[10];

    for(int i=0;i<n;i++){
        readIgra(k[i]);
    }

    najdobarIgrac(k,n);

    return 0;
}