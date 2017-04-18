#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>
#include <GL/glut.h>
#include "Ranking.h"


class Game
{
private:
    int field[18][7] ;
    void drawCubeColor(int i, int j,float positionX, float positionY);
    int trashListLine[7][2];
    int trashListColumn[15][2];
    int trashListMainDiag[7][2];
    int trashListSecondDiag[7][2];
    int trashList[105][2];
    int trashCount;
    int lineCount;
    int columnCount;
    int mainDiagCount;
    int secondDiagCount;
    int points;
    int gameState;
    int brokenBlocks;
    Ranking *ranking;

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
    void readjust();
    ///verificar em coluna
    int verifyColumnUp(int color,int line, int column);
    int verifyColumnDown(int color,int line, int column);
    void clearTrashListColumn();
    void verifyColumn(int line,int column);
    void verifyAll(int line,int column);
    int fatorialPoints(int i);
    void drawMenu();
    int getPoints();
    void clearTrashList();
    void copyColumnToTrashList(int matriz[15][2],int c);
    void copyLineToTrashList(int matriz[7][2],int c);
    void copyMainDiagToTrashList(int matriz[7][2],int c);
    void copySecondDiagToTrashList(int matriz[7][2],int c);
    ///verifica em diagonal principal e secundaria
    int verifyMainDiagUp(int color,int line, int column);
    int verifyMainDiagDown(int color,int line, int column);
    int verifySecondDiagUp(int color,int line, int column);
    int verifySecondDiagDown(int color,int line, int column);
    void verifyMainDiag(int line,int column);
    void verifySecondDiag(int line,int column);
    bool verifyCoord(int x,int y);
    void clearTrashListMainDiag();
    void clearTrashListSecondDiag();
    void clear();
    void runVerification();
    int getGameState();
    void setGameState(int gameState);
    void drawStartScreen();
    void displayGameOver();
    void scoredisplay (int posx, int posy, int posz, int space_char, int scorevar);
    void displayRanking();
    void drawPoints();
};

#endif // GAME_H_INCLUDED
