//
// Created by ivasp on 4/10/2023.
//
//
// Created by ivasp on 4/10/2023.
//
#include <stdio.h>
#include <string.h>

struct Transaction{
    int day;
    int month;
    int year;
    int amount;
    char currency[3];
};
typedef struct Transaction Transaction;

void readTransaction(Transaction *t){
    scanf("%d/%d/%d %d %s",&t->day,&t->month,&t->year,&t->amount,t->currency);
}

void print(Transaction *t,int n){
    char *mkd="MKD";
    int j=1;
    int totalAmount=0;
    for(int i=0;i<n;i++){
        if(strcmp(t[i].currency,mkd)==0 && t[i].amount>1000 && t[i].year>=2013 && t[i].year<=2015){
            printf("%d. %.02d/%.02d/%d %d MKD\n",j++,t[i].day,t[i].month,t[i].year,t[i].amount);
            totalAmount+=t[i].amount;
        }
    }
    printf("Total: %d MKD",totalAmount);
}

int main(){
    int n;
    scanf("%d",&n);
    Transaction t[500];
    for(int i=0;i<n;i++){
        readTransaction(t+i);
    }

    print(t,n);

    return 0;
}