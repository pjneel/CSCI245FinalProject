// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4



using namespace std;

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iostream>
#include "LevelObject.h"
#include "Monster.h"
#include "Room.h"

const int X_GRID_SIZE = 50;
const int Y_GRID_SIZE = 40;

//class LevelObject;
//class Monster;
//class Room;

class Level
{
private:
	LevelObject* grid[X_GRID_SIZE][Y_GRID_SIZE];
	vector<Monster> monsters;
	vector<Room> rooms;
	int xStart;
	int yStart;
public:
	Level();
	void AddItem(LevelObject* lo, int xPosition, int yPosition);
	LevelObject* ObjectAt(int xPosition, int yPosition) const;
	LevelObject* RemoveItem(int xPosition, int yPosition);
   bool IsWalkable(int xPosition, int yPosition) const;
   bool IsMonsterAt(int xPosition, int yPosition) const;
   void AddRoom(int xPosition, int yPosition, int width, int height);
   void SetStart(int xPosition, int yPosition);
};

#endif
