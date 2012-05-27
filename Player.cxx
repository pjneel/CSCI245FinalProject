// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Player.h"

Player::Player()
{
	this->health = 10;
	this->gold = 0;
	this->hunger = 200;
	this->xPos = -1;
	this->yPos = -1;
	this->moveCount = 0;
	for(int i = 0; i < 10; i++) inventory[i] = NULL;
	this->room = NULL;
	//this->beneath = NULL;
}
Player::Player(int xPos, int yPos)
{
	this->health = 10;
	this->gold = 0;
	this->hunger = 200;
	this->xPos = xPos;
	this->yPos = yPos;
	this->moveCount = 0;
	for(int i = 0; i < 10; i++) inventory[i] = NULL;
	this->room = NULL;
	//this->beneath = NULL;
}

void Player::Move(direction d)
{
	// Level::ObjectAt will need to be called first to verify the move is valid
	if(d == NORTH) this->yPos -= 1;
	else if (d == SOUTH) this->yPos += 1;
	else if (d == WEST) this->xPos -= 1;
	else if (d == EAST) this->xPos += 1;
	
	// Need else statement here for invalid direction
	// Possibly change function from void to boolean and return false if error
}
void Player::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
}

void Player::Die() 
{
	this->health = 0;
}

bool Player::Pickup(Item* o) 
{
	bool isPlaced = false;
	for(int i = 0; i < 10 && !isPlaced; i++)
	{
		if (inventory[i] != NULL)
		{
			inventory[i] = o;
			isPlaced = true;
		}
	}
	return isPlaced;
}

void Player::Combat(Monster* m) 
{
	//I need to research the randomization of this
}

void Player::Consume(Consumable* c)
{
	// Need a method in consumables class to get food type
	//if (food) this->health = 200;
	//else if (baddrink) this->health -= 5;
	//else if (gooddrink) this->health = 10;
}
void Player::ChangeGold(int amount)
{
	this->gold += amount;
}
void Player::ChangeHealth(int amount)
{
	this->health += amount;
}
int Player::GetX()
{
	return this->xPos;
}
int Player::GetY()
{
	return this->yPos;
}
int Player::GetHunger()
{
	return this->hunger;
}
Room* Player::GetRoom()
{
	return this->room;
}
/*LevelObject* Player::GetBeneath()
{
	return this->beneath;
}*/
