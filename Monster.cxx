// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Monster.h"
#include "Player.h"


MonsterType Monster::GetType() const
{
   return type;
}

void Monster::Move(int direction)
{
   // Move code goes here
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

