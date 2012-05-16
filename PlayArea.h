
// PlayArea.h -- draw the play area

#ifndef PLAYAREA_H
#define PLAYAREA_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pixmap.H>
#include <FL/fl_draw.H>

#include <cstdio>

#define GAME_X 50
#define GAME_Y 40

extern Fl_Double_Window *MainWin;

// graphic names -- add new ones before NUMGRAPH
enum graphic { BLACK, WHITE, WALL, GOUP, GODOWN, PATH, DIAMOND, GOLD,
	       FOOD, DRINK, SNAKE, PLAYER, ATRAP, TTRAP, RAT, NUMGRAPH };

class PlayArea : public Fl_Box {

 private:
  //  This number should be the number of elements in graphic
  static const int numxpms = NUMGRAPH;

 public:

  PlayArea (int bx, int by, int bw, int bh, const char *label = 0)
    : Fl_Box (bx, by, bw, bh, 0)
    {
      Init_pixmaps();
      InitArea();
    };

  PlayArea (Fl_Boxtype b, int bx, int by, int bw, int bh,
	     const char *label = 0)
    : Fl_Box (b, bx, by, bw, bh, 0)
    {
      Init_pixmaps();
      InitArea();
    };

  void draw();

  void show() {  redraw(); }

  void SetSquare(int xx, int yy, enum graphic view)
    {
      if ((view < 0) || (view > numxpms)) {
	printf ("SetSquare: bad graphic %d at (%d,%d).\n", view, xx, yy);
        return;
      }
      if ((xx < 0) || (xx > 49) ||
	  (yy < 0) || (yy > 39)) {
	printf ("SetSquare: bad index [%d,%d]\n", xx, yy);
        return;
      }
      MainWin->make_current();
      Area[xx][yy] = pixmaps[view];
      Area[xx][yy]->draw(x()+xx*15, y()+yy*15);
    }

  void ClearArea()
    {
      int x, y;

      for (x = 0; x < GAME_X; x++)
	for (y = 0; y < GAME_Y; y++)
	  SetSquare(x,y,BLACK);
    }

private:

  Fl_Pixmap *Area[GAME_X][GAME_Y];

  // xpms ...
  Fl_Pixmap *pixmaps[numxpms];

  void InitArea()
    {
      int x, y;

      for (x = 0; x < GAME_X; x++)
	for (y = 0; y < GAME_Y; y++)
	  Area[x][y] = pixmaps[BLACK];
    }

  void Init_pixmaps();
};

#endif
