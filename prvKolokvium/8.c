//
// Created by ivasp on 4/7/2023.
//
#include <stdio.h>

struct Laptop{
    char firma[100];
    float golemina;
    int touch;
    int cena;
};
typedef struct Laptop Laptop;

void readLaptop(Laptop *l){
    scanf("%s %f %d %d",l->firma,&l->golemina,&l->touch,&l->cena);
}

struct ITStore{
    char ime[100];
    char lokacija[100];
    Laptop laptopi[100];
    int brNaLaptopi;
};
typedef struct ITStore ITStore;

void readITStore(ITStore *it){
    scanf("%s %s %d",it->ime,it->lokacija,&it->brNaLaptopi);
    for(int i=0;i<it->brNaLaptopi;i++){
        readLaptop(it->laptopi+i);
    }
}

void print(ITStore *it,int n){
    for(int i=0;i<n;i++){
        printf("%s %s\n",it[i].ime,it[i].lokacija);
        for(int j=0;j<it[i].brNaLaptopi;j++){
            printf("%s %f %d\n",it[i].laptopi[j].firma,it[i].laptopi[j].golemina,it[i].laptopi[j].cena);
        }
    }
}

void najeftina_ponuda(ITStore *it,int n){
    int minCena;
    int indeks1=0;
    int flag=1;
    for(int i=0;i<n;i++){
        int min;
        for(int j=0;j<it[i].brNaLaptopi;j++){
            if(it[i].laptopi[j].touch){
                if(flag){
                    minCena=it[i].laptopi[j].cena;
                    min=it[i].laptopi[j].cena;
                    flag=0;
                }
                if(min>it[i].laptopi[j].cena){
                    min=it[i].laptopi[j].cena;
                }
            }
        }
        if(minCena>min){
            minCena=min;
            indeks1=i;
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n",it[indeks1].ime,it[indeks1].lokacija);
    printf("Najniskata cena iznesuva: %d",minCena);
}

int main() {
    ITStore s[100];
    int n;
    scanf("%d",&n); //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopi vo niv
    for(int i=0;i<n;i++){
        readITStore(s+i);
    }

    //pecatenje na site prodavnici
    print(s,n);

    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}