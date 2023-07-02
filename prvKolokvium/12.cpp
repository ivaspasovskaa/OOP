//
// Created by ivasp on 4/10/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Pica{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje;

    void copy(const Pica & p){
        strcpy(this->ime,p.ime);
        this->cena=p.cena;
        this->sostojki=new char [strlen(p.sostojki)+1];
        strcpy(this->sostojki,p.sostojki);
        this->namaluvanje=p.namaluvanje;
    }
public:
    Pica(char *ime="",int cena=0,char *sostojki="",int namaluvanje=0){
        strcpy(this->ime,ime);
        this->cena=cena;
        this->sostojki=new char [strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
        this->namaluvanje=namaluvanje;
    }
    Pica(const Pica & p){
        copy(p);
    }
    Pica & operator=(const Pica & p){
        if(this!=&p){
            delete [] sostojki;
            copy(p);
        }
        return *this;
    }
    ~Pica(){
        delete [] sostojki;
    }

    int getNamaluvanje(){
        return namaluvanje;
    }

    int getCena(){
        return cena;
    }

    void pecati(){
        cout<<ime<<" - "<<sostojki<<", "<<cena;
    }

    bool istiSe(Pica p){
        return strcmp(this->sostojki,p.sostojki)==0;
    }
};

class Picerija{
private:
    char ime[15];
    Pica *pici;
    int n;

    void copy(const Picerija & p){
        strcpy(this->ime,p.ime);
        this->n=p.n;
        this->pici=new Pica [this->n];
        for(int i=0;i<this->n;i++){
            this->pici[i]=p.pici[i];
        }
    }
public:
    Picerija(char *ime=""){
        strcpy(this->ime,ime);
        this->n=0;
        this->pici=new Pica [this->n];
    }
    Picerija(const Picerija & p){
        copy(p);
    }
    Picerija & operator=(const Picerija & p){
        if(this!=&p){
            delete [] pici;
            copy(p);
        }
        return *this;
    }
    ~Picerija(){
        delete [] pici;
    }

    void setIme(char *ime){
        strcpy(this->ime,ime);
    }

    char *getIme(){
        return ime;
    }

    void addPiza(Pica P){
        for(int i=0;i<n;i++){
            if(pici[i].istiSe(P)){
                return;
            }
        }

        Pica *tmp=new Pica [n+1];
        for(int i=0;i<n;i++){
            tmp[i]=pici[i];
        }
        tmp[n++]=P;
        delete [] pici;
        pici=tmp;
    }

    void piciNaPromocija(){
        for(int i=0;i<n;i++){
            if(pici[i].getNamaluvanje()){
                pici[i].pecati();
                int novaCena=pici[i].getCena()-(pici[i].getCena()*pici[i].getNamaluvanje()/100);
                cout<<" "<<novaCena<<endl;
            }
        }
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        //p1+=p;
        p1.addPiza(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2.addPiza(p);

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
