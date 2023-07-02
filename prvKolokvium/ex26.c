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
    scanf("%s %d %d/%d/%d",t->currency,&t->amount,&t->day,&t->month,&t->year);
}

void print(Transaction *t,int n){
    char *usd="USD";
    int j=1;
    int totalAmount=0;
    for(int i=0;i<n;i++){
        if(strcmp(t[i].currency,usd)==0 && t[i].amount<5000 && t[i].month>=1 && t[i].month<=3){
            printf("%d. %.02d/%.02d/%d %d USD\n",j++,t[i].day,t[i].month,t[i].year,t[i].amount);
            totalAmount+=t[i].amount;
        }
    }
    printf("Total: %d USD",totalAmount);
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