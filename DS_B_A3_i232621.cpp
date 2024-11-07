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
          Games_played_class* current = GP_head;
        while (current) {
            if (current->gameID== log->gameID) {
                cout << "Error: Game with ID " << log->gameID << " already exists for player " << playerID << "." << endl;
                delete log;
                return;
            }
            current = current->next;
        }
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
    Player* search(Player* node, const string& player_id) const {
        if (!node || node->playerID == player_id) return node;
        if (player_id < node->playerID) return search(node->left, player_id);
        else return search(node->right, player_id);
    }
    void insertPlayer(Player* player){
            if (search(root, player->playerID)) {
            cout << "Error: Player with ID " << player->playerID << " already exists." << endl;
            delete player;
            
        }
            if(root == NULL)
            {
                root = player;      
                return;
            }
            Player* current= root;
            Player* parent = NULL;
            while(current)
            {
                parent=current;
                if(player->playerID<current->playerID)
                {
                  current=current->left;
                  if(!current) parent->left = player;
                }else{
                  current = current->right;
                  if(!current) parent->right = player;
                }
            }
    }
    void Loading_Data_Player(const string& fileName,int seed, int limit)
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
        Player* player = new Player(name,Player_id,phone,email,password,log);

        insertPlayer(player);
       }
       file.close();

    }
   void printInOrder() const {
        printInOrderRecursive(root);
    }

    void printInOrderRecursive(Player* node) const {
        if (node == nullptr) return;

        printInOrderRecursive(node->left);

        cout << "Player ID: " << node->playerID << ", Name: " << node->name << endl;
        cout << "Phone: " << node->phone_number << ", Email: " << node->email << endl;
        cout << "Password: " << node->password << endl;
        cout << "  Games Played:" << endl;

        Games_played_class* game = node->GP_head;
        while (game != nullptr) {
            cout << "    Game ID: " << game->gameID
                 << ", Hours Played: " << game->hours_played
                 << ", Achievements Unlocked: " << game->achievements_unlock << endl;
            game = game->next;
        }

        printInOrderRecursive(node->right);
    }
      Player* deletePlayer(Player* node, const string& player_id) {
        if (node == NULL) return node;

        if (player_id < node->playerID) {
            node->left = deletePlayer(node->left, player_id);
        } else if (player_id > node->playerID) {
            node->right = deletePlayer(node->right, player_id);
        } else {
           
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
          
            else if (node->left == NULL) {
                Player* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                Player* temp = node->left;
                delete node;
                return temp;
            }
           
            else {
                Player* temp = findMin(node->right);  
                node->playerID = temp->playerID;
                node->name = temp->name;
                node->phone_number = temp->phone_number;
                node->email = temp->email;
                node->password = temp->password;
                node->GP_head = temp->GP_head;
                node->right = deletePlayer(node->right, temp->playerID);  
            }
        }
        return node;
    }

   
    Player* findMin(Player* node) {
        while (node && node->left != NULL) node = node->left;
        return node;
    }

    // Preorder Traversal for saving data
    void savePlayerDataToFile(Player* node, ofstream& file) const {
        if (node == NULL) return;

        file << node->playerID << "," << node->name << "," << node->phone_number << "," << node->email << "," << node->password;
        Games_played_class* game = node->GP_head;
        while (game != nullptr) {
            file << game->gameID << "," << game->hours_played << "," << game->achievements_unlock << endl;
            game = game->next;
        }
        savePlayerDataToFile(node->left, file);
        savePlayerDataToFile(node->right, file);
    }

    void saveData(const string& filename) {
        ofstream file(filename);
        savePlayerDataToFile(root, file);
        file.close();
    }
       //  function to calculate the height of the binary tree
int getHeight(Player* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

//  function to print all nodes at a given level
void printLevel(Player* node, int level) {
    if (node == nullptr) {
        return;
    }
    if (level == 1) {
        cout << "(Player ID --+" << node->playerID << ") ==> ";
    } else if (level > 1) {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}

// Function to show up to n levels of the binary tree
void showNLevels(int n) {
    if (root == nullptr) {
        cout << "Player database is empty." << endl;
        return;
    }

    int totalLevels = getHeight(root);
    cout << "Total Levels in the Tree: " << totalLevels << endl;

    // Traverse up to the specified level
    for (int i = 1; i <= n && i <= totalLevels; ++i) {
        cout << "Level " << i - 1 << ": ";
        printLevel(root, i);
        cout << endl;
    }

    if (n > totalLevels) {
        cout << "Warning: Requested level exceeds the total levels in the tree." << endl;
    }
}
    void showPlayerLevel(string& id) {
    int level = findPlayerLevelRecursive(root, id, 0);
    if (level != -1) {
        cout << "Player with ID " << id << " is at level " << level << "." << endl;
    } else {
        cout << "Player with ID " << id << " not found." << endl;
    }
}

int findPlayerLevelRecursive(Player* node, string& id, int currentLevel) {
    if (node == nullptr) {
        return -1;
    }
    if (node->playerID == id) {
        return currentLevel;
    }
    int leftLevel = findPlayerLevelRecursive(node->left, id, currentLevel + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    return findPlayerLevelRecursive(node->right, id, currentLevel + 1);
}

void showPlayerPath( string& id) {
    if (!findPlayerPath(root, id)) {
        cout << "Player with ID " << id << " not found." << endl;
    }
}

bool findPlayerPath(Player* node, string& id) {
    if (node == nullptr) {
        return false;
    }
    cout <<"|" <<node->playerID <<" : "<<node->name<<"|"<< "->";
    if (node->playerID == id) {
        return true;
    }
    if (findPlayerPath(node->left, id) || findPlayerPath(node->right, id)) {
        return true;
    }
    return false;
}
};

/*     ////////////Gamers DataBase Class\\\\\\\\\\\\\\\\*/

class Games_DataBase{
    public:
    Game* root;
    Games_DataBase():root(NULL){}
    
    Game* search(Game* node, const string& game_id) const {
        if (!node || node->gameID == game_id) return node;
        if (game_id < node->gameID) return search(node->left, game_id);
        else return search(node->right, game_id);
    }
        void insertGame(Game* game){
             if (search(root, game->gameID)) {
            cout << "Error: Player with ID " << game->gameID << " already exists." << endl;
            delete game;
           
        }
            if(root == NULL)
            {
                root = game;
                return;
            }
            Game* current= root;
            Game* parent = NULL;
            while(current)
            {
                parent=current;
                if(game->gameID<current->gameID)
                {
                  current=current->left;
                  if(!current) parent->left = game;
                }else{
                  current = current->right;
                  if(!current) parent->right = game;
                }
            }
    }
    void Loading_Data_Game(const string& fileName,int seed, int limit)
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
     void saveGameDataToFile(Game* node, ofstream& file) const {
        if (node == NULL) return;

        file << node->gameID << "," << node->Name << "," << node->Developer << "," << node->Publisher << "," << node->File_size_in_GB << "," << node->downloads << endl;
        saveGameDataToFile(node->left, file);
        saveGameDataToFile(node->right, file);
    }

    void saveData(const string& filename) {
        ofstream file(filename);
        saveGameDataToFile(root, file);
        file.close();
    }
      //  function to calculate the height of the binary tree
int getHeight(Game* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

//  function to print all nodes at a given level
void printLevel(Game* node, int level) {
    if (node == nullptr) {
        return;
    }
    if (level == 1) {
       cout << "(Game ID --+" << node->gameID << ") ==> ";
    } else if (level > 1) {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}

// Function to show up to n levels of the binary tree
void showNLevels(int n) {
    if (root == nullptr) {
        cout << "Player database is empty." << endl;
        return;
    }

    int totalLevels = getHeight(root);
    cout << "Total Levels in the Tree: " << totalLevels << endl;

    // Traverse up to the specified level
    for (int i = 1; i <= n && i <= totalLevels; ++i) {
        cout << "Level " << i - 1 << ": ";
        printLevel(root, i);
        cout << endl;
    }

    if (n > totalLevels) {
        cout << " Requested level exceeds the total levels in the tree. Cant go any further...." << endl;
        return;
    }
}

void showGameLevel(string& id) {
    int level = findGameLevelRecursive(root, id, 0);
    if (level != -1) {
        cout << "Player with ID " << id << " is at level " << level << "." << endl;
    } else {
        cout << "Player with ID " << id << " not found." << endl;
    }
}

int findGameLevelRecursive(Game* node, string& id, int currentLevel) {
    if (node == nullptr) {
        return -1;
    }
    if (node->gameID == id) {
        return currentLevel;
    }
    int leftLevel = findGameLevelRecursive(node->left, id, currentLevel + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    return findGameLevelRecursive(node->right, id, currentLevel + 1);
}

void showGamePath( string& id) {
    if (!findGamePath(root, id)) {
        cout << "Player with ID " << id << " not found." << endl;
    }
}

bool findGamePath(Game* node, string& id) {
    if (node == nullptr) {
        return false;
    }
    cout<<"|" << node->gameID <<" : "<<node->Name<<"|"<< "->";
    if (node->gameID == id) {
        return true;
    }
    if (findGamePath(node->left, id) || findGamePath(node->right, id)) {
        return true;
    }
    return false;
}
};
void displayMainMenu() {
    cout << "============================================================" << endl;
    cout << "                  |  Gamers Database Manager  |             " << endl;
    cout << "------------------------------------------------------------" << endl;
    cout<<"CHOOSE TTHE DATABASE:   "<<endl;
      cout << " |1|  Player Database       |       |2|  Gamer Database      " << endl;
  
}
void displayPlayerOptions() {
    cout << "[1] Add New Player" << endl;
    cout << "[2] Search Player" << endl;
    cout << "[3] Delete Player" << endl;
    cout << "[4] Display All Players" << endl;
    cout << "[5] Save Player Data" << endl;
    cout << "[6] Show Player DB Levels" << endl;
     cout << "[7] Show Player Level Number" << endl;
     cout << "[8] Show Player Path" << endl;
     cout << "[9] Back to main Menu" << endl;
     
}

void displayGameOptions() {
    cout << "[1] Add New Game" << endl;
    cout << "[2] Search Game" << endl;
    cout << "[3] Display All Games" << endl;
    cout << "[4] Save Game Data" << endl;
     cout << "[5] Show Game DB Levels" << endl;
     cout << "[6] Show Game Level Number" << endl;
     cout << "[7] Show Game Path" << endl;
     cout << "[8] Back to main Menu" << endl;
}
void performPlayerAction(Players_DataBase& playerDB, int choice) {
    string playerID, name, phone, email, password,key;
    switch (choice) {
        case 1: {  
            cout << "Enter Player ID: ";
            cin >> playerID;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Phone Number: ";
            cin >> phone;
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Password: ";
            cin >> password;
            
            Player* newPlayer = new Player(name, playerID, phone, email, password, NULL);
            playerDB.insertPlayer(newPlayer);
            cout << "Player Added Successfully!" << endl;
            break;
        }
        case 2: {  
            cout << "Enter Player ID to Search: ";
            cin >> playerID;
            Player* foundPlayer = playerDB.search(playerDB.root, playerID);
            if (foundPlayer) {
                cout << "Player Found!" << endl;
                cout << "ID: " << foundPlayer->playerID << ", Name: " << foundPlayer->name << endl;
                cout << "Phone: " << foundPlayer->phone_number << ", Email: " << foundPlayer->email << endl;
            } else {
                cout << "Player not found." << endl;
            }
            break;
        }
        case 3: {  
            cout << "Enter Player ID to Delete: ";
            cin >> playerID;
            playerDB.root = playerDB.deletePlayer(playerDB.root, playerID);
            cout << "Player Deleted Successfully!" << endl;
            break;
        }
        case 4: {  
            playerDB.printInOrder();
            break;
        }
        case 5: {  
            playerDB.saveData("players_data.csv");
            cout << "Player Data Saved Successfully!" << endl;
            break;
        }
        case 6: {
               int n;
            cout << "Enter the number of layers to display: ";
            cin >> n;
            playerDB.showNLevels(n);
            break;
        }
          case 7: {
           
        cout << "Enter the primary key to find its layer: ";
        cin >> key;
        playerDB.showPlayerLevel(key);
            break;
        }
        case 8: {
            
            cout << "Enter the primary key to show the path (Preorder Traversal): ";
            cin >> key;
            cout << "Preorder Traversal path to find node " << key << ": ";
            playerDB.showPlayerPath(key);
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void performGameAction(Games_DataBase& gameDB, int choice) {
    string gameID, name, developer, publisher;
    string key;
    float file_size;
    int downloads;
    switch (choice) {
        case 1: {  
            cout << "Enter Game ID: ";
            cin >> gameID;
            cout << "Enter Game Name: ";
            cin >> name;
            cout << "Enter Developer: ";
            cin >> developer;
            cout << "Enter Publisher: ";
            cin >> publisher;
            cout << "Enter File Size in GB: ";
            cin >> file_size;
            cout << "Enter Downloads: ";
            cin >> downloads;

            Game* newGame = new Game(gameID, name, developer, publisher, file_size, downloads);
            gameDB.insertGame(newGame);
            cout << "Game Added Successfully!" << endl;
            break;
        }
        case 2: {  
            cout << "Enter Game ID to Search: ";
            cin >> gameID;
            Game* foundGame = gameDB.search(gameDB.root, gameID);
            if (foundGame) {
                cout << "Game Found!" << endl;
                cout << "ID: " << foundGame->gameID << ", Name: " << foundGame->Name << endl;
                cout << "Developer: " << foundGame->Developer << ", Publisher: " << foundGame->Publisher << endl;
                cout << "File Size: " << foundGame->File_size_in_GB << " GB, Downloads: " << foundGame->downloads << endl;
            } else {
                cout << "Game not found." << endl;
            }
            break;
        }
        case 3: {  
            cout << "Displaying All Games..." << endl;
            break;
        }
        case 4: {  
            gameDB.saveData("games_data.csv");
            cout << "Game Data Saved Successfully!" << endl;
            break;
        }
        case 5: {
            int n;
            cout << "Enter the number of layers to display: ";
            cin >> n;
            gameDB.showNLevels(n);
            break;
        }
        case 6: {
           
        cout << "Enter the primary key to find its layer: ";
        cin >> key;
        gameDB.showGameLevel(key);
            break;
        }
        case 7: {
            
            cout << "Enter the primary key to show the path (Preorder Traversal): ";
            cin >> key;
            cout << "Preorder Traversal path to find node " << key << ": ";
            gameDB.showGamePath(key);
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}



int main()
{
    int seed = 232621;
    int thresHold = (seed%100)*10 + 100;
    Players_DataBase PDM;
    Games_DataBase  GDM;
      PDM.Loading_Data_Player("Players.txt", seed, thresHold);
      GDM.Loading_Data_Game("Games.txt", seed, thresHold);
     int choice, subChoice;
    
    while (true) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {  
                while (true) {
                    displayPlayerOptions();
                    cout << "Enter your choice: ";
                    cin >> subChoice;
                    if (subChoice == 12) break;
                    performPlayerAction(PDM, subChoice);
                }
                break;
            }
            case 2: {  
                while (true) {
                    displayGameOptions();
                    cout << "Enter your choice: ";
                    cin >> subChoice;
                    if (subChoice == 9) break;
                    performGameAction(GDM, subChoice);
                }
                break;
            }
            case 3: {  
                cout << "Exiting the Database Manager..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    return 0;
}
