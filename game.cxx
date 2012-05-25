// game.cxx -- the implementation part of the interface


#include "game.h"
#include "gui.h"
#include "Level.h"
#include "LevelObject.h"


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

bool ObjectEquals(LevelObject* lo, char* c)
   {
      return (strcmp(typeid(*lo).name(), c) == 0);
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
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         levels[currentLevel]->AddLevelObject(new Tile(T_BLACK), x, y);
      }    
   }  
   levels[currentLevel]->AddLevelObject(new Trap(), 49, 38);      
   levels[currentLevel]->AddLevelObject(new Gold(), 49, 39);  
   
}

void Game::NewRoom (int x, int y, int width, int height)
{
   if (debug) printf ("NewRoom(%d,%d,%d,%d)\n", x, y, width, height);
   levels[currentLevel]->AddRoom(x, y, width, height);
   for (int i = x; i <= x + width; i++)
   {
      if (levels[currentLevel]->ObjectAt(i, y) == NULL) levels[currentLevel]->AddLevelObject(new Tile(T_WALL), i, y);
      if (levels[currentLevel]->ObjectAt(i, y + height) == NULL) levels[currentLevel]->AddLevelObject(new Tile(T_WALL), i, y + height);     
   }
   for (int j = y + 1; j < y + height; j++)
   {
      if (levels[currentLevel]->ObjectAt(x, j) == NULL) levels[currentLevel]->AddLevelObject(new Tile(T_WALL), x, j);
      if (levels[currentLevel]->ObjectAt(x + width, j) == NULL) levels[currentLevel]->AddLevelObject(new Tile(T_WALL), x + width, j); 
   }
   for (int i = x + 1; i < width; i++)
   {
      for (int j = y + 1; j < height; j++) if (levels[currentLevel]->ObjectAt(i, j) == NULL) levels[currentLevel]->AddLevelObject(new Tile(T_WHITE), i, j);
   }   
}

void Game::NewPath (int x1, int y1, int x2, int y2)
{
   if (debug) printf ("NewPath: (%d,%d) -> (%d,%d)\n", x1, y1, x2, y2);
   if (x1 == x2)
   {
      if (y1 < y2)
      {
         for (int j = y1; j <= y2; j++) 
         {
            Tile* t = new Tile(T_PATH);
            levels[currentLevel]->AddLevelObject(t, x1, j);  
         }
      }
      else // y1 >= y2
      {
         for (int j = y2; j <= y1; j++)
         {          
            Tile* t = new Tile(T_PATH);
            levels[currentLevel]->AddLevelObject(t, x1, j);
         }    
      }
   }
   else // y1 == y2
   {
      if (x1 < x2)
      {
         for (int i = x1; i <= x2; i++)
         {  
            Tile* t = new Tile(T_PATH);
            levels[currentLevel]->AddLevelObject(t, i, y1);
         }
      }
      else // x1 >= x2
      {
         for (int i = x2; i <= x1; i++)
         {
            Tile* t = new Tile(T_PATH);
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
  else if (what == t_up) lvl->AddLevelObject(new Tile(T_UP), x, y);
  else if (what == t_down) lvl->AddLevelObject(new Tile(T_DOWN), x, y);
  //else if (what == t_trap) lvl->AddLevelObject(new Trap(), x, y);
  //else if (what == t_sickness) lvl->AddLevelObject(new Consumable(C_BAD_DRINK), x, y);
  //else if (what == t_drink) lvl->AddLevelObject(new Consumable(C_GOOD_DRINK), x, y);
  //else if (what == t_food) lvl->AddLevelObject(new Consumable(C_FOOD), x, y);
  // Snake
  // Rat
  
}

// Routines to play the game

void Game::start(void)
{

   playing = true;
   
  // The following shows you how to set some elements of the gui.
  // YOU NEED TO REPLACE THIS WITH YOUR REAL START CODE ...

  gui_level->value("1");
  gui_health->value("10/10");
  gui_gold->value("0");

  gui_message("Welcome to the game!");
  
  
// I was trying to get the display going.
// I got it to compile but got a segmentation fault.
   for (int x = 0; x < X_GRID_SIZE; x++)
   {
      for (int y = 0; y < Y_GRID_SIZE; y++)
      {
         //if (levels[currentLevel]->IsVisible(x, y)) play_area->SetSquare(x, y, BLACK);
         //else
         //{
            LevelObject* thing = levels[currentLevel]->ObjectAt(x, y);
            //gui_message(strcmp(typeid(*thing).name(), "4Tile"));
            if (debug) printf ("x=%d, y=%d, type=%s, comp=%d, \n", x, y, typeid(*thing).name(), strcmp(typeid(*thing).name(), "4Tile"));
            
            if (ObjectEquals(thing, "4Gold")) play_area->SetSquare(x, y, GOLD);
            else if (ObjectEquals(thing, "4Diamond")) play_area->SetSquare(x, y, DIAMOND);       
            else if (ObjectEquals(thing, "4Consumable"))
            {            
               // Consumable code needed
               //play_area->SetSquare(x, y, DRINK);
            }
            else if (ObjectEquals(thing, "4Trap"))
            {
               // Trap code needed
            }
            
            
            else if (ObjectEquals(thing, "4Tile"))
            {

            {
               gui_message("Found a tile"); 
               Tile* temp = (Tile*) thing;               
               if (temp->GetType() == T_WHITE) play_area->SetSquare(x, y, WHITE);
               else if (temp->GetType() == T_WALL) play_area->SetSquare(x, y, WALL);             
               else if (temp->GetType() == T_PATH) play_area->SetSquare(x, y, PATH);
               else if (temp->GetType() == T_WALL) play_area->SetSquare(x, y, WALL);
               else if (temp->GetType() == T_UP) play_area->SetSquare(x, y, GOUP);
               else if (temp->GetType() == T_DOWN) play_area->SetSquare(x, y, GODOWN);
               else if (temp->GetType() == T_BLACK) play_area->SetSquare(x, y, BLACK);
            }
         }
      }
   }    
   gui_message("Did the loop"); 
 

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
}




