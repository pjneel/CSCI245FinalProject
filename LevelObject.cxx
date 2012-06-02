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
   beneath = NULL;
}

LevelObject::LevelObject(token t, Room* r)
{
   visible = false;
   room = r;
   type = t;
   beneath = NULL;
}

bool LevelObject::IsVisible() const
{
   return visible;
}

void LevelObject::SetVisible()
{
   visible = true;
}

void LevelObject::SetBeneath(LevelObject* b)
{
   beneath = b;
}

void LevelObject::SetRoom(Room* r)
{
   room = r;
}

LevelObject* LevelObject::GetBeneath() const
{
   return beneath;
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

Room* LevelObject::GetRoom() const
{
   return room;
}

Item::Item(token t) : LevelObject(t) {}
Item::Item(token t, Room* r) : LevelObject(t, r) {}

void Trap::Activate(Player* p)
{
   if (this->GetType() == t_arrow)
   {
      p->ChangeHealth(-1);
   }
   else if (this->GetType() == t_transport)
   {
      srand(time(NULL)); // initialize random seed
      int xNew = rand() % X_GRID_SIZE;
      int yNew = rand() % Y_GRID_SIZE;
      
      p->SetPosition(xNew, yNew);
   }      
}

Trap::Trap(token t) : LevelObject(t) {}
Trap::Trap(token t, Room* r) : LevelObject(t, r) {}

Tile::Tile(token t) : LevelObject(t) {}
Tile::Tile(token t, Room* r) : LevelObject(t, r) {}

Consumable::Consumable(token t) : Item(t) {}
Consumable::Consumable(token t, Room* r) : Item(t, r) {}

Gold::Gold() : LevelObject(t_gold) {}
Gold::Gold(Room* r) : LevelObject(t_gold, r) {}

int Gold::GetGold()
{
   srand(time(NULL));
   return rand() % 95 + 5;   
}

Diamond::Diamond() : Item(t_diamond) {}
Diamond::Diamond(Room* r) : Item(t_diamond, r) {}




