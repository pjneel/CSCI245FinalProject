// Students: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4



#ifndef PLAYER_H
#define PLAYER_H

class LevelObject;
class Monster;
class Consumable;

class Player 
{
private:
	int health;
	int gold;
	Item inventory[10];
	int xPos;
	int yPos;
	int hunger;
	int moveCount;
public:
	Player();
	Player(int xPos, int yPos);
	void Move(int direction);
	void SetPosition(int x, int y);
	void Die();
	void Pickup(LevelObject o);
	void Combat(Monster m);
	void Consume(Consumable c);
	void ChangeGold(int amount);
	void ChangeHealth(int amount);
	int GetX();
	int GetY();
	int GetHunger();
};

#endif