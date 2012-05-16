// Read the game description from a file!

#include <iostream>
#include <string>
#include "lexfile.h"

#ifdef TESTREAD

int debug;

#else

#include "gui.h"

// Utility routines 
static void error ( lexfile &f, string message )
{
  cerr << f.get_linenum() << ": " << message << "\n";
}

static bool match ( lexfile &f, token look)
{
  token t = f.get_next();
  if (t != look) {
    error(f,"Syntax error on line");
  }
  return t == look;
}
  
static void get_pair ( lexfile &f, int &x, int &y)
{
  match (f, t_number);
  x = f.get_val();
  match (f, t_comma);
  match (f, t_number);
  y = f.get_val();
}

static void and_list ( lexfile &f, token what)
{
  int x, y;
  token t;

  // Starting with the "at ..."
  match (f, t_at);
  get_pair(f, x, y);
  game.PlaceAt (what, x, y); 

  // rest of the list  
  while ((t =f.get_next()) == t_and) {
    get_pair(f, x, y);
    game.PlaceAt (what, x, y); 
  }
  if (t != t_semicolon)
    error (f, "expected semicolon");
}

#endif


void readgame(int &argc, char **&argv)
{
  lexfile f;
  token t;

  if (argc > 1 && strcmp(argv[1],"-d") == 0 ) {
    argc--;
    argv++;
    debug = 1;
  }

  if (argc == 1) {
    if (!f.open("simple.txt")) {
      cout << "Could not open simple.txt!\n";
      exit(1);
    }
  } else {
    if (!f.open(argv[1])) {
      cout << "Could not open " << argv[1] << "!\n";
      exit(1);
    }
    argc--;
    argv++;
  }

#ifndef TESTREAD

  int x, y, x2, y2, ax, ay;
  int level = -1;
  token kind;

  while ( (t = f.get_next()) != t_eof ) {

    if (level == -1 && t != t_level) {
      error (f, "Level must be first.");
      exit(1);
    }
      
    switch (t) {

    case t_level:
      // New level
      match (f, t_semicolon);
      level++;
      if (level > 10) {
	cerr << "Too many levels, only 10 supported\n";
        exit(1);
      }
      game.SetBuildLevel(level);
      break;

    case t_room:
      // room *newroom;
      get_pair (f, ax, ay);
      match (f, t_at);
      get_pair (f, x, y);
      match (f, t_semicolon);
      game.NewRoom(x,y,ax,ay);
      break;

    case t_path:
      match (f, t_from);
      get_pair (f, x, y);
      while ((t = f.get_next()) == t_to) {
	get_pair (f, x2, y2);
	game.NewPath (x,y,x2,y2);
	x=x2;
	y=y2;
      }
      if (t != t_semicolon)
	error (f, "Expected a semicolon.");
      break;

    case t_gold:
    case t_food:
    case t_snake:
    case t_rat:
    case t_up:
    case t_down:
      and_list (f, t);
      break;

    case t_drink:
      match (f, t_of);
      kind = f.get_next();
      if (kind != t_sickness && kind != t_health)
	error (f, "Expected drink kind");
      and_list (f, kind);
      break;

    case t_trap:
      match (f, t_of);
      kind = f.get_next();
      if (kind != t_arrow && kind != t_transport)
	error (f, "Expected trap kind");
      and_list (f, kind);
      break;

    case t_start:
      match (f, t_at);
      get_pair (f, x, y);
      match (f, t_semicolon);
      game.SetStart (x, y);
      break;

    case t_diamond:
      match (f, t_at);
      get_pair (f, x, y);
      match (f, t_semicolon);
      game.PlaceAt (t_diamond, x, y);
      break;

    default:
      error (f, "Syntax error");  // ignore for the moment
    }
  }

#else

  int curline = f.get_linenum();
    cout << curline << ": ";

  while ( (t = f.get_next()) != t_eof ) {
    if (curline != f.get_linenum()) {
      curline = f.get_linenum();
      cout << "\n" << curline << ": ";
    }
    switch (t) {
    case t_number:
      cout << f.get_val() << " ";
      break;
    case t_comma:
      cout << ", ";
      break;
    case t_semicolon:
      cout << "; ";
      break;
    case t_level:
      cout << "Level ";
      break;
    case t_room:
      cout << "Room ";
      break;
    case t_and:
      cout << "and ";
      break;
    case t_at:
      cout << "at ";
      break;
    case t_to:
      cout << "to ";
      break;
    case t_of:
      cout << "of ";
      break;
    case t_gold:
      cout << "Gold ";
      break;
    case t_start:
      cout << "Start ";
      break;
    case t_path:
      cout << "Path ";
      break;
    case t_from:
      cout << "from ";
      break;
    case t_diamond:
      cout << "Diamond ";
      break;
    case t_rat:
      cout << "Rat ";
      break;
    case t_snake:
      cout << "Snake ";
      break;
    case t_food:
      cout << "Food ";
      break;
    case t_drink:
      cout << "Drink ";
      break;
    case t_trap:
      cout << "Trap ";
      break;
    case t_up:
      cout << "Up ";
      break;
    case t_down:
      cout << "Down ";
      break;

    case t_arrow:
      cout << "arrow ";
      break;
    case t_transport:
      cout << "transport ";
      break;
    case t_sickness:
      cout << "sickness ";
      break;
    case t_health:
      cout << "health ";
      break;


    case t_error:
    default:
      cout << " ***Error*** ";
      break;
    };
  }
  
#endif
  
}


#ifdef TESTREAD

int main (int argc, char **argv)
{
  readgame(argc, argv);
  return 0;
}

#endif
