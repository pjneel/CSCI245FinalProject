// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "LevelObject.h"
#include <time.h>
#include <cstdlib>

const int X_GRID_SIZE = 50;
const int Y_GRID_SIZE = 40;

using namespace std;

void LevelObject::LevelObject()
{
   visible = false;
   room = NULL;
}

bool LevelObject::IsVisible() const
{
   return visible;
}

void LevelObject::SetVisible()
{
   visible = true;
}

Trap::Activate(Player p)
{
   if (type == ARROW)
   {
      p.ChangeHealth(-1);
   }
   else if (type == TRANSPORT)
   {
      srand(time(NULL)); // initialize random seed   
      int xNew = rand() % X_GRID_SIZE;
      int yNew = rand() % Y_GRID_SIZE;
      
      // Loop until we find a valid position for the player
      while (!Level::IsWalkable(xNew, yNew) or Level::IsMonsterAt(xNew, yNew))
      {
         xNew = rand() % X_GRID_SIZE;
         yNew = rand() % Y_GRID_SIZE;           
      }
      p.SetPosition(xNew, yNew);
   }      
}

bool Tile::IsWalkable() const
{
   if (type == WALL or type == BLACK) return false;
   else return true;
}

void Tile::Tile(TileType t) 
{
   type = t;
}





