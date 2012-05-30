// game.cxx -- the implementation part of the interface


#include "game.h"
#include "gui.h"
#include "Level.h"
#include "LevelObject.h"
#include "Player.h"

#include <FL/fl_ask.H>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <typeinfo>
using namespace std;

// Utility routine:  called like printf.

const int MAX_LEVELS = 10;

void TokenSet(int x, int y, token tok)
{
   if (tok == t_gold) play_area->SetSquare(x, y, GOLD);
   else if (tok == t_diamond) play_area->SetSquare(x, y, DIAMOND);
   else if (tok == t_food) play_area->SetSquare(x, y, FOOD);
   else if (tok == t_health || tok == t_sickness) play_area->SetSquare(x, y, DRINK);
   else if (tok == t_arrow) play_area->SetSquare(x, y, ATRAP);
   else if (tok == t_transport) play_area->SetSquare(x, y, TTRAP);
   else if (tok == t_white) play_area->SetSquare(x, y, WHITE);
   else if (tok == t_wall) play_area->SetSquare(x, y, WALL);             
   else if (tok == t_path) play_area->SetSquare(x, y, PATH);
   else if (tok == t_wall) play_area->SetSquare(x, y, WALL);
   else if (tok == t_up) play_area->SetSquare(x, y, GOUP);
   else if (tok == t_down) play_area->SetSquare(x, y, GODOWN);
   else if (tok == t_black) play_area->SetSquare(x, y, BLACK);      
}

void Game::DrawFresh()
{  
   // Draw level
   token tok;
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         LevelObject* spot = levels[currentLevel]->ObjectAt(x, y);
         if (!levels[currentLevel]->IsVisible(x, y)) play_area->SetSquare(x, y, BLACK);
         else
         {       
            tok = spot->GetType();
            TokenSet(x, y, tok);   
         }
         if (spot->GetType() == t_arrow || spot->GetType() == t_transport)
         {
            if ((!spot->IsVisible()) && spot->GetBeneath()->IsVisible()) TokenSet(x, y, spot->GetBeneath()->GetType());
         }
      }
   }
   
   // Draw monsters
   for (int a = 0; a < levels[currentLevel]->NumberMonsters(); a++)
   {
      Monster* m = levels[currentLevel]->GetMonster(a);
      if (m->GetType() == M_SNAKE) play_area->SetSquare(m->GetX(), m->GetY(), SNAKE);
      else if (m->GetType() == M_RAT) play_area->SetSquare(m->GetX(), m->GetY(), RAT);      
   }
   
   // Draw player
   int x = player->GetX();
   int y = player->GetY();
   play_area ->SetSquare(x, y, PLAYER); 
}

void Game::error(char *fmt, ...)
{
  va_list ap;
  char mesg[1024]; 

  had_error = true;
  va_start(ap,fmt);
  vsnprintf (mesg, 1024, fmt, ap);
  va_end(ap);
  cerr << mesg << endl; 
}

// All routines from here on need to be changed by the student!

// Routines to build the game

void Game::SetBuildLevel (int newlevel)
{ 
   if (debug) printf ("SetBuildLevel -> %d.\n", newlevel);
   levels[newlevel] = new Level();
   currentLevel = newlevel;
   Tile* black = new Tile(t_black);
   black->SetVisible();   
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         levels[currentLevel]->AddLevelObject(black, x, y);
      }    
   }  
}

void Game::NewRoom (int x, int y, int width, int height)
{
   if (debug) printf ("NewRoom(%d,%d,%d,%d)\n", x, y, width, height);      
   Room* r = levels[currentLevel]->AddRoom(x, y, width, height);
   Tile* wall = new Tile(t_wall, r);
   Tile* white = new Tile(t_white, r);    

   // Top and Bottom Walls 
   for (int i = x; i < x + width; i++)
   {
      if (levels[currentLevel]->ObjectAt(i,y)->GetType() == t_black) levels[currentLevel]->AddLevelObject(wall, i, y);
      //if (debug) printf ("Placing wall at x:%d y: %d\n", i, y + height - 1);
      if (levels[currentLevel]->ObjectAt(i,y + height - 1)->GetType() == t_black) levels[currentLevel]->AddLevelObject(wall, i, y + height - 1);
   }
   
   // Left and Right Walls
   for (int j = y + 1; j < y + height; j++)
   {
      if (levels[currentLevel]->ObjectAt(x, j)->GetType() == t_black) levels[currentLevel]->AddLevelObject(wall, x, j);
      if (levels[currentLevel]->ObjectAt(x + width - 1, j)->GetType() == t_black) levels[currentLevel]->AddLevelObject(wall, x + width - 1, j); 
   }
   
   // Fill room with white
   for (int i = x + 1; i < x + width - 1; i++)
   {
      for (int j = y + 1; j < y + height - 1; j++)levels[currentLevel]->AddLevelObject(white, i, j);
   }   
}

void Game::NewPath (int x1, int y1, int x2, int y2)
{
   if (debug) printf ("NewPath: (%d,%d) -> (%d,%d)\n", x1, y1, x2, y2);
   
   // Vertical path
   if (x1 == x2)
   {
      if (y1 < y2)
      {
         for (int j = y1; j <= y2; j++) 
         {
            Tile* t = new Tile(t_path);
            levels[currentLevel]->AddLevelObject(t, x1, j);  
         }
      }
      else // y1 >= y2
      {
         for (int j = y2; j <= y1; j++)
         {          
            Tile* t = new Tile(t_path);
            levels[currentLevel]->AddLevelObject(t, x1, j);
         }    
      }
   }
   // Horizontal path
   else // y1 == y2
   {
      if (x1 < x2)
      {
         for (int i = x1; i <= x2; i++)
         {  
            Tile* t = new Tile(t_path);
            levels[currentLevel]->AddLevelObject(t, i, y1);
         }
      }
      else // x1 >= x2
      {
         for (int i = x2; i <= x1; i++)
         {
            Tile* t = new Tile(t_path);
            levels[currentLevel]->AddLevelObject(t, i, y1);
         }
      }
   }
}  

void Game::SetStart (int x, int y)
{
  if (debug) printf ("Level starts at (%d,%d)\n", x, y);
  levels[currentLevel]->SetStart(x, y);
}

void Game::PlaceAt (token what, int x, int y)
{
   if (debug) printf ("Place %s at (%d,%d)\n", tok_name[what], x, y);
   //if (debug && what == t_diamond)
   //printf ("Place the diamond at (%d,%d)...\n", x, y);

   Level* lvl = levels[currentLevel];
   if (what == t_diamond) lvl->AddLevelObject(new Diamond(), x, y);
   else if (what == t_gold) lvl->AddLevelObject(new Gold(), x,  y);
   else if (what == t_up) lvl->AddLevelObject(new Tile(t_up), x, y);
   else if (what == t_down) lvl->AddLevelObject(new Tile(t_down), x, y);
   else if (what == t_arrow) lvl->AddLevelObject(new Trap(t_arrow), x, y);  
   else if (what == t_arrow) lvl->AddLevelObject(new Trap(t_arrow), x, y);
   else if (what == t_transport) lvl->AddLevelObject(new Trap(t_transport), x, y);
   else if (what == t_sickness) lvl->AddLevelObject(new Consumable(t_sickness), x, y);
   else if (what == t_health) lvl->AddLevelObject(new Consumable(t_health), x, y);
   else if (what == t_food) lvl->AddLevelObject(new Consumable(t_food), x, y);
   else if (what == t_snake) lvl->AddMonsterAt(x, y, M_SNAKE);
   else if (what == t_rat) lvl->AddMonsterAt(x, y, M_RAT); 
}

// Routines to play the game

void Game::start(void)
{

   playing = true;
   currentLevel = 0;   
  // The following shows you how to set some elements of the gui.
  // YOU NEED TO REPLACE THIS WITH YOUR REAL START CODE ...

  gui_level->value("1");
  gui_health->value("10/10");
  gui_gold->value("0");

  gui_message("Welcome to the game!");
   
   // Player position
   int xS, yS;
   levels[currentLevel]->GetStart(xS, yS);
   player->SetPosition(xS, yS);
   player->SetRoom(levels[currentLevel]->GetRoom(xS, yS));
   
   Visibility();
   
   token tok;
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         if (!levels[currentLevel]->IsVisible(x, y)) play_area->SetSquare(x, y, BLACK);
         else
         {
            LevelObject* thing = levels[currentLevel]->ObjectAt(x, y);
            
            tok = thing->GetType();
            TokenSet(x, y, tok);   
         }
      }
   }
   
   play_area ->SetSquare(xS, yS, PLAYER);
      
   // Monster positions
   for (int a = 0; a < levels[currentLevel]->NumberMonsters(); a++)
   {
      Monster* m = levels[currentLevel]->GetMonster(a);
      if (m->GetType() == M_SNAKE) play_area->SetSquare(m->GetX(), m->GetY(), SNAKE);
      else if (m->GetType() == M_RAT) play_area->SetSquare(m->GetX(), m->GetY(), RAT); 
      m->SetRoom(levels[currentLevel]->GetRoom(m->GetX(), m->GetY()));     
   }
   
   //for(int x = 0; x < 50; x++)
   //{
      //for(int y = 0; y < 40; y++) if (debug) printf("Object at %d, %d is %d\n", x, y, levels[currentLevel]->ObjectAt(x,y)->GetType());
   //} 
   DrawFresh();
}

void Game::quit(void)
{
  if (!playing || (fl_choice ("Quit the game?","yes","no",NULL)==0))
    exit(0);
}

void Game::inventory(void)
{
   CHECK_PLAYING;
   gui_message("---------------------");
   for (int n = 0; n < INV_SIZE; n++)
   {
      Item* i = player->GetItem(n);
      if (i == NULL) gui_message("Slot %d - Empty", n + 1);
      else 
      {
         token t = i->GetType();
         if (t == t_diamond) gui_message("Slot %d - Diamond", n + 1);
         else if (t == t_food) gui_message("Slot %d - Food", n + 1);
         else if (t == t_sickness || t == t_health) gui_message("Slot %d - Drink", n + 1);      
      }
   }
   gui_message("---------------------");
}

void Game::drop(void)
{
   CHECK_PLAYING; 
   int x = player->GetX();
   int y = player->GetY();
   
   int index;   
   int nFields = sscanf(gui_in->value(), "%d", &index);
   
   if (nFields == 0 || index < 1 || index > 10)
   {
      gui_message("Enter the slot # you want to drop(1-10).");
      return;
   }
   index--; // Decrement to match inventory array indexing
   
   Item* i = player->GetItem(index);
   
   if (i == NULL) 
   {
      gui_message("Slot %d is empty.", index + 1);
      return;
   }
      
   token t = levels[currentLevel]->ObjectAt(x, y)->GetType();
   if (t == t_path || t == t_white)
   {
      LevelObject* l = (LevelObject*)i;
      levels[currentLevel]->AddLevelObject(l, x, y);
      player->SetNullInv(index);
      if (i->GetType() == t_diamond) gui_message("You dropped the diamond.");
      else if (i->GetType() == t_food) gui_message("You dropped some food.");
      else if (i->GetType() == t_sickness || t == t_health) gui_message("You dropped a drink.");
   }
   else gui_message("This spot is occupied."); 

  //gui_message("drop -> %s", gui_in->value());
  // clear the gui_in element
  gui_in->value("");
}

void Game::eat(void)
{
   CHECK_PLAYING;
      
   for (int n = 0; n < INV_SIZE; n++)   
   {
      Item* i = player->GetItem(n);
      if (i != NULL)
      {
         if (i->GetType() == t_food)
         {
            player->FillHunger();
            player->SetNullInv(n);
            delete i;
            gui_message("You ate some food.");
            return;
         }
      }
   }
   gui_message("You don't have any food.");
}

void Game::drink(void)
{
   CHECK_PLAYING;
   for (int n = 0; n < INV_SIZE; n++)   
   {
      Item* i = player->GetItem(n);
      if (i != NULL)
      {
         if (i->GetType() == t_sickness || i->GetType() == t_health)
         {         
            if (i->GetType() == t_health)
            {
               player->FillHealth();
               gui_message("You drank a tasty brew");
            }
            else 
            {
               player->ChangeHealth(-5);
               gui_message("You drank poison!");
            }
            
            // Update gui health         
            char buffer[10];
            snprintf(buffer, 10, "%d/10", player->GetHealth());
            gui_health->value(buffer);  
            
            player->SetNullInv(n);
            delete i;
            return;
         }
      }
   }
   gui_message("You don't have any drinks.");


  gui_in->value("");
}

void Game::move (direction dir)
{
   CHECK_PLAYING;
   if (debug) printf ("Move %d\n", dir);
  
   int xNew = player->GetX();
   int yNew = player->GetY();
   if (dir == NORTH) 
   {
      yNew--;
      if (yNew < 0) return;
   }
   else if (dir == SOUTH) 
   {
      yNew++;
      if (yNew >= Y_GRID_SIZE) return;
   }
   else if (dir == WEST) 
   {
      xNew--;
      if (xNew < 0) return;
   }
   else if (dir == EAST) 
   {
      xNew++;
      if (xNew >= X_GRID_SIZE) return;
   }
   else 
   {
      token t = levels[currentLevel]->ObjectAt(xNew, yNew)->GetType();
      if (dir == UP && t == t_up && currentLevel > 0)
      {
         currentLevel--;
         int xStart, yStart;
         levels[currentLevel]->GetStart(xStart, yStart);
         player->SetPosition(xStart, yStart);
         player->SetRoom(levels[currentLevel]->ObjectAt(xStart, yStart)->GetRoom());
         Visibility();
         Game::DrawFresh();
         return;
      }
      else if (dir == DOWN && t == t_down && currentLevel < MAX_LEVELS)
      {
         currentLevel++;
         int xStart, yStart;
         levels[currentLevel]->GetStart(xStart, yStart);
         player->SetPosition(xStart, yStart);
         player->SetRoom(levels[currentLevel]->ObjectAt(xStart, yStart)->GetRoom());
         Visibility();
         Game::DrawFresh();
         return;
      }      
   }
      
   token temp = levels[currentLevel]->ObjectAt(xNew, yNew)->GetType();
   if (temp == t_black || temp == t_wall) return;   
  

   player->Move(dir);
   int x = player->GetX();
   int y = player->GetY();
   token tok = levels[currentLevel]->ObjectAt(x, y)->GetType();
   TokenSet(x, y, tok);
   player->SetRoom(levels[currentLevel]->ObjectAt(x, y)->GetRoom());
   play_area->SetSquare(player->GetX(), player->GetY(), PLAYER);
   levels[currentLevel]->MoveMonsters(player);
   Visibility();
   if (tok == t_gold)
   {
      
      LevelObject* money = levels[currentLevel]->ObjectAt(x, y);
      Gold* coins = (Gold*)money;
      LevelObject* under = money->GetBeneath();
      int amount = coins->GetGold();
      player->ChangeGold(amount);
      levels[currentLevel]->DeleteAt(x,y);
      levels[currentLevel]->AddLevelObject(under, x, y);
            
      char buffer[10];
      snprintf(buffer, 10, "%d", player->GetGold());
      gui_gold->value(buffer);
      gui_message("You found %d gold!", amount);
   }
   else if (tok == t_food || tok == t_sickness || tok == t_health || tok == t_diamond)
   {
      if (debug) printf ("Item found.\n");
      LevelObject* l = levels[currentLevel]->ObjectAt(x, y);
      Item* i = (Item*)l;
      if (player->Pickup(i))
      {         
         if (debug) printf ("Item picked up.\n");
         LevelObject* under = l->GetBeneath();
         levels[currentLevel]->SetNullAt(x, y);
         levels[currentLevel]->AddLevelObject(under, x, y); 
         if (tok == t_food) gui_message("You picked up some food!");
         else if (tok == t_diamond) gui_message("You picked up the diamond!");
         else gui_message("You picked up a drink!");         
      }            
      else gui_message("Your inventory is full!");
   }
   else if (tok == t_arrow || tok == t_transport )
   {
      LevelObject* l = levels[currentLevel]->ObjectAt(x, y);
      Trap* t = (Trap*)l;
      l->SetVisible();      
      t->Activate(player);
      
      if (tok == t_arrow)
      {
         gui_message("You were hit by an arrow trap!");
         char buffer[10];
         snprintf(buffer, 10, "%d/10", player->GetHealth());
         gui_health->value(buffer);  
      }
      else if (tok = t_trap)
      {
         while(!levels[currentLevel]->IsWalkable(player->GetX(), player->GetY())) t->Activate(player); 
         gui_message("You stumbled into a transport trap!");
      }
      Visibility();     
   }
   
   Game::DrawFresh();
}

void Game::Visibility()
{
   int px = player->GetX();
   int py = player->GetY();
   LevelObject* standingAt = levels[currentLevel]->ObjectAt(px, py);
   
   if (!standingAt->IsVisible()) // if the object where the player is standing is not visible
   {
      standingAt->SetVisible();
      if (standingAt->GetRoom() != NULL) // if in a room
      {
         // Set LevelObjects associated with this room to visible
         Room* r = standingAt->GetRoom();
         for (int x = 0; x < X_GRID_SIZE; x++)
         {
            for (int y = 0; y < Y_GRID_SIZE; y++)
            {
               LevelObject* spot = levels[currentLevel]->ObjectAt(x,y);
               if (levels[currentLevel]->GetRoom(x, y) == r)     
               {
                  if (spot->GetType() != t_arrow && spot->GetType() != t_transport) 
                  {
                     LevelObject* spot = levels[currentLevel]->ObjectAt(x, y);
                     spot->SetVisible();
                  }
                  if (spot->GetBeneath() != NULL) spot->GetBeneath()->SetVisible();                  
               }
            }
         }
      }
   }
   if (player->GetRoom() == NULL) // check the 4 directions to the range of what is visible
   {
      int dx = px;
      int dy = py;
      
      // Check North
      dy--;
      while (dy >= 0 && !levels[currentLevel]->ObjectAt(px, dy)->IsVisible() && levels[currentLevel]->ObjectAt(px, dy)->GetRoom() == NULL) 
      {
         levels[currentLevel]->ObjectAt(px, dy)->SetVisible();
         dy--;
      }         
      
      // Check South
      dy = py;
      dy++;
      while (dy < Y_GRID_SIZE && !levels[currentLevel]->ObjectAt(px, dy)->IsVisible() && levels[currentLevel]->ObjectAt(px, dy)->GetRoom() == NULL) 
      {
         levels[currentLevel]->ObjectAt(px, dy)->SetVisible();
         dy++;
      }
      
      // Check West
      dx--;
      while (dx >= 0 && !levels[currentLevel]->ObjectAt(dx, py)->IsVisible() && levels[currentLevel]->ObjectAt(dx, py)->GetRoom() == NULL) 
      {
         levels[currentLevel]->ObjectAt(dx, py)->SetVisible();
         dx--;
      }        
      
      // Check East
      dx = px;
      dx++;
      while (dx < X_GRID_SIZE && !levels[currentLevel]->ObjectAt(dx, py)->IsVisible() && levels[currentLevel]->ObjectAt(dx, py)->GetRoom() == NULL) 
      {
         levels[currentLevel]->ObjectAt(dx, py)->SetVisible();
         dx++;
      }           
   }
}

Game::Game()
{
   had_error = false;
   playing = false;
   for (int i = 0; i < MAX_LEVELS; i++)
   {
      levels[i] = NULL;
   }
   currentLevel = -1;
   player = new Player();
}




