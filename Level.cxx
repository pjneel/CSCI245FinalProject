// Student: Nick Tarter & Paul Neel
// Class: CSCI 245
// Assignment: 4

#include "Level.h"
#include "LevelObject.h"
#include "Monster.h"
#include "Room.h"
#include "Player.h"
#include "PlayArea.h"
#include "lexfile.h" // for token enumeration

//#include <typeinfo>
#include <time.h> // for seeding randomization
#include <cstdlib> // for random numbers??

using namespace std;

Level::Level()
{
   for (int i = 0; i < X_GRID_SIZE; i++)
   {
      for (int j = 0; j < Y_GRID_SIZE; j++)
      {
         grid[i][j] = NULL;
      }
   }
   xStart = -1;
   yStart = -1;     
}

void Level::DeleteAt(int xPosition, int yPosition)
{
   LevelObject* temp = grid[xPosition][yPosition];
   grid[xPosition][yPosition] = NULL;
   delete temp;
}

void Level::SetNullAt(int xPosition, int yPosition)
{
   grid[xPosition][yPosition] = NULL;
}

void Level::AddLevelObject(LevelObject* lo, int xPosition, int yPosition)
{
   if (grid[xPosition][yPosition] == NULL)
   {
      grid[xPosition][yPosition] = lo;      
      return;
   }
   
   token added = lo->GetType();
   token existing = grid[xPosition][yPosition]->GetType();
   
   if (existing == t_black) grid[xPosition][yPosition] = lo;
   else if (existing == t_diamond || existing == t_food || existing == t_sickness || existing == t_health || existing == t_gold)
   {
      grid[xPosition][yPosition]->SetBeneath(lo);
      if (added == t_white) grid[xPosition][yPosition]->SetRoom(lo->GetRoom());
   }
   else if (added == t_diamond || added == t_food || added == t_sickness || added == t_health || added == t_gold || added == t_arrow || added == t_transport)
   {
      lo->SetBeneath(grid[xPosition][yPosition]);      
      lo->SetRoom(grid[xPosition][yPosition]->GetRoom());
      grid[xPosition][yPosition] = lo;
   }
   else if (added == t_up || added == t_down) 
   {
      lo->SetRoom(grid[xPosition][yPosition]->GetRoom());
      grid[xPosition][yPosition] = lo;      
   }
   else if (added == t_path && existing == t_wall)
   {
      lo->SetRoom(grid[xPosition][yPosition]->GetRoom());
      grid[xPosition][yPosition] = lo;
   }
}

LevelObject* Level::ObjectAt(int xPosition, int yPosition) const
{
   return grid[xPosition][yPosition];
}

LevelObject* Level::RemoveItem(int xPosition, int yPosition)
{
   LevelObject* temp = grid[xPosition][yPosition];
   grid[xPosition][yPosition] = NULL;
   return temp;           
}

bool Level::IsWalkable(int xPosition, int yPosition) const
{
   token t = grid[xPosition][yPosition]->GetType();
   bool tileWalkable = true;
   if (t == t_wall || t == t_black) tileWalkable = false;

   return tileWalkable && !IsMonsterAt(xPosition, yPosition);   
}

bool Level::IsMonsterAt(int xPosition, int yPosition) const
{
   for (int i = 0; i < monsters.size(); i++)
   {
      if (monsters[i]->GetX() == xPosition and monsters[i]->GetY() == yPosition)
      {
         return true;        
      }
   }
   return false;   
}

Room* Level::AddRoom(int xPosition, int yPosition, int width, int height)
{   
   Room* temp = new Room(xPosition, yPosition, width, height);
   //rooms.push_back(temp);
   return temp;
}

void Level::SetStart(int xPosition, int yPosition)
{
   xStart = xPosition;
   yStart = yPosition;
}
void Level::GetStart(int &xPosition, int &yPosition)
{
   xPosition = this->xStart;
   yPosition = this->yStart;
}

bool Level::IsVisible(int xPosition, int yPosition) const
{
   return grid[xPosition][yPosition]->IsVisible();
}

Room* Level::GetRoom(int xPosition, int yPosition) const
{
   return ObjectAt(xPosition, yPosition)->LevelObject::GetRoom();
}

void Level::AddMonsterAt(int xPosition, int yPosition, MonsterType t)
{
   monsters.push_back(new Monster(xPosition, yPosition, t));
}

Monster* Level::GetMonster(int number)
{
   return monsters[number];
}

int Level::NumberMonsters() const
{
   return monsters.size();
}

void Level::MoveMonsters(Player* p)
{
   srand(time(NULL)); // initialize random seed  
   for (int a = 0; a < monsters.size(); a++)
   {  
      int xNew = monsters[a]->GetX();
      int yNew = monsters[a]->GetY();
      if (p->GetRoom() == monsters[a]->GetRoom()) // Check if monster is in the same room as the player.
      {          
         printf ("Monster #%d - in same room as player.\n", a);
         int move = (rand() % 12) + 1;
         if (move == 1) 
         {
            yNew--;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(NORTH);            
         }
         else if (move == 2) 
         {
            xNew++;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(EAST);
         }
         else if (move ==3) 
         {
            yNew++;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(SOUTH);
         }
         else if (move == 4) 
         {
            xNew--;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(WEST);
         }
         else if (move >= 7 && move <= 12)
         {
            //printf ("Monster #%d - Move towards player.\n", a);
            int dx = p->GetX() - xNew; 
            int dy = p->GetY() - yNew;
            if (abs(dx) > abs(dy)) 
            {
               if (dx < 0) 
               {
                  xNew--;
                  if (IsWalkable(xNew, yNew)) monsters[a]->Move(WEST); 
               }
               else 
               {
                  xNew++;
                  if (IsWalkable(xNew, yNew)) monsters[a]->Move(EAST);
               }                  
            }
            else
            {
               if (dy < 0) 
               {
                  yNew--;
                  if (IsWalkable(xNew, yNew)) monsters[a]->Move(NORTH);
               }                  
               else 
               {
                  yNew++;
                  if (IsWalkable(xNew, yNew)) monsters[a]->Move(SOUTH);
               }                  
            }            
         }         
      }
      else // Monster not in the same room
      {
         int move = (rand() % 6) + 1;
         if (move == 1)
         {
            
            yNew--;
            if (IsWalkable(xNew, yNew)) 
            {
               printf ("Move NORTH IsWalkable TRUE.\n");
               monsters[a]->Move(NORTH);      
            }       
         }
         else if (move == 2) 
         {
            printf ("Move EAST.\n");
            xNew++;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(EAST);
         }
         else if (move ==3) 
         {
            printf ("Move SOUTH.\n");
            yNew++;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(SOUTH);
         }
         else if (move == 4) 
         {
            printf ("Move WEST.\n");
            xNew--;
            if (IsWalkable(xNew, yNew)) monsters[a]->Move(WEST);
         }         
      }
      monsters[a]->SetRoom(ObjectAt(monsters[a]->GetX(), monsters[a]->GetY())->GetRoom());
      if (IsVisible(monsters[a]->GetX(), monsters[a]->GetY())) monsters[a]->SetVisible();
      else monsters[a]->SetInvisible();
   }
}






