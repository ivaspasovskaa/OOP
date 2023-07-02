//
// Created by ivasp on 3/12/2023.
//
#include <stdio.h>

struct SkiLift{
    char ime[15];
    int maxKorisnici;
    int voFunkcija;
};
typedef struct SkiLift SkiLift;

struct SkiCenter{
    char ime[20];
    char drzava[20];
    SkiLift skiLiftovi[20];
    int brSkiLiftovi;
};
typedef struct SkiCenter SkiCenter;

void readLift(SkiLift *skiLift){
    scanf("%s %d %d",skiLift->ime,&skiLift->maxKorisnici,&skiLift->voFunkcija);
}

void readCenter(SkiCenter *skiCenter){
    scanf("%s %s %d",skiCenter->ime,skiCenter->drzava,&skiCenter->brSkiLiftovi);
    for(int i=0;i<skiCenter->brSkiLiftovi;i++){
        readLift(skiCenter->skiLiftovi+i);
    }
}

void najgolemKapacitet(SkiCenter *sc,int n){
    int indeks=0;
    int maxKapacitet=0;
    int maxSkiLiftovi=0;
    for(int i=0;i<n;i++){
        int kapacitet=0;
        for(int j=0;j<sc[i].brSkiLiftovi;j++){
            if(sc[i].skiLiftovi[j].voFunkcija){
                kapacitet+=sc[i].skiLiftovi[j].maxKorisnici;
            }
        }

        if(maxKapacitet<kapacitet){
            maxKapacitet=kapacitet;
            indeks=i;
            maxSkiLiftovi=sc[i].brSkiLiftovi;
        }
        else if(maxKapacitet==kapacitet && maxSkiLiftovi<sc[i].brSkiLiftovi){
            indeks=i;
            maxSkiLiftovi=sc[i].brSkiLiftovi;
        }
    }
    printf("%s\n%s\n%d",sc[indeks].ime,sc[indeks].drzava,maxKapacitet);
}

int main(){
    int n;
    scanf("%d",&n);

    SkiCenter skiCenter[10];
    for(int i=0;i<n;i++){
        readCenter(skiCenter+i);
    }

    najgolemKapacitet(skiCenter,n);

    return 0;
}