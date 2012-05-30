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
	if(d == NORTH) this->yPos -= 1;
	else if (d == SOUTH) this->yPos += 1;
	else if (d == WEST) this->xPos -= 1;
	else if (d == EAST) this->xPos += 1;
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
	for(int i = 0; i < INV_SIZE && !isPlaced; i++)
	{
		if (inventory[i] == NULL)
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

void Player::FillHealth()
{
   health = MAX_HEALTH;
}

void Player::SetRoom(Room* r)
{
   room = r;
}

void Player::SetNullInv(int n)
{
   inventory[n] = NULL;
}

void Player::ChangeHunger(int n)
{
   hunger += n;
}

void Player::FillHunger()
{
   hunger = MAX_HUNGER;
}

Item* Player::GetItem(int n) const
{
   return inventory[n];
}

int Player::GetGold() const
{
   return gold;
}

int Player::GetX() const
{
	return this->xPos;
}

int Player::GetY() const
{
	return this->yPos;
}

int Player::GetHunger() const
{
	return this->hunger;
}

int Player::GetHealth() const
{
   return this->health;
}

Room* Player::GetRoom() const
{
	return this->room;
}

