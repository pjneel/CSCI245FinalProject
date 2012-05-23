// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Level.h"

#include "LevelObject.h"
#include "Monster.h"
#include "Room.h"

#include <typeinfo>

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
   LevelObject* temp = grid[xPosition][yPosition];
   bool tileWalkable = false;
   if (typeid(*temp).name() == "Tile")
   {
      //Tile* t = dynamic_cast<Tile*>(temp);
      tileWalkable = grid[xPosition][yPosition]->IsWalkable();
   }
   else tileWalkable = true;

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
   for(int i = yPosition; i <= height; i++)
   {
	for(int j = xPosition; j <= width; j++) this->AddLevelObject(new Tile(T_WALL), j, i);
   }
}

void Level::SetStart(int xPosition, int yPosition)
{
   xStart = xPosition;
   yStart = yPosition;
}
