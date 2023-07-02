//
// Created by ivasp on 4/8/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class List{
private:
    int *lista;
    int n;

    void copy(const List & l){
        this->n=l.n;
        this->lista=new int [l.n];
        for(int i=0;i<l.n;i++){
            this->lista[i]=l.lista[i];
        }
    }

public:
    List(){ }
    List(int *lista,int n){
        this->n=n;
        this->lista=new int [n];
        for(int i=0;i<n;i++){
            this->lista[i]=lista[i];
        }
    }

    List(const List & l){
        copy(l);
    }

    ~List(){
        delete [] lista;
    }

    List & operator= (const List & l){
        if(this!=&l){
            delete [] lista;
            copy(l);
        }
        return *this;
    }

    int getN(){
        return n;
    }

    int sum(){
        int s=0;
        for(int i=0;i<n;i++){
            s+=lista[i];
        }
        return s;
    }

    double average(){
        return (double)sum()/n;
    }

    void pecati(){
        cout<<n<<": ";
        for(int i=0;i<n;i++){
            cout<<lista[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }

};

class ListContainer{
private:
    List *listi;
    int brListi;
    int obidi;

    void copy(const ListContainer &lc){
        this->brListi=lc.brListi;
        this->listi=new List [this->brListi];
        for(int i=0;i<this->brListi;i++){
            this->listi[i]=lc.listi[i];
        }
        this->obidi=lc.obidi;
    }
public:
    ListContainer(int brListi=0){
        this->brListi=brListi;
        this->listi=new List [this->brListi];
        this->obidi=0;
    }
    ListContainer(const ListContainer &lc){
        copy(lc);
    }

    ~ListContainer(){
        delete [] listi;
    }

    ListContainer & operator= (const ListContainer & lc){
        if(this!=&lc){
            delete [] listi;
            copy(lc);
        }
        return *this;
    }

    void addNewList(List l){
        obidi++;
        for(int i=0;i<brListi;i++){
            if(listi[i].sum()==l.sum()){
                return;
            }
        }
        List *tmp=new List[brListi+1];
        for(int i=0;i<brListi;i++){
            tmp[i]=listi[i];
        }
        tmp[brListi++]=l;
        delete [] listi;
        listi=tmp;
    }


    int sum(){
        int s=0;
        for(int i=0;i<brListi;i++){
            s+=listi[i].sum();
        }
        return s;
    }

    double average(){
        int br=0;
        for(int i=0;i<brListi;i++){
            br+=listi[i].getN();
        }
        return sum()/(double)br;
    }

    void print(){
        if(brListi==0){
            cout<<"The list is empty"<<endl;
        }else{
            for(int i=0;i<brListi;i++){
                cout<<"List number: "<<i+1<<" List info: ";
                listi[i].pecati();
            }
            cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<brListi<<" Failed attempts: "<<obidi-brListi<<endl;
        }
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}