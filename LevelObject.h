// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include <stdio.h>
#include "lexfile.h"

#ifndef LEVELOBJECT_H
#define	LEVELOBJECT_H

class Player;
class Room;

//enum TrapType {ARROW, TRANSPORT};
//enum TileType {T_WALL, T_PATH, T_WHITE, T_BLACK, T_UP, T_DOWN};
//enum ConsumableType {C_FOOD, C_GOOD_DRINK, C_BAD_DRINK};
//enum ClassType {TYPE_GOLD, TYPE_TRAP

class LevelObject 
{
public:
   //LevelObject();
   LevelObject(token tok);
   bool IsVisible() const;
   void SetVisible();
   bool IsWalkable() const;
   token GetType() const;
private:
   token type;
   bool visible;
   Room* room;
};


class Gold : public LevelObject
{
public:
   Gold();
   int GetGold();
};

   
class Trap : public LevelObject
{
public:
   Trap(token t);
   void Activate(Player p); 
//   TrapType GetType();  
private:
//   TrapType type;  
};


class Tile : public LevelObject
{
public:
   bool IsWalkable() const;
   Tile(token t);
//   TileType GetType() const; 
private:
//   TileType type;   
};


class Item : public LevelObject
{
public:
   Item(token t);
};
 
class Diamond : public Item
{
public:
   Diamond();
};

class Consumable : public Item
{
public:
   Consumable(token t);
//   ConsumableType GetType() const;
private:
//   ConsumableType type;   
};
   
   
   
   

#endif	/* LEVELOBJECT_H */

