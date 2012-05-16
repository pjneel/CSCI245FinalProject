
// PlayArea.cxx -- the implementation!

#include <cstdio>

#include "gui.h"
#include "PlayArea.h"

//  graphic xpms..
#include "xpms/black.xpm"
#include "xpms/white.xpm"
#include "xpms/wall.xpm"
#include "xpms/goup.xpm"
#include "xpms/godown.xpm"
#include "xpms/path.xpm"
#include "xpms/diamond.xpm"
#include "xpms/gold.xpm"
#include "xpms/food.xpm"
#include "xpms/drink.xpm"
#include "xpms/snake.xpm"
#include "xpms/player.xpm"

#include "xpms/atrap.xpm"
#include "xpms/ttrap.xpm"
#include "xpms/rat.xpm"


// Arrays of xpms.

static 
const char **xpms[] = {black, white, wall, goup, godown, path, diamond,
		       gold, food, drink, snake, player, atrap, ttrap, rat};

// Initialize the hotel pixmaps.

void PlayArea::Init_pixmaps(void)
{ 
  for (int i=0; i<numxpms ; i++)
    pixmaps[i] = new Fl_Pixmap(xpms[i]);
}

void PlayArea::draw()
{
  int xx,yy;

  // draw each square
  for (xx = 0; xx < 50; xx++)
    for (yy = 0; yy < 40; yy++)
      Area[xx][yy]->draw(x()+xx*15, y()+yy*15);
};

