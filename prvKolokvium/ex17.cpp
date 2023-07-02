//
// Created by ivasp on 4/11/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Piano{
private:
    char serialN[25];
    float price;
    int year;
public:
    Piano(char serialN[25]="",float price=0.0,int year=2023){
        strcpy(this->serialN,serialN);
        this->price=price;
        this->year=year;
    }
    Piano(const Piano & p){
        strcpy(this->serialN,p.serialN);
        this->price=p.price;
        this->year=p.year;
    }

    void setSerial(char s[25]){
        strcpy(this->serialN,s);
    }

    char *getSerial(){
        return serialN;
    }

    float getPrice(){
        return price;
    }

    bool equals(Piano &p){
        return strcmp(this->serialN,p.serialN)==0;
    }

    void print(){
        cout<<serialN<<" "<<year<<" "<<price<<endl;
    }
};

class PShop{
private:
    char name[50];
    Piano *pianos;
    int n;

    void copy(const PShop & p){
        strcpy(this->name,p.name);
        this->n=p.n;
        this->pianos=new Piano[p.n];
        for(int i=0;i<p.n;i++){
            this->pianos[i]=p.pianos[i];
        }
    }
public:
    PShop(char name[50]=""){
        strcpy(this->name,name);
        this->n=0;
        this->pianos=new Piano [0];
    }
    PShop(const PShop & p){
        copy(p);
    }
    PShop & operator=(const PShop & p){
        if(this!=&p){
            delete [] pianos;
            copy(p);
        }
        return *this;
    }
    ~PShop(){
        delete [] pianos;
    }

    Piano getP(int k){
        return pianos[k];
    }

    double value(){
        double sum=0;
        for(int i=0;i<n;i++){
            sum+=pianos[i].getPrice();
        }
        return sum;
    }

    void add(Piano p){
        Piano *tmp=new Piano[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=pianos[i];
        }
        tmp[n++]=p;
        delete [] pianos;
        pianos=tmp;
    }

    void sell(Piano p){
        int index=-1;
        for(int i=0;i<n;i++){
            if(pianos[i].equals(p)){
                index=i;
                break;
            }
        }

        if(index!=-1){
            Piano *tmp=new Piano [n-1];
            int j=0;
            for(int i=0;i<n;i++){
                if(i!=index){
                    tmp[j++]=pianos[i];
                }
            }
            n=j;
            delete [] pianos;
            pianos=tmp;
        }
    }

    void print(){
        cout<<name<<endl;
        for(int i=0;i<n;i++){
            cout<<i+1<<". ";
            pianos[i].print();
        }
    }
};

int main() {

    int n;
    cin >> n;


    if(n == 1) {
        cout << "---Class Piano---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p(serialNo,price,pYear);
        p.print();
    } else if(n == 2) {
        cout << "---Equals---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        Piano p2(p1);
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
        p2.setSerial("12344");
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
    }  else if(n == 3) {
        cout << "---Class PShop---" << endl;
        char name[50];
        cin >> name;
        PShop ps(name);
        ps.print();
    } else if(n == 4) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();
    } else if(n == 5) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

    } else if(n == 6) {
        cout << "---value method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        cout<<"Total price: "<<ps.value()<<endl;
    }
    else if(n == 7) {
        cout << "---sell method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        int d;
        cin>>d;
        Piano p1(ps.getP(d).getSerial());
        ps.sell(p1);
        ps.print();
    } else if(n == 8) {
        cout << "---Full Test---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();

        cout<<endl;

        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

        cout<<endl;

        cout<<"Total price: "<<ps.value()<<endl;

        cout<<endl;

        int d;
        cin>>d;
        Piano p3(ps.getP(d).getSerial());
        ps.sell(p3);
        ps.print();

        cout<<"Total price: "<<ps.value()<<endl;
    }
    return 0;
}