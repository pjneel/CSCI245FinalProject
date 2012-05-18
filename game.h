// game.h  -- interface between the gui and the game engine

#ifndef GAME_H
#define GAME_H

#include "lexfile.h"
#include <iostream>

// types
enum direction {WEST, NORTH, SOUTH, EAST, DOWN, UP};

class Game {

 public:

  // Default constructor ... only one needed ...
  // May want to add code to initialize student defined
  // private data.

  Game() : had_error(false), playing(false) {};

  // Routines to build the game

  void SetBuildLevel (int newlevel);
  void NewRoom (int row, int col, int width, int height);
  void NewPath (int row1, int col1, int row2, int col2);  
  void SetStart (int row, int col);
  void PlaceAt (token what, int row, int col);

  // routines to play the game

  void start(void);
  void quit(void);
  void inventory(void);
  void drop(void);
  void eat(void);
  void drink(void);
  void move (direction dir);

  // Other utility routines ..

  void error (char *fmt, ...);  

  int getMaxLevel() { return 10; };
  
 private:
  bool had_error;
  bool playing;

  // STUDENT ADDS PRIVATE DATA HERE
   
};

#define CHECK_PLAYING  \
  if (!playing) { \
    fl_alert("Not playing a game."); \
    return ; \
  }

#endif