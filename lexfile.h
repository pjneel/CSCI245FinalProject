// A Class for doing simple lexical analysis of
// a level description of CS 341 assignments

#ifndef LEXFILE_H
#define LEXFILE_H

#include <iostream>
#include <fstream>

using namespace std;

enum token {t_number, t_comma, t_semicolon, t_and, t_from, t_at, t_to, t_of,
	    t_level, t_room, t_path, t_trap, t_up, t_down, t_start,
	    t_diamond, t_gold, 
	    t_rat, t_snake,
	    t_food, t_drink,
	    t_arrow, t_transport, t_sickness, t_health,
	    t_eof, t_error};

extern const char *tok_name[t_error+1];


class lexfile {
 public:

  bool open(const char *name);

  token get_next();  // get the next token

  int  get_val()  // get the value of the last t_number token
      { return num_val; }

  int  get_linenum() // get the current line number
    { return line_num; }

 private:
  ifstream f;
  int num_val;
  int line_num;
};

#endif
