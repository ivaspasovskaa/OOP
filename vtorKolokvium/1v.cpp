//
// Created by ivasp on 5/30/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Book{
protected:
    char isbn[20], title[50], author[30];
    float price;

    void copy(const Book & b){
        strcpy(this->isbn,b.isbn);
        strcpy(this->title,b.title);
        strcpy(this->author,b.author);
        this->price=b.price;
    }
public:
    Book(char *isbn="", char *title="", char *author="",float price=0.0){
        strcpy(this->isbn,isbn);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }

    virtual float bookPrice()=0;

    bool operator>(const Book &b1) const {
        return price>b1.price;
    }

    friend ostream &operator<<(ostream &os, Book &book) {
        os<<book.isbn<< ": "<<book.title<<", "<<book.author<<" "<<book.bookPrice()<<endl;
        return os;
    }
};

class OnlineBook : public Book{
private:
    char *url;
    int size;

    void copy(const OnlineBook & o){
        Book::copy(o);
        this->url=new char [strlen(o.url)+1];
        strcpy(this->url,o.url);
        this->size=o.size;
    }

public:
    OnlineBook(char *isbn="", char *title="", char *author="",float price=0.0,char *url="",int size=0) : Book(isbn,title,author,price){
        this->url=new char [strlen(url)+1];
        strcpy(this->url,url);
        this->size=size;
    }

    OnlineBook(const OnlineBook & o){
        copy(o);
    }

    OnlineBook & operator=(const OnlineBook & o){
        if(this!=&o){
            delete [] url;
            copy(o);
        }
        return *this;
    }

    ~OnlineBook(){
        delete [] url;
    }

    float bookPrice(){
        if(size>20){
            return price*1.2;
        }else{
            return price;
        }
    }

    void setISBN(char *isbn){
        strcpy(this->isbn,isbn);
    }
};

class PrintBook : public Book{
private:
    float weight;
    bool inStock;

public:
    PrintBook(char *isbn="", char *title="", char *author="",float price=0.0,float weight=0.0,bool inStock=false) : Book(isbn,title,author,price){
        this->weight=weight;
        this->inStock=inStock;
    }

    float bookPrice(){
        if(weight>0.7){
            return price*1.15;
        }else{
            return price;
        }
    }
};

void mostExpensiveBook(Book **books, int n){
    int online=0,print=0;
    Book *maxBook=books[0];
    for(int i=0;i<n;i++){
        if(*books[i]>*maxBook){
            maxBook=books[i];
        }

        Book *onlineBook=dynamic_cast<OnlineBook *>(books[i]);
        if(onlineBook){
            online++;
        }else{
            print++;
        }
    }

    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<print<<endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*maxBook<<endl;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}