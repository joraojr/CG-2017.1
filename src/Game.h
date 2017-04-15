#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>

class Game
{
private:
    int field[15][7] ;
    void drawCubeColor(int i, int j,float positionX, float positionY);

public:
    void drawField();
    void addColor(int i, int j, int color);

    Game();
    ~Game();
};

#endif // GAME_H_INCLUDED
