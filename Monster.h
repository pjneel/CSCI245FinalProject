// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "game.h"  // for direction enumeration

#ifndef MONSTER_H
#define	MONSTER_H

class Player;
class Room;
class LevelObject;

enum MonsterType {M_RAT, M_SNAKE};

class Monster
{
public:
   Monster(int x, int y, MonsterType t, int level);
   ~Monster();
   MonsterType GetType() const;   
   void SetVisible();
   void SetInvisible();
   void Move(direction d);   
   void ChangeHealth(int h);
   int GetHealth() const;
   int Combat(Player* p);   
   void SetRoom(Room* r);
   int GetX() const;
   int GetY() const;
   bool IsVisible() const;
   Room* GetRoom() const;
private:
   MonsterType type;
   int health;   
   bool visible;
   Room* room;
   int xPosition;
   int yPosition;
};
#endif	/* MONSTER_H */

