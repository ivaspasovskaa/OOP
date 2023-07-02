//
// Created by ivasp on 6/3/2023.
//
#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

//место за вашиот код
class NegativnaVrednost{
public:
    void showMessage(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;

public:
    Oglas(char *naslov="", char *kategorija="", char *opis="", float cena=0){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }

    bool operator>(Oglas & o) const{
        return this->cena>o.cena;
    }

    friend ostream & operator<<(ostream & out, const Oglas & o){
        return out<<o.naslov<<endl<<o.opis<<endl<<o.cena<<" evra"<<endl;
    }

    float getCena(){
        return cena;
    }

    char *getKategorija(){
        return kategorija;
    }
};

class Oglasnik{
private:
    char ime[50];
    Oglas *oglasi;
    int n;

    void copy(const Oglasnik & o){
        strcpy(this->ime,ime);
        this->n=o.n;
        this->oglasi=new Oglas [o.n];
        for(int i=0;i<o.n;i++){
            this->oglasi[i]=o.oglasi[i];
        }
    }
public:
    Oglasnik(char *ime=""){
        strcpy(this->ime,ime);
        this->n=0;
        this->oglasi=new Oglas[0];
    }

    Oglasnik(const Oglasnik & o){
        copy(o);
    }

    Oglasnik & operator=(const Oglasnik & o){
        if(this!=&o){
            delete [] oglasi;
            copy(o);
        }
        return *this;
    }

    ~Oglasnik(){
        delete [] oglasi;
    }

    Oglasnik & operator+=(Oglas & o){
        if(o.getCena()<0){
            throw NegativnaVrednost();
        }
        Oglas *tmp=new Oglas[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=oglasi[i];
        }
        tmp[n++]=o;
        delete oglasi;
        oglasi=tmp;
        return *this;
    }

    friend ostream & operator<<(ostream & out, const Oglasnik & o){
        out<<o.ime<<endl;
        for(int i=0;i<o.n;i++){
            out<<o.oglasi[i]<<endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k){
        for(int i=0;i<n;i++){
            if(strcmp(oglasi[i].getKategorija(),k)==0){
                cout<<oglasi[i]<<endl;
            }
        }
    }

    void najniskaCena(){
        Oglas min=oglasi[0];
        for(int i=0;i<n;i++){
            if(min>oglasi[i]){
                min=oglasi[i];
            }
        }
        cout<<min;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch (NegativnaVrednost & e) {
                e.showMessage();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch (NegativnaVrednost & e) {
                e.showMessage();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch (NegativnaVrednost & e) {
                e.showMessage();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch (NegativnaVrednost & e) {
                e.showMessage();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch (NegativnaVrednost & e) {
                e.showMessage();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}