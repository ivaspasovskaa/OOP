//
// Created by ivasp on 4/10/2023.
//
#include <stdio.h>

struct Driver{
    char name[100];
    int time;
};
typedef struct Driver Driver;

struct Race{
    char location[100];
    int n;
    Driver drivers[100];
};
typedef struct Race Race;

void readDriver(Driver *d){
    scanf("%s %d",d->name,&d->time);
}

void readRace(Race *r){
    scanf("%s %d",r->location,&r->n);
    for(int i=0;i<r->n;i++){
        readDriver(r->drivers+i);
    }
}

void sort(Driver *d,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(d[j].time>d[j+1].time){
                Driver tmp=d[j];
                d[j]=d[j+1];
                d[j+1]=tmp;
            }
        }
    }
}

void top3Drivers(Race r){
    sort(r.drivers,r.n);
    printf("%s (%d Drivers)\n",r.location,r.n);
    for(int i=0;i<3;i++){
        printf("%d. %s %2d:%02d\n",i+1,r.drivers[i].name,r.drivers[i].time/60,r.drivers[i].time%60);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    Race race[100];
    for(int i=0;i<n;i++){
        readRace(race+i);
    }

    for(int i=0;i<n;i++){
        top3Drivers(race[i]);
    }
    return 0;
}