// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
	int xPos;
	int yPos;
	int xSize;
	int ySize;
public:
	Room(int xPos, int yPos, int xSize, int ySize);
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;
};


#endif	/* ROOM_H */

