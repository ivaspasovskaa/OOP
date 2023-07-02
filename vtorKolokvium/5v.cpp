//
// Created by ivasp on 6/1/2023.
//
#include <cstring>
#include <iostream>
#define MAX 50
using namespace std;
enum typeC{standard,loyal,vip};

class UserExistsException{
public:
    UserExistsException(){}

    void showMessage(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

class Customer{
private:
    char name[50];
    char email[50];
    typeC tC;
    static int BASIC_DISCOUNT;
    const static int DISCOUNT=20;
    int numProducts;

public:
    Customer(const char *name="",const char *email="",typeC tc=standard,int numProducts=0){
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->tC=tc;
        this->numProducts=numProducts;
    }

    friend ostream &operator<<(ostream &os, const Customer &customer) {
        os<<customer.name<<endl;
        os<<customer.email<<endl;
        os<<customer.numProducts<<endl;
        if(customer.tC==standard){
            os<<"standard "<<0<<endl;
        }else if(customer.tC==loyal){
            os<<"loyal "<<Customer::BASIC_DISCOUNT<<endl;
        }else{
            os<<"vip "<<Customer::BASIC_DISCOUNT+Customer::DISCOUNT<<endl;
        }
        return os;
    }

    static void setDiscount1(int d){
        BASIC_DISCOUNT=d;
    }

    const char *getEmail() const{
        return email;
    }

    typeC getType(){
        return tC;
    }

    void setType(typeC t){
        this->tC=t;
    }

    int getNumProducts(){
        return numProducts;
    }
};

int Customer::BASIC_DISCOUNT=10;

class FINKI_bookstore{
private:
    int n;
    Customer *customers;

public:
    FINKI_bookstore(){
        this->n=0;
        this->customers=new Customer[0];
    }

//    FINKI_bookstore(const FINKI_bookstore & f){
//        this->n=f.n;
//        this->customers=new Customer[f.n];
//        for(int i=0;i<f.n;i++){
//            this->customers[i]=f.customers[i];
//        }
//    }
//
//    FINKI_bookstore & operator=(FINKI_bookstore f){
//        if(this!=&f){
//            delete [] customers;
//            this->n=f.n;
//            this->customers=new Customer[f.n];
//            for(int i=0;i<f.n;i++){
//                this->customers[i]=f.customers[i];
//            }
//        }
//        return *this;
//    }

    friend ostream &operator<<(ostream &os, FINKI_bookstore &bookstore) {
        for(int i=0;i<bookstore.n;i++){
            os<<bookstore.customers[i];
        }
        return os;
    }

    FINKI_bookstore &operator+=(const Customer &c){
        for(int i=0;i<n;i++){
            if(strcmp(customers[i].getEmail(),c.getEmail())==0){
                throw UserExistsException();
            }
        }
        Customer *tmp=new Customer [n+1];
        for(int i=0;i<n;i++){
            tmp[i]=customers[i];
        }
        tmp[n++]=c;
        delete [] customers;
        customers=tmp;
        return *this;
    }

    void update(){
        for(int i=0;i<n;i++){
            if(customers[i].getType()==standard && customers[i].getNumProducts()>5){
                customers[i].setType(loyal);
                continue;
            }
            if(customers[i].getType()==loyal && customers[i].getNumProducts()>10){
                customers[i].setType(vip);
            }
        }
    }

    void setCustomers(Customer *customers,int m){
        delete [] this->customers;
        this->n=m;
        this->customers=new Customer[m];
        for(int i=0;i<m;i++){
            this->customers[i]=customers[i];
        }
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        }
        catch (UserExistsException &e){
            e.showMessage();
        }

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);

        try{
            fc+=c;
        }
        catch (UserExistsException &e){
            e.showMessage();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}