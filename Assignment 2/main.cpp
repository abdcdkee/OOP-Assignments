#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

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

typedef const int cint;         //Google typedef to see what this means
typedef const Point cPoint;

char* CreateDungeon(int, int, Point&, Point&);      //Creates the dungeon
void Traversal(char*, Point&, cPoint&, cint, cint); //Used for moving inside dungeon
void Combat(Player&, int);  //Used for simulating combat
void TrapStatements();  //3 statements that show at random when the player activates a trap
void FoodStatements();  //3 statements that show at random when the player finds food
void HitStatements();   //3 statements that show at random when the player hits enemy
void GetHitStatements();//3 statements that show at random when the player gets hit

int main ()
{
    srand(time(0));

    int width = 0;
    int height = 0;

    /*
    *   ADD YOUR CODE HERE IF REQUIRED
    */

    Point startPoint(0,0);
    Point exitPoint(0,0);

    char* dungeon = nullptr;

    dungeon = CreateDungeon(width, height, startPoint, exitPoint);

    Traversal(dungeon, startPoint, exitPoint, width, height);

    /*
    *   ADD YOUR CODE HERE IF REQUIRED
    */

    return 0;
}

void TrapStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void FoodStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void HitStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void GetHitStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void Traversal(char* dungeon, Point& startPoint, cPoint& exitPoint, cint width, cint height)
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED. DEFINE NEW FUNCTIONS IF IT GETS LONG.
    */

}

void Combat(Player& player, int enemies)
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

char* CreateDungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint)
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED. DEFINE NEW FUNCTIONS IF IT GETS LONG.
    */
}
