// game.cxx -- the implementation part of the interface


#include "gui.h"
#include "game.h"

#include <FL/fl_ask.H>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
using namespace std;

// Utility routine:  called like printf.

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
}

void Game::NewRoom (int row, int col, int width, int height)
{
  if (debug) printf ("NewRoom(%d,%d,%d,%d)\n", row, col, width, height);
}

void Game::NewPath (int row1, int col1, int row2, int col2)
{
  if (debug) printf ("NewPath: (%d,%d) -> (%d,%d)\n", row1, col1, row2, col2);
}  

void Game::SetStart (int row, int col)
{
  if (debug) printf ("Level starts at (%d,%d)\n", row, col);
}

void Game::PlaceAt (token what, int row, int col)
{
  if (debug) printf ("Place %s at (%d,%d)\n", tok_name[what], row, col);
  if (debug && what == t_diamond)
    printf ("Place the diamond at (%d,%d)...\n", row, col);
    
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



