//
// Created by ivasp on 4/7/2023.
//
#include <stdio.h>

struct Vozenje{
    char ime[100];
    int vremetraenje;
    float cena;
    int popust;
};
typedef struct Vozenje Vozenje;

struct ZabavenPark{
    char ime[100];
    char lokacija[100];
    Vozenje vozenja[100];
    int brNaVozenja;
};
typedef struct ZabavenPark ZabavenPark;

void pecati(ZabavenPark *z,int n){
    for(int i=0;i<n;i++){
        printf("%s %s\n",z[i].ime,z[i].lokacija);
        for(int j=0;j<z[i].brNaVozenja;j++){
            printf("%s %d %.2f\n",z[i].vozenja[j].ime,z[i].vozenja[j].vremetraenje,z[i].vozenja[j].cena);
        }
    }
}

void najdobar_park(ZabavenPark *z,int n){
    int indeks=0;
    int maxPopust=0;
    int maxVremetraenje=0;
    for(int i=0;i<n;i++){
        int popust=0;
        int vreme=0;
        for(int j=0;j<z[i].brNaVozenja;j++){
            popust+=z[i].vozenja[j].popust;
            vreme+=z[i].vozenja[j].vremetraenje;
        }

        if(maxPopust<popust){
            maxPopust=popust;
            indeks=i;
            maxVremetraenje=vreme;
        }
        else if(popust==maxPopust && vreme>maxVremetraenje){
            indeks=i;
            maxVremetraenje=vreme;
        }
    }

    printf("Najdobar park: %s %s",z[indeks].ime,z[indeks].lokacija);
}

int main()
{
    int i, j, n, broj;
    ZabavenPark z[100];  //kreiraj niza od maksimum 100 zabavni parkovi
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
        scanf("%s",z[i].ime);//ime na zabavniot park
        scanf("%s",z[i].lokacija);//lokacija
        scanf("%d",&z[i].brNaVozenja);//broj na vozenja
        for (j = 0; j < z[i].brNaVozenja; j++){
            scanf("%s",z[i].vozenja[j].ime);/* Ime na vozenjeto */
            scanf("%d",&z[i].vozenja[j].vremetraenje);/* Vremetraenje   */
            scanf("%f",&z[i].vozenja[j].cena);/* Cena */
            scanf("%d",&z[i].vozenja[j].popust);/* Popust */
        }


    }
    pecati(z,n);
    najdobar_park(z,n);

    return 0;
}
