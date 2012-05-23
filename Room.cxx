// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Room.h"

Room::Room(int xPos, int yPos, int xSize, int ySize)
{
   this->xPos = xPos;
   this->yPos = yPos;
   this->xSize = xSize;
   this->ySize = ySize;
}

int Room::GetX() const
{
   return xPos;   
}

int Room::GetY() const
{
   return yPos;   
}

int Room::GetWidth() const
{
   return xSize;   
}

int Room::GetHeight() const
{
   return ySize;   
}


