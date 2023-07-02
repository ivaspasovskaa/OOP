//
// Created by ivasp on 6/4/2023.
//
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class SMS{
protected:
    float cena;
    char tel[20];
    const static float DANOK;
public:
    SMS(char *tel="",float cena=0){
        strcpy(this->tel,tel);
        this->cena=cena;
    }

    virtual float SMS_cena()=0;

    friend ostream &operator<<(ostream & out, SMS &s){
        return out<<"Tel: "<<s.tel<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
    }
};

class RegularSMS : public SMS{
public:
    char msg[1000];
    bool roam;
    static float REGULAR_DANOK;
public:
    RegularSMS(char *tel="",float cena=0, char *msg="",bool roam=false) : SMS(tel,cena){
        strcpy(this->msg,msg);
        this->roam=roam;
    }

    float SMS_cena(){
        float total=cena;
        if(roam){
            total*=(1+REGULAR_DANOK/100);
        }else{
            total*=(1+SMS::DANOK);
        }
        if(strlen(msg)>160){
            total*=(1+strlen(msg)/160);
        }
        return total;
    }

    static void set_rProcent(float p){
        REGULAR_DANOK=p;
    }
};

class SpecialSMS : public SMS{
public:
    bool hum;
    static float SPECIAL_DANOK;
public:
    SpecialSMS(char *tel="",float cena=0,bool hum=false) : SMS(tel,cena){
        this->hum=hum;
    }

    float SMS_cena(){
        if(!hum){
            cena*=(1+SPECIAL_DANOK/100);
        }
        return cena;
    }

    static void set_sProcent(float p){
        SPECIAL_DANOK=p;
    }
};

const float SMS::DANOK=0.18;
float RegularSMS::REGULAR_DANOK=300;
float SpecialSMS::SPECIAL_DANOK=150;

void vkupno_SMS(SMS** poraka, int n){
    int regularCounter=0,specialCounter=0;
    float regularVkupno=0,specialVkupno=0;
    for(int i=0;i<n;i++){
        RegularSMS *r=dynamic_cast<RegularSMS *>(poraka[i]);
        if(r){
            regularVkupno+=r->SMS_cena();
            regularCounter++;
        }else{
            specialVkupno+=poraka[i]->SMS_cena();
            specialCounter++;
        }
    }
    cout<<"Vkupno ima "<<regularCounter<<" regularni SMS poraki i nivnata cena e: "<<regularVkupno<<endl;
    cout<<"Vkupno ima "<<specialCounter<<" specijalni SMS poraki i nivnata cena e: "<<specialVkupno<<endl;
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}