// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include <stdio.h>

#ifndef LEVELOBJECT_H
#define	LEVELOBJECT_H

class Player;
class Room;

enum TrapType {ARROW, TRANSPORT};
enum TileType {WALL, PATH, WHITE, BLACK, UP, DOWN};
enum ConsumablesType {FOOD, GOOD_DRINK, BAD_DRINK};

class LevelObject 
{
public:
   bool IsVisible();
   void SetVisible();
private:
   bool visible;
   Room* room;
};

class Gold : public LevelObject
{
public:   
   int GetGold();
};
   
class Trap : public LevelObject
{
public:
   void Activate(Player P);
   
private:
   TrapType type;  
};

class Tile : public LevelObject
{
public:
   bool IsWalkable();
   
private:
   TileType type;   
};

class Item : public LevelObject
{   
};
 
class Diamond : public Item
{   
};

class Consumable : public Item
{
private:
   ConsumablesType type;   
};
   
   
   
   

#endif	/* LEVELOBJECT_H */

