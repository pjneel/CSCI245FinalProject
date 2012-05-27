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
}

MonsterType Monster::GetType() const
{
   return type;
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

void Monster::Combat(Player p)
{
   // Combat code goes here
}

int Monster::GetX() const
{
   return xPosition;
}

int Monster::GetY() const
{
   return yPosition;
}

Room* Monster::GetRoom() const
{
   return room;
}

