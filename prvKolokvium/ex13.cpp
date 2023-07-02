//
// Created by ivasp on 4/10/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Pasta{
private:
    char *name;
    float price;
    int discount;
    int calories;

    void copy(const Pasta & p){
        this->name=new char [strlen(p.name)+1];
        strcpy(this->name,p.name);
        this->price=p.price;
        this->calories=p.calories;
        this->discount=p.discount;
    }

public:
    Pasta(char *name="",float price=0.0,int calories=0){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->price=price;
        this->calories=calories;
        this->discount=0;
    }
    Pasta(const Pasta & p){
        copy(p);
    }
    Pasta & operator=(const Pasta & p){
        if(this!=&p){
            delete [] name;
            copy(p);
        }
        return *this;
    }
    ~Pasta(){
        delete [] name;
    }

    void setName(char* n){
        delete [] name;
        this->name=new char [strlen(n)+1];
        strcpy(this->name,n);
    }

    void setDiscount(int d){
        if(d>=0 && d<=100){
            this->discount=d;
        }
    }

    void print(){
        cout<<name<<" "<<calories<<" "<<price;
        if (discount>0) {
             cout<<" ("<<price*(100-discount)/100<<")";
        }
    }

    void dby5(){
        discount-=5;
    }

    Pasta light(int c){
        char *oldName=name;
        char *newName=new char [strlen(oldName)+6];
        strcat(newName,oldName);
        strcat(newName,"Light");
        float newPrice=price*0.8;
        int newCalories=calories-c;
        Pasta p(newName,newPrice,newCalories);
        p.discount=0;
        return p;
    }
};

class ItalianRestaurant{
private:
    char name[50];
    Pasta *pasta;
    int n;

    void copy(const ItalianRestaurant &ir){
        strcpy(this->name,ir.name);
        this->n=ir.n;
        this->pasta=new Pasta [ir.n];
        for(int i=0;i<ir.n;i++){
            this->pasta[i]=ir.pasta[i];
        }
    }

public:
    ItalianRestaurant(char *name=""){
        strcpy(this->name,name);
        this->n=0;
        this->pasta=new Pasta [0];
    }

    ItalianRestaurant(const ItalianRestaurant & ir){
        copy(ir);
    }

    ItalianRestaurant & operator=(const ItalianRestaurant & ir){
        if(this!=&ir){
            delete [] pasta;
            copy(ir);
        }
        return *this;
    }

    ~ItalianRestaurant(){
        delete [] pasta;
    }

    void add(Pasta & p){
        Pasta *tmp=new Pasta[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=pasta[i];
        }
        tmp[n++]=p;
        delete [] pasta;
        pasta=tmp;
    }

    void print(){
        cout<<name<<endl;
        for(int i=0;i<n;i++){
            pasta[i].print();
            cout<<endl;
        }
    }

    void setPasta(int i, Pasta & p){
        pasta[i]=p;
    }
};

int main() {
    char name[100];
    float price;
    int discount;
    int calories;

    int testCase;

    cin >> testCase;

    if(testCase == 1) {
        cout << "====== TESTING Pasta CLASS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.setDiscount(discount);
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        Pasta c2(name, price, calories);
        c2.setDiscount(discount);
        cout << "Print" << endl;
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "Decrease by 5" << endl;
        c1.dby5();
        c1.print();
        cout << endl;
        cout << "Calories" << endl;
        int ca;
        cin >> ca;
        Pasta c3 = c1.light(ca);
        c3.print();
        cout << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING Pasta CONSTRUCTORS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.print();
        cout << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        Pasta c2(c1);
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "OPERATOR =" << endl;
        c1 = c2;
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;

    } else if(testCase == 3) {
        cout << "====== TESTING Italian Restaurant ======" << endl;
        char csName[50];
        cin >> csName;
        cout << "CONSTRUCTOR" << endl;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        cout << "Add" << endl;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        cs.print();
        cout << endl;

    } else if(testCase == 4) {
        cout << "====== TESTING Italian Restaurant CONSTRUCTORS ======" << endl;
        char csName[50];
        cin >> csName;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        Pasta x("Funghi", 260, 275);
        ItalianRestaurant cp = cs;
        cs.setPasta(0, x);
        cs.print();
        cout << endl;
        cp.print();
        cout << endl;
    }


    return 0;
}
