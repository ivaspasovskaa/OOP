//
// Created by ivasp on 4/8/2023.
//
#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

// ovde strukturata RabotnaNedela
struct RabotnaNedela{
    int casovi[DENOVI];
};
typedef struct RabotnaNedela RN;

// ovde strukturata Rabotnik
struct Rabotnik{
    char ime[50];
    RN nedeli[NEDELI];
};
typedef struct Rabotnik R;

// ovde funkciite
int maxNedela(R *r){
    int maxNedela=0;
    int maxCasovi=0;
    for(int i=0;i<NEDELI;i++){
        int casovi=0;
        for(int j=0;j<DENOVI;j++){
            casovi+=r->nedeli[i].casovi[j];
        }

        if(maxCasovi<casovi){
            maxCasovi=casovi;
            maxNedela=i;
        }
    }
    return maxNedela;
}

void table(R *r,int n){
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0;i<n;i++){
        printf("%s\t",r[i].ime);
        int vkupno=0;
        for(int j=0;j<NEDELI;j++){
            int suma=0;
            for(int k=0;k<DENOVI;k++){
                suma+=r[i].nedeli[j].casovi[k];
            }
            vkupno+=suma;
            printf("%d\t",suma);
        }
        printf("%d\n",vkupno);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}