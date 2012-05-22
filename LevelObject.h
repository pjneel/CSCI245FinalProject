// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include <stdio.h>
#include "Level.h"

#ifndef LEVELOBJECT_H
#define	LEVELOBJECT_H

class Player;
class Room;

enum TrapType {ARROW, TRANSPORT};
enum TileType {T_WALL, T_PATH, T_WHITE, T_BLACK, T_UP, T_DOWN};
enum ConsumablesType {C_FOOD, C_GOOD_DRINK, C_BAD_DRINK};

class LevelObject 
{
public:
   LevelObject();
   bool IsVisible() const;
   void SetVisible();
   virtual bool IsWalkable() const;
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
   void Activate(Player p);   
private:
   TrapType type;  
};


class Tile : public LevelObject
{
public:
   bool IsWalkable() const;
   Tile(TileType t);   
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

