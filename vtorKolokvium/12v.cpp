//
// Created by ivasp on 6/4/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

enum tip{
    smartfon,laptop
};

class InvalidProductionDate{
public:
    void showMessage(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class Device{
private:
    char ime[100];
    tip tipDevice;
    int godina;
    static float POTREBNI_CASOVI;

public:
    Device(char *ime="",tip tipDevice=smartfon,int godina=0){
        strcpy(this->ime,ime);
        this->tipDevice=tipDevice;
        this->godina=godina;
    }

    static void setPocetniCasovi(float C){
        POTREBNI_CASOVI=C;
    }

    float casoviZaProverka() const{
        float casovi=POTREBNI_CASOVI;
        if(godina>2015){
            casovi+=2;
        }
        if(tipDevice==laptop){
            casovi+=2;
        }
        return casovi;
    }

    friend ostream & operator<<(ostream & out,Device & d){
        out<<d.ime<<endl;
        if(d.tipDevice==smartfon){
            out<<"Mobilen ";
        }else{
            out<<"Laptop ";
        }
        out<<d.casoviZaProverka()<<endl;
    }

    int getGodina(){
        return godina;
    }
};

float Device::POTREBNI_CASOVI=1;

class MobileServis{
private:
    char adresa[100];
    Device *devices;
    int n;

    void copy(const MobileServis & m){
        strcpy(this->adresa,m.adresa);
        this->n=m.n;
        this->devices=new Device [m.n];
        for(int i=0;i<m.n;i++){
            this->devices[i]=m.devices[i];
        }
    }

public:
    MobileServis(char *adresa=""){
        strcpy(this->adresa,adresa);
        this->n=0;
        this->devices=new Device[0];
    }

    MobileServis(const MobileServis & m){
        copy(m);
    }

    MobileServis & operator=(const MobileServis & m){
        if(this!=&m){
            delete [] devices;
            copy(m);
        }
        return *this;
    }

    ~MobileServis(){
        delete [] devices;
    }

    MobileServis & operator+=(Device & d){
        if(d.getGodina()<2000 || d.getGodina()>2019){
            throw InvalidProductionDate();
        }

        Device *tmp=new Device[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=devices[i];
        }
        tmp[n++]=d;
        delete [] devices;
        devices=tmp;
        return *this;
    }

    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<n;i++){
            cout<<devices[i];
        }
    }
};

int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate & e) {
                e.showMessage();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate & e) {
                e.showMessage();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate & e) {
                e.showMessage();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}