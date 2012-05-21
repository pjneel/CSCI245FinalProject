// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#ifndef MONSTER_H
#define	MONSTER_H

class Player;

enum MonsterType {M_RAT, M_SNAKE};

class Monster
{
public:
   MonsterType GetType() const;   
   void Move(int direction);   
   void ChangeHealth(int health);   
   void Combat(Player p);   
private:
   MonsterType type;
   int health;   
   Room* room;
   LevelObject* beneath;

};
#endif	/* MONSTER_H */

