//
// Created by ivasp on 4/7/2023.
//
 #include<stdio.h>

 struct Pacient{
    char ime[100];
    int zdrastveno;
    int pregledi;
};
typedef struct Pacient Pacient;

struct MaticenDoktor{
    char ime[100];
    int br_pac;
    Pacient niza[200];
    float cena;
};
typedef struct MaticenDoktor doktor;

void najuspesen_doktor(doktor *md,int n){
    int indeks=0;
    float vkupnaCena=0;
    int vkupnoPregledi=0;
    for(int i=0;i<n;i++){
        int suma=0;
        int brPregledi=0;
        float cena;
        for(int j=0;j<md[i].br_pac;j++){
            if(!md[i].niza[j].zdrastveno){
                suma+=md[i].niza[j].pregledi;
                brPregledi+=md[i].niza[j].pregledi;
            }
        }
        cena=suma*md[i].cena;

        brPregledi=0;
        for(int j=0;j<md[i].br_pac;j++){
            brPregledi+=md[i].niza[j].pregledi;
        }

        if(vkupnaCena<cena){
            vkupnaCena=cena;
            indeks=i;
            vkupnoPregledi=brPregledi;
        }
        else if(vkupnaCena==cena && vkupnoPregledi<brPregledi){
            indeks=i;
            vkupnoPregledi=brPregledi;
        }
    }

    printf("%s %.2f %d",md[indeks].ime,vkupnaCena,vkupnoPregledi);
}

 int main()
 {
 	int i, j, n, broj;
 	doktor md[200];
 	scanf("%d", &n);
 	for (i = 0; i < n; i++){
 		//ime na doktor
 		scanf("%s", &md[i].ime);
 		//broj na pacienti
 		scanf("%d", &md[i].br_pac);
 		//cena na pregled
 		scanf("%f", &md[i].cena);

 		for (j = 0; j < md[i].br_pac; j++){
 			scanf("%s", &md[i].niza[j].ime);
 			scanf("%d", &md[i].niza[j].zdrastveno);
 			scanf("%d", &md[i].niza[j].pregledi);
 		}
 	}
 	najuspesen_doktor(md, n);

 	return 0;
 }