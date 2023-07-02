//
// Created by ivasp on 6/5/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class FudbalskaEkipa{
protected:
    char coach[100];
    int goals[10];

public:
    FudbalskaEkipa(char *coach="",int *goals=0){
        strcpy(this->coach,coach);
        for(int i=0;i<10;i++){
            this->goals[i]=goals[i];
        }
    }

    FudbalskaEkipa & operator+=(int lastGoals){
        for(int i=0;i<9;i++){
            this->goals[i]=this->goals[i+1];
        }
        this->goals[9]=lastGoals;
        return *this;
    }

    virtual int uspeh()=0;

    bool operator>(FudbalskaEkipa & f){
        return uspeh()>f.uspeh();
    }

    char *getCoach(){
        return coach;
    }
};

class Klub : public FudbalskaEkipa{
private:
    char name[100];
    int titles;

public:
    Klub(char *coach="",int *goals=0,char *name="",int titles=0)
    : FudbalskaEkipa(coach,goals){
        strcpy(this->name,name);
        this->titles=titles;
    }

    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++){
            sum+=goals[i];
        }
        return sum*3+titles*1000;
    }

    char *getName(){
        return name;
    }
};

class Reprezentacija : public FudbalskaEkipa{
private:
    char country[100];
    int matches;

public:
    Reprezentacija(char *coach="",int *goals=0,char *country="",int matches=0)
            : FudbalskaEkipa(coach,goals){
        strcpy(this->country,country);
        this->matches=matches;
    }

    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++){
            sum+=goals[i];
        }
        return sum*3+matches*50;
    }

    char *getCountry(){
        return country;
    }
};

ostream & operator<<(ostream & out, FudbalskaEkipa & f){
    Klub *k=dynamic_cast<Klub *>(&f);
    if(k){
        out<<k->getName()<<endl;
    }else{
        Reprezentacija *r=dynamic_cast<Reprezentacija *>(&f);
        if(r){
            out<<r->getCountry()<<endl;
        }
    }
    return out<<f.getCoach()<<endl<<f.uspeh()<<endl;
}

void najdobarTrener(FudbalskaEkipa **ekipi, int n){
    FudbalskaEkipa *best=ekipi[0];
    for(int i=0;i<n;i++){
        if(*ekipi[i]>*best){
            best=ekipi[i];
        }
    }
    cout<<*best;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}