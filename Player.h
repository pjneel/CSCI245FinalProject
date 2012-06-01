// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#ifndef PLAYER_H
#define PLAYER_H

#include "LevelObject.h"
#include "game.h" // for direction enumeration

const int INV_SIZE = 10;
const int MAX_HEALTH = 10;
const int MAX_HUNGER = 200;


//class LevelObject;
class Monster;
//class Consumable;
//class Item;
class Room;

class Player 
{
private:
	int health;
	int gold;
	Item* inventory[INV_SIZE];
	int xPos;
	int yPos;
	int hunger;
	int moveCount;
	Room* room;
public:
	Player();
	Player(int xPos, int yPos);
	void Move(direction d);
	void SetPosition(int x, int y);
	void Die();
	bool Pickup(Item* o);
	int Combat(Monster* m);
	void Consume(Consumable* c);
	void ChangeGold(int amount);
	void ChangeHealth(int amount);
	void FillHealth();
	void ChangeHunger(int amount);
	void FillHunger();
	void SetRoom(Room* r);
	void SetNullInv(int n);
	Item* GetItem(int n) const;
	int GetGold() const;
	int GetX() const;
	int GetY() const;
	int GetHunger() const;
	int GetHealth() const;
	Room* GetRoom() const;
	bool HasDiamond() const;	
};

#endif
