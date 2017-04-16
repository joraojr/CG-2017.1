#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>
#include <GL/glut.h>


class Game
{
private:
    int field[18][7] ;
    void drawCubeColor(int i, int j,float positionX, float positionY);
    int trashListLine[7][2];
    int trashListColumn[15][2];
    int lineCount;
    int columnCount;
    int points;

public:
    void drawField();
    void addColor(int i, int j, int color);
    Game();
    ~Game();
    int getColor(int i, int j);
    bool isGameOver();
    void printMatrix();///para teste
    void printMatrix2();
    bool verifyMoveLeft(int i,int j);
    bool verifyMoveRight(int i,int j);
    ///verificar em linha
    int verifyLineLeft(int color,int line, int column);
    int verifyLineRight(int color,int line, int column);
    void verifyLine(int line,int column);
    void clearTrashListLine();
    void clearLine();
    void readjust();
    ///verificar em coluna
    int verifyColumnUp(int color,int line, int column);
    int verifyColumnDown(int color,int line, int column);
    void clearTrashListColumn();
    void clearColumn();
    void verifyColumn(int line,int column);
    int fatorialPoints(int i);
    void drawMenu();
    int getPoints();
};

#endif // GAME_H_INCLUDED
