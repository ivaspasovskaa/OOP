//
// Created by ivasp on 6/5/2023.
//
#include<iostream>
#include<string.h>
using namespace std;

class BadInputException{
public:
    void showMessage(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA=6;

    void copy(const StudentKurs & s){
        strcpy(this->ime,s.ime);
        this->ocenka=s.ocenka;
        this->daliUsno=s.daliUsno;
    }
public:
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
    //дополни ја класата
    StudentKurs(const StudentKurs & s){
        copy(s);
    }

    StudentKurs & operator=(const StudentKurs & s){
        if(this!=&s){
            copy(s);
        }
        return *this;
    }

    ~StudentKurs(){}

    friend ostream & operator<<(ostream & out,const StudentKurs & s){
        return out<<s.ime<<" --- "<<s.getOcenka();
    }

    virtual int getOcenka() const{
        return ocenka;
    }

    static void setMAX(int M){
        MAX=M;
    }

    bool getDaliUsno(){
        return daliUsno;
    }

    char *getIme(){
        return ime;
    }

    static int getMINOCENKA(){
        return MINOCENKA;
    }
};

int StudentKurs::MAX=10;

//вметни го кодот за StudentKursUsno
class StudentKursUsno : public StudentKurs{
private:
    char *opisna;

    void copy(const StudentKursUsno & s){
        StudentKurs::copy(s);
        this->opisna=new char [strlen(s.opisna)+1];
        strcpy(this->opisna,s.opisna);
    }
public:
    StudentKursUsno(char* ime,int finalenIspit) : StudentKurs(ime,finalenIspit){
        this->daliUsno=true;
        this->opisna=new char [1];
    }

    StudentKursUsno(const StudentKursUsno & s) : StudentKurs(s){
        copy(s);
    }

    ~StudentKursUsno(){
        delete [] opisna;
    }

    friend ostream & operator<<(ostream & out,const StudentKursUsno & s){
        return out<<s.ime<<" --- "<<s.getOcenka();
    }

    int getOcenka() const{
        int kursOcenka=ocenka;
        if(strcmp(opisna,"odlicen")==0){
            kursOcenka+=2;
        }else if(strcmp(opisna,"dobro")==0){
            kursOcenka+=1;
        }else if(strcmp(opisna,"losho")==0){
            kursOcenka+=-1;
        }else{
            return ocenka;
        }
        if(kursOcenka<MAX){
            return kursOcenka;
        } else{
            return MAX;
        }
    }

    StudentKursUsno & operator+=(char *o){
        for(int i=0;i<strlen(o);i++){
            if(!isalpha(o[i])){
                throw BadInputException();
            }
        }

        delete [] opisna;
        this->opisna=new char [10];
        strcpy(this->opisna,o);
        return *this;
    }
};


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0;i<broj;i++){
            if(studenti[i]->getOcenka()>=StudentKurs::getMINOCENKA()){
                cout<<*studenti[i]<<endl;
            }
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka){
        for(int i=0;i<broj;i++){
            if(strcmp(studenti[i]->getIme(),ime)==0 && studenti[i]->getDaliUsno()){
                *dynamic_cast<StudentKursUsno *>(studenti[i])+=opisnaOcenka;
            }
        }
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try{
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }
        catch (BadInputException & e) {
            e.showMessage();
            char nova[10];
            int k=0;
            for(int j=0;j< strlen(opisna);j++){
                if(isalpha(opisna[j])){
                    nova[k++]=opisna[j];
                }
                nova[k]='\0';
                programiranje.postaviOpisnaOcenka(ime,nova);
            }
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}