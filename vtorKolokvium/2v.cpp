//
// Created by ivasp on 5/30/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
// vashiot kod ovde
class Vozac{
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool vet;

public:
    Vozac(const char *ime="",int vozrast=0,int trki=0,bool vet=false){
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->trki=trki;
        this->vet=vet;
    }

    virtual float zarabotuvacka()=0;

    virtual float danok()=0;

    friend ostream &operator<<(ostream &os, Vozac &vozac) {
        os<<vozac.ime<<endl<<vozac.vozrast<<endl<<vozac.trki<<endl;
        if(vozac.vet){
            cout<<"VETERAN"<<endl;
        }
        return os;
    }

    bool operator==(Vozac &v){
        return zarabotuvacka()==v.zarabotuvacka();
    }

};

class Avtomobilist : public Vozac{
private:
    float cena_avto;

public:
    Avtomobilist(const char *ime="",int vozrast=0,int trki=0,bool vet=false, float cena_avto=0.0) : Vozac(ime, vozrast, trki, vet){
        this->cena_avto=cena_avto;
    }

    float zarabotuvacka(){
        return cena_avto/5;
    }

    float danok(){
        if(trki>10){
            return zarabotuvacka()*0.15;
        }else{
            return zarabotuvacka()*0.1;
        }
    }

};

class Motociklist : public Vozac{
private:
    int mokjnost;

public:
    Motociklist(const char *ime="",int vozrast=0,int trki=0,bool vet=false, int mokjnost=0) : Vozac(ime, vozrast, trki, vet){
        this->mokjnost=mokjnost;
    }

    float zarabotuvacka(){
        return mokjnost*20;
    }

    float danok(){
        if(vet){
            return zarabotuvacka()*0.25;
        }else{
            return zarabotuvacka()*0.2;
        }
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx){
    int isti=0;
    for(int i=0;i<n;i++){
        if(*v[i]==*vx){
            isti++;
        }
    }
    return isti;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}