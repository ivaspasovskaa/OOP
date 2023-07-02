//
// Created by ivasp on 4/9/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Gitara{
private:
    char seriskiBroj[25];
    float nabavnaCena;
    int godina;
    char tip[40];
public:
    Gitara(char *tip="", char *seriskiBroj="",int godina=2022,float nabavnaCena=2000){
        strcpy(this->tip,tip);
        strcpy(this->seriskiBroj,seriskiBroj);
        this->godina=godina;
        this->nabavnaCena=nabavnaCena;
    }
    Gitara(const Gitara & g){
        strcpy(this->tip,g.tip);
        strcpy(this->seriskiBroj,g.seriskiBroj);
        this->godina=g.godina;
        this->nabavnaCena=g.nabavnaCena;
    }

    char *getTip(){
        return tip;
    }

    char *getSeriski(){
        return seriskiBroj;
    }

    int getGodina(){
        return godina;
    }

    float getNabavna(){
        return nabavnaCena;
    }

    bool daliIsti(const Gitara & g){
        return strcmp(this->seriskiBroj,g.seriskiBroj)==0;
    }

    void pecati(){
        cout<<seriskiBroj<<" "<<tip<<" "<<nabavnaCena<<endl;
    }
};

class Magacin{
private:
    char ime[30];
    char lokacija[60];
    Gitara *gitari;
    int n;
    int godina;

    void copy(const Magacin & m){
        strcpy(this->ime,m.ime);
        strcpy(this->lokacija,m.lokacija);
        this->n=m.n;
        this->gitari=new Gitara[m.n];
        for(int i=0;i<m.n;i++){
            gitari[i]=m.gitari[i];
        }
        this->godina=m.godina;
    }
public:
    Magacin(char *ime="",char *lokacija="",int godina=2000){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->godina=godina;
        this->n=0;
        this->gitari=new Gitara[this->n];
    }
    Magacin(const Magacin & m){
        copy(m);
    }
    Magacin & operator=(const Magacin & m){
        if(this!=&m){
            delete [] gitari;
            copy(m);
        }
        return *this;
    }
    ~Magacin(){
        delete [] gitari;
    }

    double vrednost(){
        double v=0;
        for(int i=0;i<n;i++){
            v+=gitari[i].getNabavna();
        }
        return v;
    }

    void dodadi(Gitara d){
        Gitara *tmp=new Gitara [n+1];
        for(int i=0;i<n;i++){
            tmp[i]=gitari[i];
        }
        tmp[n++]=d;
        delete [] gitari;
        gitari=tmp;
    }

    void prodadi(Gitara & p){
        int j=0;
        Gitara *tmp=new Gitara [n-1];
        for(int i=0;i<n;i++){
            if(!gitari[i].daliIsti(p)){
                tmp[j++]=gitari[i];
            }
        }
        n=j;
        delete [] gitari;
        gitari=tmp;
    }

    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        if(daliNovi){
            for(int i=0;i<n;i++){
                if(gitari[i].getGodina()>godina){
                    gitari[i].pecati();
                }
            }
        }else{
            for(int i=0;i<n;i++){
                gitari[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}