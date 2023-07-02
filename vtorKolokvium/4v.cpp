//
// Created by ivasp on 6/1/2023.
//
#include <cstring>
#include <iostream>
using namespace std;
enum Size{small,big,family};
// Your Code goes here
class Pizza{
protected:
    char name[20];
    char ingredients[100];
    float inPrice;

public:
    Pizza(char *name="",char *ingredients="",float inPrice=0.0){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->inPrice=inPrice;
    }

    virtual float price()=0;

    bool operator<(Pizza &p){
        return price()<p.price();
    }
};

class FlatPizza : public Pizza{
private:
    Size size;

public:
    FlatPizza(char *name="",char *ingredients="",float inPrice=0.0, Size size=small) : Pizza(name,ingredients,inPrice){
        this->size=size;
    }

    float price(){
        if(size==0){
            return inPrice*1.1;
        }else if(size==1){
            return inPrice*1.2;
        }else{
            return inPrice*1.3;
        }
    }

    friend ostream &operator<<(ostream &os, FlatPizza &pizza) {
        os<<pizza.name<<": "<<pizza.ingredients;
        if(pizza.size==0){
            os<<", small - ";
        }else if(pizza.size==1){
            os<<", big - ";
        }else{
            os<<", family - ";
        }
        os<<pizza.price()<<endl;
        return os;
    }
};

class FoldedPizza : public Pizza{
private:
    bool whiteFlour;

public:
    FoldedPizza(char *name="",char *ingredients="",float inPrice=0.0, bool whiteFlour=true) : Pizza(name,ingredients,inPrice){
        this->whiteFlour=whiteFlour;
    }

    void setWhiteFlour(bool wf){
        this->whiteFlour=wf;
    }

    float price(){
        if(whiteFlour){
            return inPrice*1.1;
        }else{
            return inPrice*1.3;
        }
    }

    friend ostream &operator<<(ostream &os, FoldedPizza &pizza) {
        os<<pizza.name<<": "<<pizza.ingredients<<", ";
        if(pizza.whiteFlour){
            os<<"wf - ";
        }else{
            os<<"nwf - ";
        }
        os<<pizza.price()<<endl;
        return os;
    }
};

void expensivePizza(Pizza **p,int n){
    Pizza *max=p[0];
    for(int i=1;i<n;i++){
        if(*max<*p[i]){
            max=p[i];
        }
    }
    FlatPizza *flat=dynamic_cast<FlatPizza *>(max);
    if(flat){
        cout<<*flat;
    }else{
        FoldedPizza *folded=dynamic_cast<FoldedPizza *>(max);
        if(folded){
            cout<<*folded;
        }
    }
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}