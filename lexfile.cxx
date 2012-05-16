// Lexfile implementation

#include <iostream>

#include "lexfile.h"
#include <string>
#include <cctype>

using namespace std;

// token names
const char *tok_name[t_error+1] =
  { "number", "comma", "semicolon", "and", "from", "at", "to", "of",
    "level", "room", "path", "trap", "up", "down", "start",
    "diamond", "gold", 
    "rat", "snake",
    "food", "drink",
    "arrow", "transport", "sickness", "health",
    "eof", "error"};


bool lexfile::open(const char *name)
{
  f.open(name);
  line_num = 1;
  return f.is_open();
}

token lexfile::get_next()
{
  char c;
  string s;

  f.get(c);
  while (!f.eof() && (c == ' ' || c == '\n' || c == '\r')) {
    if (c == '\n') line_num++;
    f.get(c);
  }

  if (f.eof())
    return t_eof;

  if (isalpha(c)) {
    f.putback(c);
    f>>s;

    if (s == "level") return t_level;
    if (s == "level;") { f.putback(';'); return t_level; }

    if (s == "and") return t_and;
    if (s == "from") return t_from;
    if (s == "at") return t_at;
    if (s == "to") return t_to;
    if (s == "of") return t_of;

    if (s == "room") return t_room;
    if (s == "path") return t_path;
    if (s == "trap") return t_trap;
    if (s == "up") return t_up;
    if (s == "down") return t_down;
    if (s == "start") return t_start;

    if (s == "diamond") return t_diamond;
    if (s == "gold") return t_gold;

    if (s == "rat") return t_rat;
    if (s == "snake") return t_snake;

    if (s == "food") return t_food;
    if (s == "drink") return t_drink;

    if (s == "arrow") return t_arrow;
    if (s == "transport") return t_transport;
    if (s == "sickness") return t_sickness;
    if (s == "health") return t_health;

    return t_error;
  }

  if (isdigit(c)) {
    f.putback(c);
    f>>num_val;
    return t_number;
  }

  switch (c) {
    case ',':  return t_comma;
    case ';':  return t_semicolon;
   }

  return t_error;
}
