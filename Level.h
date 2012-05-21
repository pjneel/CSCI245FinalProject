// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4



using namespace std;

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iostream>

class LevelObject;
class Monster;

class Level
{
private:
	LevelObject* grid[50][40];
	vector<Monster> monsters;
	vector<Room> rooms;
	int xStart;
	int yStart;
public:
	Level();
	void AddItem(LevelObject* lo, int xPosition, int yPosition);
	LevelObject ObjectAt(int xPosition, int yPosition);
	LevelObject RemoveItem(int xPosition, int yPosition);
   bool IsWalkable(int xPosition, int yPosition);
   bool IsMonsterAt(int xPosition, int yPosition);
   void AddRoom(int xPosition, int yPosition, int width, int height);
   void SetStart(int xPosition, int yPosition);
};

#endif
