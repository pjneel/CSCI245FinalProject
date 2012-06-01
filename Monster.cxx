// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Monster.h"
#include "Player.h"

#include <time.h>
#include <cstdlib>

Monster::Monster(int x, int y, MonsterType t, int level)
{
   srand(time(NULL));
   xPosition = x;
   yPosition = y;
   type = t;
   visible = false;
   health = 7 + (rand() % (level + 1)) + 1;
}

MonsterType Monster::GetType() const
{
   return type;
}

void Monster::SetVisible()
{
   visible = true;
}

void Monster::SetInvisible()
{
   visible = false;
}

void Monster::Move(direction d)
{
   if(d == NORTH) this->yPosition -= 1;
	else if (d == SOUTH) this->yPosition += 1;
	else if (d == WEST) this->xPosition -= 1;
	else if (d == EAST) this->xPosition += 1;
}

void Monster::ChangeHealth(int h)
{
   health += h;
}
int Monster::GetHealth() const
{
   return this->health;
}

int Monster::Combat(Player* p)
{
   if (p->GetHealth > 0)
   {
      srand(time(NULL)); // initialize random seed
      int mnstr = (rand() % (this->health + 1)) + 1;
      int plyr = (rand() % p->GetHealth()) + 1;

      if(plyr > mnstr) this->ChangeHealth(mnstr - plyr);
      else if (mnstr > plyr) p->ChangeHealth(plyr - mnstr);

      return mnstr - plyr;
   }
   return -9999;
}

void Monster::SetRoom(Room* r)
{
   room = r;
}

int Monster::GetX() const
{
   return xPosition;
}

int Monster::GetY() const
{
   return yPosition;
}

bool Monster::IsVisible() const
{
   return this->visible;
}

Room* Monster::GetRoom() const
{
   return room;
}

