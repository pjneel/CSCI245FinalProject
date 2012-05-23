// game.cxx -- the implementation part of the interface


#include "game.h"
#include "gui.h"
#include "Level.h"
#include "LevelObject.h"

#include <FL/fl_ask.H>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
using namespace std;

// Utility routine:  called like printf.

const int MAX_LEVELS = 10;

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
}

void Game::NewRoom (int x, int y, int width, int height)
{
  if (debug) printf ("NewRoom(%d,%d,%d,%d)\n", x, y, width, height);
  levels[currentLevel]->AddRoom(x, y, width, height);
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
  if (debug && what == t_diamond)
    printf ("Place the diamond at (%d,%d)...\n", x, y);
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



