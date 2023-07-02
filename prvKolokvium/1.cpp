//
// Created by ivasp on 4/8/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

enum tip{
    POP, RAP, ROK
};

class Pesna{
private:
    char *ime;
    int vremetraenje;
    tip t;

    void copy(const Pesna & p){
        this->ime=new char [strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->vremetraenje=p.vremetraenje;
        this->t=p.t;
    }
public:
    Pesna(char *ime="",int vremetraenje=0,enum tip t=POP){
        this->ime=new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vremetraenje=vremetraenje;
        this->t=t;
    }

    Pesna(const Pesna & p){
        copy(p);
    }

    Pesna & operator=(const Pesna & p){
        if(this!=&p){
            delete [] ime;
            copy(p);
        }
        return *this;
    }

    ~Pesna(){
        delete [] ime;
    }

    int getVremetraenje(){
        return vremetraenje;
    }

    tip getTip(){
        return t;
    }

    void pecati(){
        cout<<"\""<<ime<<"\""<<"-"<<vremetraenje<<"min"<<endl;
    }
};

class CD{
private:
    Pesna *pesni;
    int brPesni;
    int vremetraenje;

    void copy(const CD & cd){
        this->brPesni=cd.brPesni;
        this->pesni=new Pesna[this->brPesni];
        for(int i=0;i<this->brPesni;i++){
            this->pesni[i]=cd.pesni[i];
        }
        this->vremetraenje=cd.vremetraenje;
    }

public:
    CD(int vremetraenje=0){
        this->pesni=new Pesna[0];
        this->brPesni=0;
        this->vremetraenje=vremetraenje;
    }

    CD(const CD & cd){
        copy(cd);
    }

    ~CD(){
        delete [] pesni;
    }

    int getBroj(){
        return brPesni;
    }

    Pesna getPesna(int n){
        return pesni[n];
    }

    void dodadiPesna(Pesna p){
        int maxVremetraenje=0;
        for(int i=0;i<brPesni;i++){
            maxVremetraenje+=pesni[i].getVremetraenje();
        }

        if(maxVremetraenje+p.getVremetraenje()<vremetraenje && brPesni<10){
            Pesna *tmp=new Pesna[brPesni+1];
            for(int i=0;i<brPesni;i++){
                tmp[i]=pesni[i];
            }
            tmp[brPesni++]=p;
            delete [] pesni;
            pesni=tmp;
        }
    }

    void pecatiPesniPoTip(tip t){
        for(int i=0;i<brPesni;i++){
            if(pesni[i].getTip()==(tip)t){
                pesni[i].pecati();
            }
        }
    }

};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}