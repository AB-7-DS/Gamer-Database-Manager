#include <iostream>
using namespace std;

class Games_played_class{
    string gameID;
    float hours_played;
    int achievements_unlock;
};

class Player{
    string name;
    string playerID;
    string phone_number;
    string email;
    string password;
    Games_played_class Logs;
};
class Game{
    string gameID;
    string Name;
    string Developer;
    string Publisher;
    float File_size_in_GB;
    int downloads;
};