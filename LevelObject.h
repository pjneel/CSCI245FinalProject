// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include <stdio.h>

#ifndef LEVELOBJECT_H
#define	LEVELOBJECT_H

class Player;
class Room;

enum TrapType {ARROW, TRANSPORT};
enum TileType {T_WALL, T_PATH, T_WHITE, T_BLACK, T_UP, T_DOWN};
enum ConsumableType {C_FOOD, C_GOOD_DRINK, C_BAD_DRINK};

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
   Trap(TrapType t);
   void Activate(Player p); 
   TrapType GetType();  
private:
   TrapType type;  
};


class Tile : public LevelObject
{
public:
   bool IsWalkable() const;
   Tile(TileType t);
   TileType GetType() const;
//   bool operator==(TileType t) const;   
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
public:
   Consumable(ConsumableType t);
   ConsumableType GetType() const;
private:
   ConsumableType type;   
};
   
   
   
   

#endif	/* LEVELOBJECT_H */

