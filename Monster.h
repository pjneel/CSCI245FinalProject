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
   Monster(int x, int y, MonsterType t);
   MonsterType GetType() const;   
   void Move(direction d);   
   void ChangeHealth(int h);   
   void Combat(Player p);   
   int GetX() const;
   int GetY() const;
   Room* GetRoom() const;
private:
   MonsterType type;
   int health;   
   Room* room;
   LevelObject* beneath;
   int xPosition;
   int yPosition;
};
#endif	/* MONSTER_H */

