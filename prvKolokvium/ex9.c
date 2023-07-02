//
// Created by ivasp on 4/10/2023.
//
#include<stdio.h>

struct Film{
    char name[100];
    int time;
    float price;
    int discount;
};
typedef struct Film Film;

struct FilmFestival{
    char name[100];
    char place[100];
    Film films[100];
    int no;
};
typedef struct FilmFestival FilmFestival;

void printFilm(Film f){
    printf("%s %d %.2f\n",f.name,f.time,f.price);
}

void print(FilmFestival f){
    printf("%s %s\n",f.name,f.place);
    for(int i=0;i<f.no;i++){
        printFilm(f.films[i]);
    }
}

void bestFestival(FilmFestival *f,int n){
    int maxDiscount=0;
    int LongestDuration=0;
    int index=0;
    for(int i=0;i<n;i++){
        int discount=0;
        int duration=0;
        for(int j=0;j<f[i].no;j++){
            discount+=f[i].films[j].discount;
            duration+=f[i].films[j].time;
        }

        if(maxDiscount<discount){
            maxDiscount=discount;
            index=i;
            LongestDuration=duration;
        }
        else if(maxDiscount==discount && LongestDuration<duration){
            index=i;
            LongestDuration=duration;
        }
    }
    printf("Najdobar festival: %s %s",f[index].name,f[index].place);
}

int main()
{
    int i, j, n, broj;
    FilmFestival ff[50];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        /* name of the festival */
        scanf("%s", ff[i].name);
        /* place it is held */
        scanf("%s", ff[i].place);
        /* number of movies */
        scanf("%d", &ff[i].no);

        for (j = 0; j < ff[i].no; j++){
            scanf("%s", ff[i].films[j].name);  		/* title of the movie */
            scanf("%d", &ff[i].films[j].time); 		/* duration */
            scanf("%f", &ff[i].films[j].price); 	/* price */
            scanf("%d", &ff[i].films[j].discount);	/* discount */
        }
    }

    for(i=0; i<n; ++i){
        print(ff[i]);
    }

    bestFestival(ff, n);


    return 0;
}