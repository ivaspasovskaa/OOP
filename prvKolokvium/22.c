//
// Created by ivasp on 4/8/2023.
//
#include <stdio.h>
#include <string.h>

//место за вашиот код
struct Proizvod{
    char kod[20];
    int cena;
    int brProizvodi;
};
typedef struct Proizvod Proizvod;

struct Narachka{
    char ime[15];
    Proizvod proizvodi[10];
    int brProizvodiZaSekojProizvod[10];
    int n; //brVkupnoNarachaniProizvodi
};
typedef struct Narachka Narachka;

void swap(Proizvod *x,Proizvod *y){
    Proizvod tmp=*x;
    *x=*y;
    *y=tmp;
}

void pecatiFaktura(Narachka n){
    printf("Faktura za %s\n",n.ime);
    for(int i=0;i<n.n;i++){
        if(n.brProizvodiZaSekojProizvod[i]>n.proizvodi[i].brProizvodi){
            printf("Fakturata ne moze da se izgotvi");
            return;
        }
    }

    for(int i=0;i<n.n;i++){
        for(int j=0;j<n.n-i-1;j++){
            if(strcmp(n.proizvodi[j].kod,n.proizvodi[j+1].kod)>0){
                swap(&n.proizvodi[j],&n.proizvodi[j+1]);
            }
        }
    }

    int vkupnaSuma=0;
    for(int i=0;i<n.n;i++){
        int suma=n.proizvodi[i].cena*n.brProizvodiZaSekojProizvod[i];
        printf("%s %d %d %d\n",n.proizvodi[i].kod,n.proizvodi[i].cena,n.brProizvodiZaSekojProizvod[i],suma);
        vkupnaSuma+=suma;
    }
    printf("Vkupnata suma na fakturata e %d",vkupnaSuma);
}

int main() {

    Narachka narachka;

    scanf("%s",narachka.ime);// внеси го името лицето кое ја прави нарачката
    scanf("%d",&narachka.n);// внеси го бројот на порачани производи во нарачката

    int i;
    //за секој од нарачаните производи се внесуваат информации
    for (i = 0; i < narachka.n; ++i) {
        scanf("%s",narachka.proizvodi[i].kod);// внеси код
        scanf("%d",&narachka.proizvodi[i].cena);// внеси единицчна цена
        scanf("%d",&narachka.proizvodi[i].brProizvodi);// внеси број на производи во магацин
    }
    //за секој производ се внесува колку такви производи се порачани во нарачката
    int j;
    for (j = 0; j < narachka.n; ++j) {
        scanf("%d",&narachka.brProizvodiZaSekojProizvod[j]);//се внесува број на производи во нарачката
    }

    // повик на функцијата pecatiFaktura
    pecatiFaktura(narachka);

    return 0;
}