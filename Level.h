// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Monster.h"

using namespace std;

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iostream>


const int X_GRID_SIZE = 50;
const int Y_GRID_SIZE = 40;

class LevelObject;
class Room;
class Player;

class Level
{
private:
	LevelObject* grid[X_GRID_SIZE][Y_GRID_SIZE];
	vector<Monster*> monsters;
	int xStart;
	int yStart;
public:
	Level();
	~Level();
	void AddLevelObject(LevelObject* lo, int xPosition, int yPosition);
	LevelObject* ObjectAt(int xPosition, int yPosition) const;
	LevelObject* RemoveItem(int xPosition, int yPosition);
	void DeleteAt(int xPosition, int yPosition);
	void SetNullAt(int xPosition, int yPosition);
   bool IsWalkable(int xPosition, int yPosition) const;
   bool IsMonsterAt(int xPosition, int yPosition) const;
   Monster* MonsterAt(int xPosition, int yPosition) const;
   void AddMonsterAt(int xPosition, int yPosition, MonsterType t, int level);
   Monster* GetMonster(int number);
   Room* AddRoom(int xPosition, int yPosition, int width, int height);
   void SetStart(int xPosition, int yPosition);
   void GetStart(int &xPosition, int &yPosition);
   void RemoveMonster(Monster* m);
   bool IsVisible(int xPosition, int yPosition) const;
   Room* GetRoom(int xPosition, int yPosition) const;
   int NumberMonsters() const;
   void MoveMonsters(Player* p);
};

#endif
