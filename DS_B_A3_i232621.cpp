#include <iostream>
using namespace std;
//Simple Class for game status
class Games_played_class{
    public:
    string gameID;
    float hours_played;
    int achievements_unlock;
    Games_played_class(string id,float h,int ach):gameID(id),hours_played(h),achievements_unlock(ach){}
    
};
//Players Node : Will be used in players Database
class Player{
    public:
    string name;
    string playerID;
    string phone_number;
    string email;
    string password;
    Games_played_class Logs;
    Player* left;
    Player* right;
    Player(string n,string id,string ph,string em,string pass,Games_played_class log):name(n),playerID(id),phone_number(ph),email(em),password(pass),Logs(log),left(NULL),right(NULL){}
};
//Games Node : Will be used in Games Database
class Game{
    public:
    string gameID;
    string Name;
    string Developer;
    string Publisher;
    float File_size_in_GB;
    int downloads;
    Game* left;
    Game* right;
    Game(string id,string n,string dev,string pub,float file,int down):gameID(id),Name(n),Developer(dev),Publisher(pub),File_size_in_GB(file),downloads(down),left(NULL),right(NULL){}
};



class Players_DataBase{
    public:
    Player* root;  
    Players_DataBase():root(NULL){}

    void insert(Player* player){

    }
    void Loading_Data_Player(string& fileName,int seed, int limit)
    {

    }

};
class Games_DataBase{
    public:
    Game* root;
    Games_DataBase():root(NULL){}
     
    void insert(Game* player){

    }
    void Loading_Data_Game(string& fileName,int seed, int limit)
    {

    }
};
int main()
{
    int seed = 232621;
    int thresHold = (seed%100)*10 + 100;
    Players_DataBase PDM;
    Games_DataBase  GDM;
    return 0;
}