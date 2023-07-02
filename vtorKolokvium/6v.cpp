//
// Created by ivasp on 6/1/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Game{
protected:
    char game_name[100];
    float game_price;
    bool game_on_sale;

public:
    Game(char *name="",float price=0.0,bool onSale=false){
        strcpy(this->game_name,name);
        this->game_price=price;
        this->game_on_sale=onSale;
    }

    friend ostream &operator<<(ostream &os, const Game &game) {
        os << "Game: " << game.game_name << ", regular price: $" << game.game_price;
        if(game.game_on_sale){
            os<<", bought on sale";
        }
        return os;
    }

    friend istream &operator>>(istream &os,Game &game) {
        os.get();
        os.getline(game.game_name,100);
        os>>game.game_price>>game.game_on_sale;
        return os;
    }

    bool operator==(Game &g){
        return strcmp(game_name,g.game_name)==0;
    }

    virtual float getPrice(){
        if(game_on_sale){
            return game_price*0.3;
        }else{
            return game_price;
        }
    }
};

class SubscriptionGame: public Game{
private:
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

public:
    SubscriptionGame(char *name="",float price=0.0,bool onSale=false, float monthly=0.0,int month=0,int year=0) : Game(name,price,onSale){
        this->sub_game_monthly_fee=monthly;
        this->sub_game_month=month;
        this->sub_game_year=year;
    }

    friend ostream &operator<<(ostream &os, SubscriptionGame &game) {
        Game *tmp=dynamic_cast<Game *>(&game);
        os<<*tmp;
        os<<", monthly fee: $"<<game.sub_game_monthly_fee<<", purchased: "<<game.sub_game_month<<"-"<<game.sub_game_year<<endl;
        return os;
    }

    friend istream &operator>>(istream &os,SubscriptionGame &game) {
        os.get();
        os.getline(game.game_name,100);
        os>>game.game_price>>game.game_on_sale>>game.sub_game_monthly_fee>>game.sub_game_month>>game.sub_game_year;
        return os;
    }

    float getPrice(){
        float price=Game::getPrice();
        int months=0;
        if(sub_game_year<2018){
            months=(12-sub_game_month)+(2017-sub_game_year)*12+5;
        }else{
            months=5-sub_game_month;
        }
        price+=months*sub_game_monthly_fee;
        return price;
    }

};

class ExistingGame{
public:
    ExistingGame(){}

    void message(){
        cout<<"The game is already in the collection"<<endl;
    }
};

class User{
private:
    char username[100];
    int n;
    Game **games;

public:
    User(char *name="",int n=0){
        strcpy(this->username,name);
        this->n=n;
        this->games=new Game * [0];
    }

    User(const User & u){
        strcpy(this->username,u.username);
        this->n=u.n;
        this->games=new Game * [u.n];
        for(int i=0;i<u.n;i++){
            this->games[i]=u.games[i];
        }
    }

    User &operator=(const User & u){
        if(this!=&u){
            delete [] games;
            strcpy(this->username,u.username);
            this->n=u.n;
            this->games=new Game * [u.n];
            for(int i=0;i<u.n;i++){
                this->games[i]=u.games[i];
            }
        }
        return *this;
    }

    ~User(){
        delete [] games;
    }

    User &operator+=(Game & g){
        Game **tmp=new Game*[n+1];
        for(int i=0;i<this->n;i++){
            if(*(this->games[i])==g){
                throw ExistingGame();
            }
        }
        for(int i=0;i<this->n;i++){
            tmp[i]=games[i];
        }
        SubscriptionGame *s=dynamic_cast<SubscriptionGame *>(&g);
        if(s){
            tmp[n++]=new SubscriptionGame(*s);
        }else{
            tmp[n++]=new Game(g);
        }
        delete [] this->games;
        this->games=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const User &u) {
        os<<"\nUser: "<<u.username<<endl;
        for(int i=0;i<u.n;i++){
            Game *g=u.games[i];
            SubscriptionGame *s=dynamic_cast<SubscriptionGame*>(g);
            if(s){
                cout<<"- "<<(*s)<<endl;
            }else{
                cout<<"- "<<(*g)<<endl;
            }
        }
        return os;
    }

    float total_spent(){
        float total=0.0;
        for(int i=0;i<n;i++){
            total+=games[i]->getPrice();
        }
        return total;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}