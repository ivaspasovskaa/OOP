//
// Created by ivasp on 6/2/2023.
//
#include<iostream>
#include<cstring>
using namespace std;

class Koncert{
protected:
    char naziv[100], lokacija[100];
    float cenaBilet;
    static float POPUST;

public:
    Koncert(char *naziv="", char *lokacija="",float cenaBilet=0.0){
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet=cenaBilet;
    }

    Koncert(const Koncert & k){
        strcpy(this->naziv,k.naziv);
        strcpy(this->lokacija,k.lokacija);
        this->cenaBilet=k.cenaBilet;
    }

    char *getNaziv(){
        return naziv;
    }

    void setSezonskiPopust(float s){
        POPUST=s;
    }

    float getSezonskiPopust(){
        return POPUST;
    }

    virtual float cena(){
        return cenaBilet*POPUST;
    }
};

float Koncert::POPUST=0.8;

class ElektronskiKoncert : public Koncert{
private:
    char *imeDJ;
    float casovi;
    bool dnevna;

public:
    ElektronskiKoncert(char *naziv="", char *lokacija="",float cenaBilet=0.0, char *imeDJ="",float casovi=0.0,bool dnevna=false) : Koncert(naziv,lokacija,cenaBilet){
        this->imeDJ=new char [strlen(imeDJ)+1];
        strcpy(this->imeDJ,imeDJ);
        this->casovi=casovi;
        this->dnevna=dnevna;
    }

    ElektronskiKoncert(const ElektronskiKoncert & e) : Koncert(e){
        this->imeDJ=new char [strlen(e.imeDJ)+1];
        strcpy(this->imeDJ,e.imeDJ);
        this->casovi=e.casovi;
        this->dnevna=e.dnevna;
    }

    float cena(){
        if(casovi>7 && dnevna){
            return Koncert::cena()+310;
        }else if(casovi>7 && !dnevna){
            return Koncert::cena()+460;
        }else if(casovi>5 && dnevna){
            return Koncert::cena()+100;
        }else if(casovi>5 && !dnevna){
            return Koncert::cena()+250;
        }else{
            return Koncert::cena();
        }
    }
};

void najskapKoncert(Koncert ** koncerti, int n){
    Koncert *najskap=koncerti[0];
    for(int i=0;i<n;i++){
        if(najskap->cena()<koncerti[i]->cena()){
            najskap=koncerti[i];
        }
    }
    cout<<"Najskap koncert: "<<najskap->getNaziv()<<" "<<najskap->cena()<<endl;

    int counter=0;
    for(int i=0;i<n;i++){
        ElektronskiKoncert *e=dynamic_cast<ElektronskiKoncert *>(koncerti[i]);;
        if(e){
            counter++;
        }
    }
    cout<<"Elektronski koncerti: "<<counter<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    if(elektronski){
        for(int i=0;i<n;i++){
            ElektronskiKoncert *e=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if(e){
                if(strcmp(naziv,koncerti[i]->getNaziv())==0){
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                    return true;
                }
            }
        }
    }else{
        for(int i=0;i<n;i++){
            if(strcmp(naziv,koncerti[i]->getNaziv())==0){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}