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
//const int X_GRID_SIZE = 50;
//const int Y_GRID_SIZE = 40;

/*bool ObjectEquals(LevelObject* lo, char* c)
{
   return (strcmp(typeid(*lo).name(), c) == 0);
}*/

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
   token tok;
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         //if (levels[currentLevel]->IsVisible(x, y)) play_area->SetSquare(x, y, BLACK);
         //else
         //{
            LevelObject* thing = levels[currentLevel]->ObjectAt(x, y);
            
            tok = thing->GetType();
            TokenSet(x, y, tok);   
      }
   }
   
   // Player position
   int xS, yS;
   levels[currentLevel]->GetStart(xS, yS);
   player->SetPosition(xS, yS);
   play_area ->SetSquare(xS, yS, PLAYER);   
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
   levels[currentLevel]->AddRoom(x, y, width, height);
   if (debug) printf ("Room placed!");
   Tile* wall = new Tile(t_wall);
   

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
      if (levels[currentLevel]->ObjectAt(x, j)->GetType() == t_black) levels[currentLevel]->AddLevelObject(new Tile(t_wall), x, j);
      if (levels[currentLevel]->ObjectAt(x + width - 1, j)->GetType() == t_black) levels[currentLevel]->AddLevelObject(new Tile(t_wall), x + width - 1, j); 
   }
   // Room Filling
   for (int i = x + 1; i < x + width - 1; i++)
   {
      /*if (levels[currentLevel]->ObjectAt(i, j)->GetType() == t_black || levels[currentLevel]->ObjectAt(i, j) == NULL)*/ 
      for (int j = y + 1; j < y + height - 1; j++)levels[currentLevel]->AddLevelObject(new Tile(t_white), i, j);
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
  
   token tok;
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         //if (levels[currentLevel]->IsVisible(x, y)) play_area->SetSquare(x, y, BLACK);
         //else
         //{
            LevelObject* thing = levels[currentLevel]->ObjectAt(x, y);
            
            tok = thing->GetType();
            TokenSet(x, y, tok);   
      }
   }
   
   // Player position
   int xS, yS;
   levels[currentLevel]->GetStart(xS, yS);
   player->SetPosition(xS, yS);
   play_area ->SetSquare(xS, yS, PLAYER);
   
   for (int a = 0; a < levels[currentLevel]->NumberMonsters(); a++)
   {
      Monster* m = levels[currentLevel]->GetMonster(a);
      if (m->GetType() == M_SNAKE) play_area->SetSquare(m->GetX(), m->GetY(), SNAKE);
      else if (m->GetType() == M_RAT) play_area->SetSquare(m->GetX(), m->GetY(), RAT);      
   }
   
   //for(int x = 0; x < 50; x++)
   //{
      //for(int y = 0; y < 40; y++) if (debug) printf("Object at %d, %d is %d\n", x, y, levels[currentLevel]->ObjectAt(x,y)->GetType());
   //}
 

/*         
   int x, y;

  for (x = 0; x<50; x++) play_area->SetSquare(x,2,WHITE);
  for (x = 0; x<50; x++) play_area->SetSquare(x,4,WALL);
  for (x = 0; x<50; x++) play_area->SetSquare(x,6,PATH);
  for (x = 0; x<50; x++) play_area->SetSquare(x,8,DIAMOND);
  for (x = 0; x<50; x++) play_area->SetSquare(x,10,GOLD);
  for (x = 0; x<50; x++) play_area->SetSquare(x,12,FOOD);
  for (x = 0; x<50; x++) play_area->SetSquare(x,13,ATRAP);
  for (x = 0; x<50; x++) play_area->SetSquare(x,14,DRINK);
  for (x = 0; x<50; x++) play_area->SetSquare(x,15,TTRAP);
  for (x = 0; x<50; x++) play_area->SetSquare(x,16,SNAKE);
  for (x = 0; x<50; x++) play_area->SetSquare(x,17,RAT);

  for (x=10; x<30; x++)
    for ( y=20; y<27; y++)
      play_area->SetSquare(x, y,
			   (x==10 || x== 29 || y==20 || y==26 ? WALL
			    : WHITE));
  play_area->SetSquare(15, 22, GOUP);
  play_area->SetSquare(25, 24, GODOWN);
  play_area->SetSquare(20, 23, PLAYER);

  // End of code you need to replace ....
*/  
}

void Game::quit(void)
{
  if (!playing || (fl_choice ("Quit the game?","yes","no",NULL)==0))
    exit(0);
}

void Game::inventory(void)
{
  CHECK_PLAYING;
  gui_message("You are carrying nothing!");
}

void Game::drop(void)
{
  CHECK_PLAYING;

  gui_message("drop -> %s", gui_in->value());
  // clear the gui_in element
  gui_in->value("");
}

void Game::eat(void)
{
  CHECK_PLAYING;

  gui_message ("eat -> %s", gui_in->value());
  // clear the gui_in element
  gui_in->value("");
}

void Game::drink(void)
{
  CHECK_PLAYING;

  gui_message("drink -> %s", gui_in->value());
  // clear the gui_in element
  gui_in->value("");
}

void Game::move (direction dir)
{
   CHECK_PLAYING;
   if (debug)
      printf ("Move %d\n", dir);
   gui_message("move -> %d", dir);
  
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
         Game::DrawFresh();
         return;
      }
      else if (dir == DOWN && t == t_down && currentLevel < MAX_LEVELS)
      {
         currentLevel++;
         int xStart, yStart;
         levels[currentLevel]->GetStart(xStart, yStart);
         player->SetPosition(xStart, yStart);
         Game::DrawFresh();
         return;
      }      
   }  
      
   token temp = levels[currentLevel]->ObjectAt(xNew, yNew)->GetType();
   if (temp == t_black || temp == t_wall) return;   
  
   int x = player->GetX();
   int y = player->GetY();
   token tok = levels[currentLevel]->ObjectAt(x, y)->GetType();
   TokenSet(x, y, tok);
   player->Move(dir);
   play_area->SetSquare(player->GetX(), player->GetY(), PLAYER);
   levels[currentLevel]->MoveMonsters(player);
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




