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
enum ConsumablesType {C_FOOD, C_GOOD_DRINK, C_adlLBAD_DRINK};

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

