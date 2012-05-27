PROG=game

# Add your .cxx files here.  They need the .cxx extension.
SRCS=gui.cxx PlayArea.cxx game.cxx lexfile.cxx readgame.cxx Level.cxx LevelObject.cxx Player.cxx Monster.cxx Room.cxx

OBJ1=$(SRCS:.cxx=.o)
OBJS=$(OBJ1:.cpp=.o)

CLEAN=$(OBJS) $(PROG) gui.h gui.cxx *~ testread .depend

#local fltk installations ....
FLTK=/home/phil/cs245sw

# applications
CXX=g++
FLUID=$(FLTK)/bin/fluid

# compile and link flags for Ubuntu Linux
CXXFLAGS= -g -I$(FLTK)/include 
LDFLAGS= -L$(FLTK)/lib -L/usr/lib/X11
LIBS=-lXext -lXft -lXinerama -lm -lfltk -lX11

# how to comple
.SUFFIXES: .c .cpp .cxx .fl .o

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

# how to get .fl files ready to compile
.fl.cxx:
	$(FLUID) -c $<

# make the program

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(LDFLAGS) $(OBJS) $(LIBS)

clean:
	rm -f $(CLEAN)

# testread

testread: lexfile.h lexfile.cxx readgame.cxx
	$(CXX) -o testread -DTESTREAD readgame.cxx lexfile.cxx

# making dependencies

gui.o: gui.fl gui.cxx
gui.o PlayArea.o: PlayArea.h
game.o: game.h gui.fl PlayArea.h Level.h LevelObject.h Player.h
PlayArea.o: xpms/*.xpm
lexfile.o: lexfile.h
readgame.o: lexfile.h
Level.o: Level.h LevelObject.h Monster.h Room.h Player.h
LevelObject.o: LevelObject.h Player.h
Monster.o: Monster.h Player.h game.h
Player.o: Player.h LevelObject.h game.h
Room.o: Room.h

# For each .h file in your project, make sure that you have
# a line that reads "file.o: myfile.h" where file.cxx includes
# the myfile.h.  You can have several .h files on one line.
# See game.o above.   And if you change those above, (game.cxx
# should be the only one you change, make sure to add the new
# .h files included by the appropriate .cxx files.)
