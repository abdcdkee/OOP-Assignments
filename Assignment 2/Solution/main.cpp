/*Name: Muhammad Abdullah Siddiqui                                                       ID: ms03586*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/***Note: Code has been separated into segments based on type of task being attempted, delimited by a line of forward slashes
 ***for clarity while reading. The function declarations for each segments are separated by whitespace.*/

//Structure to keep track of various locations
struct Point
{
    int x;
    int y;

    Point(int _x, int _y): x(_x), y(_y)
    {

    }

};
//Structure for the Player object
struct Player
{
    int food;
    int health;
    bool alive;
    int x;
    int y;
    Player()
    {
        food = 64;
        health = 10;
        alive = true;
    }
    void loseHealth()
    {
        if(health>0)
            health--;
        if(health==0)
            alive = false;
    }
    void gainHealth()
    {
        if(health<10)
            health++;
    }
};

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef const int cint;
typedef const Point cPoint;

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CheckSize(int);                             //Assigns default value of '8' if value of height/width is less than 8

char* CreateDungeon(int, int, Point&, Point&);  //Creates the dungeon. Calls PlacingFeatures, StartPosition, ExitPosition
void PlacingFeatures(char*, int, int);          //Places objects in the dungeon randomly. Calls random placement
int StartPosition(char*, int, int);             //Specifies starting position of player
int ExitPosition(char*, int, int);              //Specifies position of the exit
char RandomPlacement(int);                      //Returns random object to be placed in dungeon

void Instructions(char*, int, int);             //Specifies Instructions at the start of the game
char MovementInput();                           //Specifies instructions and accepts user input for direction to move in

void Traversal(char*, Point&, cPoint&, cint, cint);     //Used for moving inside dungeon

int GetIndex(Player&, int, int);                        //Returns index of a 1D array given a Point location of a 2D dungeon
void DisplayDungeon(char*, int, int);                   //Prints the dungeon. Used for debugging
void EraseElement(char*, int);                          //Erases the element in an array at a certain index


Player ChangePlayerPosition(char*, Player&, char, int, int); //Moves the player one step in a direction. Calls CheckPlayer
                                                             //Location
bool CheckPlayerLocation(char*, Player&, int, int);          //Checks whether a wall is blocking player's path. Calls
                                                             //Obstacle, PlayerReaction
void PlayerReaction(char*, Player&, int);                    //Changes player attributes depending on the object in the
                                                             //new player location. Calls multiple other functions
void Obstacle(Player&, int, int);                            //Warns the user about the presence of a wall


void TrapStatements();      //3 statements that show at random when the player activates a trap
void HealthSatus(Player&);  //Displays the health of the player
void HealthBoost(Player&);  //Displays a statement when player finds health in the dungeon

void FoodStatements();      //3 statements that show at random when the player finds food
void FoodStatus(Player&);   //Displays the current food the player has left
void PlayerFood(Player&);   //Displays a statement when player finds food in the dungeon

void Combat(Player&, int);  //Used for simulating combat
int GenerateEnemies();      //Specifies number of enemies created, prints message to initialize comba
void HitStatements();       //3 statements that show at random when the player hits enemy
void GetHitStatements();    //3 statements that show at random when the player gets hit

void GameWon();             //Displays message when player has found the exit
void GameLossHealth();      //Displays message when player has lost due to zero health
void GameLossFood();        //Displays message when player has lost due to zero food

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main ()
{
    srand(time(0));

    int width = 0;
    int height = 0;

    cout<<"Enter the size of the dungeon you want to play in:"<<endl;
    cout<<"\nWidth: ";
    cin>>width;
    width = CheckSize(width);   //Ensures width is more than 8
    cout<<"\nHeight: ";
    cin>>height;
    height = CheckSize(height); //Ensures height is more than 8

    Point start_point(0,0);     //startPoint changed to start_point to maintain uniformity in usage of variable names
                                //throughout code
    Point exit_point(0,0);

    char* dungeon = NULL;       //nullptr changed to NULL since my code was not compiling. A problem i believe might be solved
                                //when compiling in C++11 mode, but i thought that would be overtly complicated

    dungeon = CreateDungeon(width, height, start_point, exit_point);
    Instructions(dungeon, height, width);                               //Displays instructions for user
    Traversal(dungeon, start_point, exit_point, width, height);

    delete[] dungeon; //Deletes pointer to deallocate memory

    return 0;
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int CheckSize(int value)
    /*Changes width/height to more than 8 if value entered is less than 8*/
{
    if (value<8)
    {
        cout<<"Sorry: Your input value for too small. "<<value<<" has been changed to 8."<<endl;
        return 8;
    }
    else
    {
        return value;
    }
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


char* CreateDungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint)
      /*Creates Dungeon*/
{
    int array_length = height*width;        //Specifies 1D array of size height*width
    char* dungeon = new char[array_length]; //Creates dynamic char array.
    dungeon[array_length] = '\0';           //Adds null terminator at the end of the array
    for (int i=0; i < array_length; i++)
    {
        if ((i<width) || (i>=(array_length-width)))     //Adds walls to the first and last row of the dungeon
        {
            dungeon[i] = 'w';
        }
        if ((i>0) && (i%width==0))                      //Adds walls to the first and last column of the dungeon
        {
            dungeon[i] = 'w';
            dungeon[i+width-1] = 'w';
        }
    }

    PlacingFeatures(dungeon, height, width);                        //Places objects in the dungeon
    int start_y_coordinate = StartPosition(dungeon, height, width); //Specifies row number of player's starting position
    int exit_y_coordinate = ExitPosition(dungeon, height, width);   //Specifies row number of exit's position
    ref_startPoint.x = 1;
    ref_startPoint.y = start_y_coordinate;                          //Specifies player's starting position in ref_startPoint
    ref_exitPoint.x = width-2;
    ref_exitPoint.y = exit_y_coordinate;                            //Specifies exit position in ref_exitPoint
    return dungeon;
}

void PlacingFeatures(char* dungeon, int height, int width)
     /*Places objects in dungeon*/
{
    for (int i=0; i < height*width; i++)
    {
        int probability = rand()%100;
        if (probability<20 && dungeon[i]!='w')   //Condition fulfilled if location is empty and probability is 20%
        {
            int random = rand()%75;              //Assigns 'random' a random value between 0 and 75
            dungeon[i] = RandomPlacement(random);//Returns an object to be placed depending on the random value passed to function
        }
        else if (dungeon[i]!='w')
        {
            dungeon[i] = ' ';                    //Ensures that there are no stray/unwanted characters stored in the array
        }
    }
}

/***Note that the StartPosition function below iterates each row of the first column with a 33.3% chance of placing the player's
    starting position there, while the ExitPosition function below iterates each row of the last column with a 20% chance of placing
    the exit there. This has been done to increase the chances of the start position being in the top left half, and the exit
    being in the bottom right half, to increase the difficulty of the game slightly. However, it is still of course, completely
    random as instructed*/

int StartPosition(char* dungeon, int height, int width)
    /*Assigns starting position to player*/
{
    bool position_found = false;
    int player_position = 0;                                  //y coordinate of player's starting position
    for (int j=0; j<height*width; j++)
    {
        if (((j-1)%width==0) && (j>1))
        {
            player_position++;                                //Increments as we iterate to a next row in the dungeon
        }

        if ((j%width==1) && (dungeon[j] == ' ') && (j>width)) //Iterates each row in first column until it reaches an empty space
        {
            int random_placer = rand()%3;
            if (random_placer==0)                             //Condition fulfilled with a 33.3% probability
            {
                dungeon[j] = 'P';                             //Assigns a player a starting position
                position_found = true;
                break;
            }

        }
    }
    if (position_found == false)  //Assigns a default location at top left to player's starting position if needed
    {
        player_position = 1;
        dungeon[width+1] = 'P';
    }
    return player_position;
}

int ExitPosition(char* dungeon, int height, int width)
{   /*Assigns exit position*/
    bool position_found = false;
    int exit_position = 0;                                           //y coordinate of exit position
    for (int j=0; j<height*width; j++)
    {
        if ( ((j+2)%width==0) && (dungeon[j] == ' ') && (j>width) ) //Iterates each row in last column until it reaches an
        {                                                           //empty spot
            int random_placer = rand()%5;
            if (random_placer==0)                                   //Condition has 20% probability of being fulfilled
            {
                dungeon[j] = 'X';                                   //Assigns position of exit
                position_found = true;
                break;
            }

        }
        if (((j-1)%width==0) && (j>1))
        {
            exit_position++;                                        //Increments as we iterate to next row in the last column
        }
    }
    if (position_found == false) //Assigns default exit position at bottom right if needed
    {
        exit_position = height - 2;
        dungeon[height*width - width - 2] = 'X';
    }
    return exit_position;
}

char RandomPlacement(int value)
     /*Returns an object depending on the value inputted. Each object is associated with a 15 digit range*/
{
    if (value>=0 && value<15)
    {
        return 'E';
    }
    else if (value>=15 && value<30)
    {
        return 'H';
    }
    else if (value>=30 && value<45)
    {
        return 'T';
    }
    else if (value>=45 && value<60)
    {
        return 'F';
    }
    else if (value>=60)
    {
        return 'w';
    }
    return ' ';
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Instructions(char* dungeon, int height, int width)
     /*Outputs instructions for the user to start playing the game*/
{
    cout<<"=========================BASED ON LORD OF THE RINGS============================="<<endl;
    cout<<endl<<"Disclaimer: The game is best played in full screen mode for large dungeon sizes."<<endl;
    cout<<endl<<"You are Aragorn, a ranger of some repute in Middle Earth. Your were traveling with a band of heroes in";
    cout<<" a quest to destroy the One Ring. Your party was ambushed by minions of the Dark Lord in the mines of Moria";
    cout<<" and you were knocked unconscious. You wake up to find yourself in a dungeon filled with danger. It's now up to you";
    cout<<" to find your way out of the dungeon and rescue your friends. Good Luck!!"<<endl<<endl;
    cout<<"U -> Move Up"<<endl;
    cout<<"L -> Move Left"<<endl;
    cout<<"D -> Move Down"<<endl;
    cout<<"R -> Move Right"<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------";
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<"================================ TURN # 1 ====================================="<<endl<<endl;
    //DisplayDungeon(dungeon, height, width);
}

char MovementInput()
     /*Outputs movement Instructions and takes input from user at every turn to specify direction of movement*/
{
    char direction;
    cout<<"In which direction do you want to move? <W,A,S,D; Press 'X' if you want to give up and die>"<<endl;
    cin>>(direction);
    cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    return direction;
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Traversal(char* dungeon, Point& start_point, cPoint& exit_point, cint width, cint height)
     /*Traverses the dungeon at each turn of the game to move player and change player attributes as needed
      *Do note that the convention for position coordinates are such that the top left is <0,0> and each value
      *of a coordinate to the right or downwards is incremented by one*/
{
    Player player;                                 //Creates player object of type Player
    player.x = start_point.x;                      //Assigns x and y coordinates of start_point to player
    player.y = start_point.y;
    int counter=1;                                 //Records number of turns

    while (true)   //Loop runs until player runs out of food or player health decreased to zero or the game is won
    {
        player.food--;                             //Decreases one food in every turn of the game
        char direction = MovementInput();          //Takes input from the user

        if (direction=='x' || direction=='X')      //Ends the game when user quits midway
        {
            cout<<"\nYou have chosen to end the game, Do try again later!!"<<endl;
            break;
        }

        dungeon[GetIndex(player, height, width)] = ' ';                           //Erases symbol 'P' from current location of
                                                                                  //player
        player = ChangePlayerPosition(dungeon, player, direction, height, width); //Assigns player the new location
        dungeon[GetIndex(player, height, width)] = 'P';                           //Assigns symbol 'P' at new player location

        FoodStatus(player);                                   //Displays how many food/turns a player has left

        if (player.x==exit_point.x && player.y==exit_point.y) //Breaks loop and displays that game has been won when
                                                              //player's location matches the exit position
        {
            GameWon();
            break;
        }
        if (player.health==0)   //Breaks loop and displays that game is lost when player runs out of health
        {
            GameLossHealth();
            break;
        }
        if (player.food==0)     //Breaks loop and displays that game is lost when player runs out of food
        {
            GameLossFood();
            break;
        }

        //DisplayDungeon(dungeon, height, width); //Prints dungeon if needed (used for debugging)
        counter++;
        cout<<"\n\n\n\n================================ TURN #"<<counter<<" ====================================="<<endl;
    }
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int GetIndex(Player& player, int height, int width)
    /*Returns index of a 1D array taking coordinates and height/width for a 2D dungeon as inputs*/
{
    int x = player.x;
    int y = player.y;
    int location = (width-1) + (y-1)*width + x + 1;     //Generalized formula utilized. Simplified form of formula is
                                                        //width*y + x , which is not implemented as i feel the one given
                                                        //on the left is more intuitive
    return location;
}

void DisplayDungeon(char* dungeon, int height, int width)
     /*Prints dungeon with all objects and player/exit location (used for debugging)*/
{
    int array_length = height*width;

    for (int i=0; i<array_length; i++)
    {
        cout<<dungeon[i];                   //Prints each element of the 1D dungeon array

        if (((i+1)%width == 0) && (i>0))    //New line initiated on output screen when elements in one row has been iterated
        {
            cout<<endl;
        }
    }
    cout<<endl;
}

void EraseElement(char* dungeon, int index)
     /*Erases the element at 'index' index in a 1D 'dungeon' array*/
{
    dungeon[index] = ' ';
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Player ChangePlayerPosition(char* dungeon, Player& player, char direction, int height, int width)
      /*Changes position coordinate of the player depending on user inputs. Subsequently calls functions
       *to check whether there's any change to player's attributes*/
{
    bool move_possible = true;              //Bool initiated to ensure that there's no wall blocking player path
    if (direction=='U' || direction=='u')
    {
        player.y -= 1;                      //y coordinate decreases by 1 when player moves up
        move_possible = CheckPlayerLocation(dungeon, player, height, width);
        if (move_possible==false)           //Changes player position back to original value if path is being blocked by a wall
        {
            player.y+=1;
        }
        return player;
    }
    else if (direction=='L' || direction=='l')
    {
        player.x -= 1;                      //x coordinate decreases by 1 when player moves left
        move_possible = CheckPlayerLocation(dungeon, player, height, width);
        if (move_possible==false)           //Changes player position back to original value if path is being blocked by a wall
        {
            player.x+=1;
        }
        return player;
    }
    else if (direction=='D' || direction=='d')
    {
        player.y += 1;                      //y coordinate increases by 1 when player moves down
        move_possible = CheckPlayerLocation(dungeon, player, height, width);
        if (move_possible==false)           //Changes player position back to original value if path is being blocked by a wall
        {
            player.y-=1;
        }
        return player;
    }
    else if (direction=='R' || direction=='r')
    {
        player.x += 1;                      //x coordinate increases by 1 when player moves right
        move_possible = CheckPlayerLocation(dungeon, player, height, width);
        if (move_possible==false)           //Changes player position back to original value if path is being blocked by a wall
        {
            player.x-=1;
        }
        return player;
    }
    else                                    //Accounts for wrong input for direction and subsequently displays an error message
    {
        cout<<"Error: Wrong Input. You just wasted one turn. Please try again."<<endl;
    }

    return player;                          //Returns updated player position
}

bool CheckPlayerLocation(char* dungeon, Player& player, int height, int width)
     /*Returns false if player runs into a wall, true otherwise*/
{
    int array_index = GetIndex(player, height, width); //array_index stores index value for player location in an array

    if (dungeon[array_index] == 'w')
    {
        Obstacle(player, height, width);               //Displays error message stating an obstacle is blocking the path
        return false;
    }
    else
    {
        PlayerReaction(dungeon, player, array_index);  //Displays player reaction and changes player attributes as required

    }

    return true;
}

void PlayerReaction(char* dungeon, Player& player, int array_index)
     /*Displays player reaction and changes player attributes as required*/
{
    if (dungeon[array_index] == 'H')
    {
        HealthBoost(player); //Displays story element showing health has increased
        player.gainHealth(); //Increments player's health attribute
        HealthSatus(player); //Displays message showing health level of player
    }
    else if (dungeon[array_index] == 'T')
    {
        player.loseHealth(); //Decrements player's health attribute
        TrapStatements();    //Displays story element showing health has decreased
        HealthSatus(player); //Displays message showing health level of player
    }
    else if (dungeon[array_index] == 'E')
    {
        int enemies = GenerateEnemies(); //Assigns number of enemies player faces. Displays a message accordingly
        Combat(player, enemies);         //Combat function plays out player v/s enemy combat with a random outcome
    }
    else if (dungeon[array_index] == 'X')//Placeholder condition so that program doesn't enter the 'else' statement accidentally
    {}                                   //Displays no message if player has reached the exit
    else if (dungeon[array_index] == 'F')
    {
        FoodStatements();   //Displays story element showing food has increased
        PlayerFood(player); //Displays message showing amount of food player has found. Also changes player's food attribute
    }
    else
    {
        cout<<"There is nothing here."<<endl<<endl; //Displays message for an empty location
    }
    EraseElement(dungeon, array_index); //Erases any object at the location and replaces them with a blank spot
}

void Obstacle(Player& position, int height, int width)
     /*Displays message when player's path is blocked by a wall. Also hints whether player is at
      *the edge of the dungeon or has encountered a wall in the middle of the dungeon*/
{
    if (position.x==0 || position.x==(width-1) || position.y==0 || position.y==(height-1))
    {
        cout<<"You can not move in that direction. You are at the edge of the dungeon."<<endl<<endl;
    }
    else
    {
        cout<<"You can not move in that direction. There's a wall blocking your path."<<endl<<endl;
    }
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TrapStatements()
     /*Displays one out of five random statements with 20% probability each*/
{
    int probability = rand()%5;
    if (probability==0)
    {
        cout<<"Oh No, Your leg got caught in a bear trap."<<endl;
    }
    else if (probability==1)
    {
        cout<<"Oh No, You were struck by spikes suddenly flying out of the wall."<<endl;
    }
    else if (probability==2)
    {
        cout<<"Ouch! You stepped on some spikes hidden cleverly beneath some leaves."<<endl;
    }
    else if (probability==3)
    {
        cout<<"Woah, You stumble upon a tripwire and scrape your knee."<<endl;
    }
    else
    {
        cout<<"Ouch!! You were bitten by a rabid dog out of nowhere."<<endl;
    }
}

void HealthSatus(Player& player)
     /*Outputs current health attribute of player*/
{
    cout<<endl<<"Your current health is: "<<player.health<<endl;
}

void HealthBoost(Player& player)
     /*Displays story element showing player's health has increased*/
{
    cout<<"You discovered a magic potion and drank it. You feel strength returning to your tired limbs."<<endl<<endl;
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void FoodStatements()
     /*Displays one out of five random statements with 20% probability each*/
{
    int probability = rand()%5;
    if (probability==0)
    {
        cout<<"You found some herbs lying around."<<endl;
    }
    else if (probability==1)
    {
        cout<<"You opened a chest to discover some Lembas bread, a wonderful Elvish food."<<endl;
    }
    else if (probability==2)
    {
        cout<<"You hunted and killed some enormous rats."<<endl;
    }
    else if (probability==3)
    {
        cout<<"You accidentally step on a lizard. Oh well, you'll have to eat what you get."<<endl;
    }
    else
    {
        cout<<"You find a hoard of fruits and berries hidden in a nook, presumably left by some long dead prisoner."<<endl;
    }
}

void FoodStatus(Player& player)
     /*Outputs current food attribute of player*/
{
    cout<<"You have enough food for "<<player.food<<" more turns."<<endl<<endl;
}

void PlayerFood(Player& player)
     /*Displays by how much the food attribute of the player has increased. Food increases by a
      *random value between 4 and 8*/
{
    int food_qty = rand()%5 + 4;
    player.food += food_qty;
    cout<<endl<<"You found food to last you "<<food_qty<<" more days."<<endl;
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Combat(Player& player, int enemies)
     /*Simulates player versus enemies combat*/
{
    cout<<endl<<"*********************************START OF COMBAT********************************"<<endl;
    while ((enemies>0) && (player.health>0)) //Loop runs till either player dies or all enemies are vanquished
    {
        int hit_enemy = rand()%100;
        if (hit_enemy < 30)                  //Conditional fulfilled: player hits enemies with 30% success probability
        {
            HitStatements();
            enemies--;                       //Number of elements decremented as one enemy dies
            cout<<"^_^ You killed 1 enemy."<<endl;
        }
        if (enemies==0)
        {
            break;
        }

        int hit_player = rand()%100;
        if (hit_player < 10)                 //Conditional fulfilled: enemies hit player with 10% success probability
        {
            GetHitStatements();
            player.loseHealth();             //Player attribute health decremented when player gets hit
            cout<<"x_x You lost 1 health."<<endl;
        }
    }
    if (player.health==0)                    //Displays message depending on whether player survived the combat
    {
        cout<<endl<<"Oh No, You have been vanquished by the Dark Lord's fearsome minions."<<endl<<endl<<endl;
    }
    else
    {
        cout<<endl<<"Congratulations, You successfully fought off this attack."<<endl<<endl<<endl;
    }
    cout<<"**********************************END OF COMBAT*********************************"<<endl<<endl;
    HealthSatus(player);
}

int GenerateEnemies()
    /*Generates random number of enemies (between 2 and 4) and displays story element message regarding combat*/
{
    int qty = rand()%3 + 2;
    int probability = rand()%3;
    if (probability==0)
    {
        cout<<"You turned a corner and stumble upon a party of Orcs. You are faced with "<<qty<<" foes."<<endl;
    }
    else if (probability==1)
    {
        cout<<qty<<" Balrogs appear out of nowhere."<<endl<<endl;
    }
    else if (probability==2)
    {
        cout<<"The ground rumbles in the distance. You look up to see "<<qty<<" trolls charging at you."<<endl<<endl;
    }
    return qty;
}

void HitStatements()
     /*Displays one out of five random statements with 20% probability each*/
{
    int probability = rand()%5;
    if (probability==0)
    {
        cout<<"You used your dagger to slice open the enemy's throat."<<endl;
    }
    else if (probability==1)
    {
        cout<<"Your right cross sent the enemy sprawling down on the dungeon floor."<<endl;
    }
    else if (probability==2)
    {
        cout<<"You decide to play dirty and stab the enemy where the sun doesn't shine. It's super effective!"<<endl;
    }
    else if (probability==3)
    {
        cout<<"You thrust your trusty sword 'Anduril' into the enemies heart as he lunges towards you."<<endl;
    }
    else
    {
        cout<<"You summon the power of the one ring to send one enemy back to the pits of      Mordor."<<endl;
    }
}

void GetHitStatements()
     /*Displays one out of five random statements with 20% probability each*/
{
    int probability = rand()%5;
    if (probability==0)
    {
        cout<<"An enemy throws a rock at you. It bounces off your shoulder."<<endl;
    }
    else if (probability==1)
    {
        cout<<"You are shot in the leg by an arrow."<<endl;
    }
    else if (probability==2)
    {
        cout<<"You are stabbed in the abdomen by a foe. Fortunately, your breastplate takes thebrunt of the attack."<<endl;
    }
    else if (probability==3)
    {
        cout<<"An enemy head-butts you unexpectedly."<<endl;
    }
    else
    {
        cout<<"Your foe wrestles you to the ground and punches you multiple times, breaking your nose."<<endl;
    }
}


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameWon()
     /*Outputs story element when player has found the exit & won the game*/
{
    cout<<endl<<"After a long and hard journey, you finally managed to escape from the terrors of the dungeon.";
    cout<<"It feels good to feel the wind upon your face once again. But your quest is not yet at an end.";
    cout<<"You take a deep breath and set off into the unknown  to free your friends. "<<endl<<endl;
    cout<<"------------------------YOU WON THE GAME, YOU'RE AMAZING------------------------";
}

void GameLossFood()
     /*Outputs story element when player has ran out of food & lost the game*/
{
    cout<<endl<<"The bravest of heroes might be brought down by a turn of fortune. You ran out of food even as you struggled";
    cout<<" to find your way out of the dungeon. Now your bones will rest with those of all the other unfortunate souls";
    cout<<" who found themselves on the wrong side of the Dark Lord forevermore."<<endl<<endl;
    cout<<"------------------------YOU LOST THE GAME, TRY AGAIN L8R------------------------";
}

void GameLossHealth()
     /*Outputs story element when player has ran out of health & lost the game*/
{
    cout<<endl<<"The bravest of heroes might be brought down by a turn of fortune.";
    cout<<" Now your bones will rest alongside your vanquished foes forevermore."<<endl<<endl;
    cout<<"------------------------YOU LOST THE GAME, TRY AGAIN L8R------------------------";
}


/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


