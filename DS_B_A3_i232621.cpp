#include <iostream>
#include<fstream>
using namespace std;
//Simple Node Class for game status Link List
class Games_played_class{
    public:
    string gameID;
    float hours_played;
    int achievements_unlock;
    Games_played_class* next;
    Games_played_class(string &id,float h,int ach):gameID(id),hours_played(h),achievements_unlock(ach),next(NULL){}
    
};
//Players Node : Will be used in players Database
class Player{
    public:
    string name;
    string playerID;
    string phone_number;
    string email;
    string password;
    Games_played_class* GP_head;
    Player* left;
    Player* right;
    Player(string &n,string &id,string &ph,string &em,string &pass,Games_played_class* log):name(n),playerID(id),phone_number(ph),email(em),password(pass),GP_head(log),left(NULL),right(NULL){}
    void addGameLog(Games_played_class* log)
    {
        log->next=  GP_head;
        GP_head=log;
    }
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
    Game(string &id,string &n,string &dev,string &pub,float file,int down):gameID(id),Name(n),Developer(dev),Publisher(pub),File_size_in_GB(file),downloads(down),left(NULL),right(NULL){}
};



class Players_DataBase{
    public:
    Player* root;  
    Players_DataBase():root(NULL){}

    void insertPlayer(Player* player){

    }
    void Loading_Data_Player(string& fileName,int seed, int limit)
    {
        srand(seed);
       ifstream file(fileName);
       string line;

       while(getline(file,line))
       {
         if(rand()% 1000 < limit) continue; 

         int pos = 0;
         string Player_id,name,phone,email,password,game_id;
         float hours=0;
         int achievement=0;

         pos = line.find(',');
         Player_id=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
         name=line.substr(0,pos);
         line.erase(0,pos + 1);

        pos = line.find(',');
         phone=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
         email=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
         password=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
        game_id=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
         hours= stof(line.substr(0, pos));
         line.erase(0,pos + 1);

        achievement = stoi(line);
        
        Games_played_class* log = new Games_played_class(game_id,hours,achievement);
        Player* player = new Player(Player_id,name,phone,email,password,log);

        insertPlayer(player);
       }
       file.close();

    }

};
class Games_DataBase{
    public:
    Game* root;
    Games_DataBase():root(NULL){}
     
    void insertGame(Game* player){


    }
    void Loading_Data_Game(string& fileName,int seed, int limit)
    {
       srand(seed);
       ifstream file(fileName);
       string line;

       while(getline(file,line))
       {
         if(rand()% 1000 < limit) continue; 

         int pos = 0;
         string game_id,name,dev,publisher;
         float filesize=0;
         int  downloads=0;

         pos = line.find(',');
        game_id=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
         name=line.substr(0,pos);
         line.erase(0,pos + 1);

        pos = line.find(',');
         dev=line.substr(0,pos);
         line.erase(0,pos + 1);

         pos = line.find(',');
         publisher=line.substr(0,pos);
         line.erase(0,pos + 1);


         pos = line.find(',');
         filesize= stof(line.substr(0, pos));
         line.erase(0,pos + 1);

        downloads = stoi(line);
        
       
        Game* game = new Game(game_id,name,dev,publisher,filesize,downloads);

        insertGame(game);
       }
       file.close();
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