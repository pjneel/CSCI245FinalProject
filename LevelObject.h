// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include <stdio.h>
#include "lexfile.h"

#ifndef LEVELOBJECT_H
#define	LEVELOBJECT_H

class Player;
class Room;

class LevelObject 
{
public:
   LevelObject(token t);
   LevelObject(token t, Room* r);
   bool IsVisible() const;
   void SetVisible();
   void SetBeneath(LevelObject* b);
   void SetRoom(Room* r);
   LevelObject* GetBeneath() const;
   Room* GetRoom() const;
   bool IsWalkable() const;
   token GetType() const;
private:
   token type;
   bool visible;
   Room* room;
   LevelObject* beneath;
};


class Gold : public LevelObject
{
public:
   Gold();
   Gold(Room* r);
   int GetGold();
};

   
class Trap : public LevelObject
{
public:
   Trap(token t);
   Trap(token t, Room* r);
   void Activate(Player p); 
};


class Tile : public LevelObject
{
public:
   bool IsWalkable() const;
   Tile(token t);
   Tile(token t, Room* r);
};


class Item : public LevelObject
{
public:
   Item(token t);
   Item(token t, Room* r);
};
 
class Diamond : public Item
{
public:
   Diamond();
   Diamond(Room* r);
};

class Consumable : public Item
{
public:
   Consumable(token t);
   Consumable(token t, Room* r);
};
   
   
   
   

#endif	/* LEVELOBJECT_H */

