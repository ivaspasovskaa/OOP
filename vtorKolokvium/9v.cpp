//
// Created by ivasp on 6/3/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Exception{
public:
    void showMessage(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud{
private:
    char tip;
    int godina;

public:
    Trud(char tip='C',int godina=0){
        this->tip=tip;
        this->godina=godina;
    }

    friend istream & operator>>(istream &in, Trud & t){
        return in>>t.tip>>t.godina;
    }

    char getTip(){
        return tip;
    }

    int getGodina(){
        return godina;
    }
};

class Student{
protected:
    char ime[30];
    int indeks;
    int godina;
    int oceni[50];
    int nOceni;

    void copy(const Student & s){
        strcpy(this->ime,s.ime);
        this->indeks=s.indeks;
        this->godina=s.godina;
        this->nOceni=s.nOceni;
        for(int i=0;i<s.nOceni;i++){
            this->oceni[i]=s.oceni[i];
        }
    }

public:
    Student(char *ime="",int indeks=0,int godina=0,int oceni[50]=0,int n=0){
        strcpy(this->ime,ime);
        this->indeks=indeks;
        this->godina=godina;
        this->nOceni=n;
        for(int i=0;i<n;i++){
            this->oceni[i]=oceni[i];
        }
    }

    virtual float rang() const{
        int sum=0;
        for(int i=0;i<nOceni;i++){
            sum+=oceni[i];
        }
        return (float)sum/nOceni;
    }

    friend ostream &operator<<(ostream & out, const Student & s){
        return out<<s.indeks<<" "<<s.ime<<" "<<s.godina<<" "<<s.rang()<<endl;
    }

    int getIndeks(){
        return indeks;
    }

    int getGodina(){
        return godina;
    }
};

class PhDStudent : public Student{
private:
    Trud *trudovi;
    int n;
    static int KONF;
    static int SPIS;

    void copy(const PhDStudent & p){
        Student::copy(p);
        this->n=p.n;
        this->trudovi=new Trud [p.n];
        for(int i=0;i<p.n;i++){
            this->trudovi[i]=p.trudovi[i];
        }
    }

public:
    PhDStudent(char *ime="",int indeks=0,int godina=0,int oceni[50]=0,int nOceni=0,Trud *trudovi=new Trud[0],int n=0)
            : Student(ime,indeks,godina,oceni,nOceni){
        this->trudovi=new Trud[n];
        int j=0;
        for(int i=0;i<n;i++){
            if(getGodina()>trudovi[i].getGodina()){
                try{
                    throw Exception();
                }
                catch (Exception & t) {
                    t.showMessage();
                }
            }else{
                this->trudovi[j++]=trudovi[i];
            }
        }
        this->n=j;
    }

    PhDStudent(const PhDStudent & p){
        copy(p);
    }

    PhDStudent & operator=(const PhDStudent & p){
        if(this!=&p){
            delete [] trudovi;
            copy(p);
        }
        return *this;
    }

    ~PhDStudent(){
        delete [] trudovi;
    }

    float rang() const{
        int trudPoeni=0;
        for(int i=0;i<n;i++){
            if(tolower(trudovi[i].getTip())=='c'){
                trudPoeni+=KONF;
            }else{
                trudPoeni+=SPIS;
            }
        }
        return Student::rang()+trudPoeni;
    }

    static void setKonferenciskiTrud(int poen){
        KONF=poen;
    }

    static void setSpisanieTrud(int poen){
        SPIS=poen;
    }

    PhDStudent & operator+=(Trud & t){
        if(t.getGodina()<godina){
            throw Exception();
        }

        Trud *tmp=new Trud[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=trudovi[i];
        }
        tmp[n++]=t;
        delete [] trudovi;
        trudovi=tmp;
        return *this;
    }
};

int PhDStudent::KONF=1;
int PhDStudent::SPIS=3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        int flag=0;
        for(int i=0;i<m;i++){
            if(niza[i]->getIndeks()==indeks){
                PhDStudent *p=dynamic_cast<PhDStudent *>(niza[i]);
                if(p){
                    *dynamic_cast<PhDStudent *>(niza[i])+=t;
                    flag=1;
                }
                if(flag==0){
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        int flag=0;
        for(int i=0;i<m;i++){
            if(niza[i]->getIndeks()==indeks){
                PhDStudent *p=dynamic_cast<PhDStudent *>(niza[i]);
                if(p){
                    *dynamic_cast<PhDStudent *>(niza[i])+=t;
                    flag=1;
                }
                if(flag==0){
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try{
            int flag=0;
            for(int i=0;i<m;i++){
                if(niza[i]->getIndeks()==indeks){
                    PhDStudent *p=dynamic_cast<PhDStudent *>(niza[i]);
                    if(p){
                        *dynamic_cast<PhDStudent *>(niza[i])+=t;
                        flag=1;
                    }
                    if(flag==0){
                        cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    }
                }
            }
        }
        catch (Exception & t) {
            t.showMessage();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setKonferenciskiTrud(conf);
        PhDStudent::setSpisanieTrud(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}