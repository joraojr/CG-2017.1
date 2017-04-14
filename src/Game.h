#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>

class Game{
    private:
        int field[15][7] ;
        addFieldColor();
        drawCubeColor(int i, int j);

    public:
        drawField();
        addCor(int i, int j, int cor);
        Game();
        ~Game();
};

#endif // GAME_H_INCLUDED
