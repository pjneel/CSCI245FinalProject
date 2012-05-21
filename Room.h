
class Room
{
private:
	int xPos;
	int yPos;
	int xSize;
	int ySize;
public:
	Room(int xPos, int yPos, int xSize, int ySize);
	int X_Start();
	int Y_Start();
	int Width();
	int Height();
};
