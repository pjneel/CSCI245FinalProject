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
#include "game.h"

//#include <typeinfo>
#include <time.h> // for seeding randomization
#include <cstdlib> // for random numbers??
#include "gui.h"

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

Level::~Level()
{
   vector<LevelObject*> deleted;
   vector<Room*> deletedRooms;
   for(int i = 0; i < X_GRID_SIZE; i++)
   {
      for (int j = 0; j < Y_GRID_SIZE; j++)
      {
         bool foundLO = false;
         bool foundRoom = false;
         bool foundBeneath = false;
         for(int k = 0; k < deleted.size(); k++)
         {            
            if (deleted[k] == grid[i][j]) foundLO = true;
            if (deleted[k] == grid[i][j]->GetBeneath()) foundBeneath = true;
         }
         if (!foundBeneath && grid[i][j]->GetBeneath() != NULL)
         {
            deleted.push_back(grid[i][j]->GetBeneath());
         }
         if (!foundLO)
         {
            deleted.push_back(grid[i][j]);
            for(int t = 0; t < deletedRooms.size(); t++)
            {
               if (deletedRooms[t] == grid[i][j]->GetRoom())
               {
                  foundRoom = true;
               }
            }
            if (!foundRoom)
            {
               deletedRooms.push_back(grid[i][j]->GetRoom());
               grid[i][j]->SetRoom(NULL);
            }
         }
         grid[i][j] = NULL;
      }
   }
   
   for(int i = 0; i < deletedRooms.size(); i++) delete deletedRooms[i];
   for(int i = 0; i < deleted.size(); i++) delete deleted[i];
}

// DeleteAt - Set a grid position to NULL and delete the object.
void Level::DeleteAt(int xPosition, int yPosition)
{
   LevelObject* temp = grid[xPosition][yPosition];
   grid[xPosition][yPosition] = NULL;
   delete temp;
}

// SetNullAt - Set a grid position to NULL 
void Level::SetNullAt(int xPosition, int yPosition)
{
   grid[xPosition][yPosition] = NULL;
}

// AddLevelObject - Add new objects to the grid.
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

// IsWalkable - Check if a position is available to be moved into
bool Level::IsWalkable(int xPosition, int yPosition) const
{
   if (!(xPosition < X_GRID_SIZE && yPosition < Y_GRID_SIZE)) return false;
   else if (!(xPosition >= 0 && yPosition >= 0)) return false;

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

Monster* Level::MonsterAt(int xPosition, int yPosition) const
{
   for(int i = 0; i < monsters.size(); i++)
   {
      if (monsters[i]->GetX() == xPosition and monsters[i]->GetY() == yPosition) return monsters[i];
   }
   return NULL;
}

Room* Level::AddRoom(int xPosition, int yPosition, int width, int height)
{   
   Room* temp = new Room(xPosition, yPosition, width, height);
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

void Level::AddMonsterAt(int xPosition, int yPosition, MonsterType t, int level)
{
   monsters.push_back(new Monster(xPosition, yPosition, t, level));
}

Monster* Level::GetMonster(int number)
{
   return monsters[number];
}

int Level::NumberMonsters() const
{
   return monsters.size();
}

void Level::RemoveMonster(Monster* m)
{
   gui_message("Monster is dead!");
   for(int i = 0; i < monsters.size(); i++)
   {
      if (monsters[i] == m)
      {
         delete monsters[i];
         monsters.erase(monsters.begin()+i);
         return;
      }
   }
}

// MoveMonsters - Handles movement for monsters checking for player in the same room and combat.
void Level::MoveMonsters(Player* p)
{
   srand(time(NULL)); // initialize random seed  
   for (int a = 0; a < monsters.size(); a++)
   {        
      int xNew = monsters[a]->GetX();
      int yNew = monsters[a]->GetY();
      
      bool combat = false;
      //gui_message("Player at %d, %d. Monster at %d, %d.", p->GetX(), p->GetY(), xNew, yNew);
      if (xNew == p->GetX() - 1 && yNew == p->GetY()) combat = true;
      else if (xNew == p->GetX() + 1 && yNew == p->GetY()) combat = true;
      else if (yNew == p->GetY() - 1 && xNew == p->GetX()) combat = true;
      else if (yNew == p->GetY() + 1 && xNew == p->GetX()) combat = true;
      
      if (combat)
      {
         gui_message("Monster attacks player!");
         if (debug) printf ("Monster attacks player!\n");
         int result = monsters[a]->Combat(p);
         if (result >= 1) 
         {
            gui_message("Monster hit player for %d damage!", result);
            char buffer[10];
            snprintf(buffer, 10, "%d/10", p->GetHealth());
            gui_health->value(buffer);
            if (p->GetHealth() < 1) return;            
         }
         
         else if (result <= -1)
         {
            gui_message("Player hit monster for %d damage!", abs(result));
            if (monsters[a]->GetHealth() < 1) RemoveMonster(monsters[a]);
         }
         else 
         {
            gui_message("Both missed.");
         }
      }
      else if (monsters[a]->GetRoom() != NULL && p->GetRoom() == monsters[a]->GetRoom()) // Check if monster is in the same room as the player.
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






