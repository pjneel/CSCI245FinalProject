// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "LevelObject.h"
#include "Player.h"

#include <time.h>
#include <cstdlib>

const int X_GRID_SIZE = 50;
const int Y_GRID_SIZE = 40;

using namespace std;

LevelObject::LevelObject(token t)
{
   visible = false;
   room = NULL;
   type = t;
}

bool LevelObject::IsVisible() const
{
   return visible;
}

void LevelObject::SetVisible()
{
   visible = true;
}

token LevelObject::GetType() const
{
   return type;
}

bool LevelObject::IsWalkable() const
{
   if (type == t_wall or type == t_black) return false;
   else return true;
}

Item::Item(token t) : LevelObject(t)
{

}

void Trap::Activate(Player p)
{
   if (this->GetType() == t_arrow)
   {
      p.ChangeHealth(-1);
   }
   else if (this->GetType() == t_transport)
   {
      srand(time(NULL)); // initialize random seed   
      int xNew = rand() % X_GRID_SIZE;
      int yNew = rand() % Y_GRID_SIZE;
      
      // Loop until we find a valid position for the player
      // I'm commenting this out for now so I can compile
      // Currently may return an invalid position. - PJN
      
      
      //while (!Level::IsWalkable(xNew, yNew) or Level::IsMonsterAt(xNew, yNew))
      //{
      //   xNew = rand() % X_GRID_SIZE;
      //   yNew = rand() % Y_GRID_SIZE;           
      //}
      p.SetPosition(xNew, yNew);
   }      
}

Trap::Trap(token t) : LevelObject(t)
{
   //LevelObject(t);
}

/*TrapType Trap::GetType()
{
   return type;
}

bool Tile::IsWalkable() const
{
   if (type == t_wall or type == t_black) return false;
   else return true;
}
*/

Tile::Tile(token t) : LevelObject(t)
{
   //LevelObject(t);
}

/*TileType Tile::GetType() const
{
   return type;
}*/

Consumable::Consumable(token t) : Item(t)
{
   //LevelObject(t);
}
 
/*ConsumableType Consumable::GetType() const
{
   return type;
}*/
Gold::Gold() : LevelObject(t_gold) {}
Diamond::Diamond() : Item(t_diamond) {}




