// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Level.h"
#include "LevelObject.h"
#include "Monster.h"
#include "Room.h"
#include "Player.h"

//#include <typeinfo>
#include <time.h> // for seeding randomization
#include <cstdlib> // for random numbers??

using namespace std;

Level::Level()
{
   for (int i = 0; i < X_GRID_SIZE; i++)
   {
      for (int j = 0; j < Y_GRID_SIZE; j++)
      {
         grid[i][j] = NULL;
      }
   }
   xStart = -1;
   yStart = -1;     
}

void Level::AddLevelObject(LevelObject* lo, int xPosition, int yPosition)
{
   //if (grid[xPosition][yPosition] == NULL || grid[xPosition][yPosition]->GetType() == t_black) grid[xPosition][yPosition] = lo;
   grid[xPosition][yPosition] = lo;
}

LevelObject* Level::ObjectAt(int xPosition, int yPosition) const
{
   return grid[xPosition][yPosition];
}

LevelObject* Level::RemoveItem(int xPosition, int yPosition)
{
   LevelObject* temp = grid[xPosition][yPosition];
   grid[xPosition][yPosition] = NULL;
   return temp;           
}

bool Level::IsWalkable(int xPosition, int yPosition) const
{
   token t = grid[xPosition][yPosition]->GetType();
   bool tileWalkable = true;
   if (t != t_wall && t != t_black) tileWalkable = false;

   return tileWalkable && IsMonsterAt(xPosition, yPosition);   
}

bool Level::IsMonsterAt(int xPosition, int yPosition) const
{
   for (int i = 0; i < monsters.size(); i++)
   {
      if (monsters[i]->GetX() == xPosition and monsters[i]->GetY() == yPosition)
      {
         return true;        
      }
   }
   return false;   
}

void Level::AddRoom(int xPosition, int yPosition, int width, int height)
{   
   Room* temp = new Room(xPosition, yPosition, width, height);
   rooms.push_back(temp);
}

void Level::SetStart(int xPosition, int yPosition)
{
   xStart = xPosition;
   yStart = yPosition;
}
void Level::GetStart(int &xPosition, int &yPosition)
{
   xPosition = this->xStart;
   yPosition = this->yStart;
}

bool Level::IsVisible(int xPosition, int yPosition) const
{
   return grid[xPosition][yPosition]->IsVisible();
}

void Level::AddMonsterAt(int xPosition, int yPosition, MonsterType t)
{
   monsters.push_back(new Monster(xPosition, yPosition, t));
}

Monster* Level::GetMonster(int number)
{
   return monsters[number];
}

int Level::NumberMonsters() const
{
   return monsters.size();
}

void Level::MoveMonsters(Player* p)
{
   srand(time(NULL)); // initialize random seed  
   for (int a = 0; a < monsters.size(); a++)
   {  
      int x = monsters[a]->GetX();
      int y = monsters[a]->GetY();
      if (p->GetRoom() == monsters[a]->GetRoom()) // Check if monster is in the same room as the player
      {          
         int move = (rand() % 12) + 1;
         if (move == 1) 
         {
            monsters[a]->Move(NORTH);
         }
         else if (move == 2) 
         {
            monsters[a]->Move(EAST);
         }
         else if (move ==3) 
         {
            monsters[a]->Move(SOUTH);
         }
         else if (move == 4) 
         {
            monsters[a]->Move(WEST);
         }
         else if (move >= 7 && move <= 12)
         {
            // Move toward the player code
         }         
      }
      else // Monster not in the same room
      {
         int move = (rand() % 6) + 1;
         if (move == 1) 
         {
            monsters[a]->Move(NORTH);
         }
         else if (move == 2) 
         {
            monsters[a]->Move(EAST);
         }
         else if (move ==3) 
         {
            monsters[a]->Move(SOUTH);
         }
         else if (move == 4) 
         {
            monsters[a]->Move(WEST);
         }
         
      }
   }
}






