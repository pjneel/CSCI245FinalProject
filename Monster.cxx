// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Monster.h"
#include "Player.h"

Monster::Monster(int x, int y, MonsterType t)
{
   xPosition = x;
   yPosition = y;
   type = t;
   visible = false;
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

void Monster::Combat(Player p)
{
   // Combat code goes here
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

