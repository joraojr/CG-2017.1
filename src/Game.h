#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>
#include <GL/glut.h>
#include "Ranking.h"
#include "Piece.h"

class Game
{
private:
    int** field;
    int** field2;
    int** trashListAux;
    int** trashListFinal;
    int** trashListAux2;
    int** trashListFinal2;
    int** trashReadjust;

    int trashCount;
    int points;
    int gameState;
    int brokenBlocks;
    int level;
    bool pause;
    int animationOn;
    Ranking *ranking;
    Piece* piece;
    Piece* piece2;
    Piece* nextPiece;

    void drawCubeColor(int i, int j,float positionX, float positionY);
    void getPosition(int x,int y);
    void getReadjustPosition();
    void clearTrashReadjust();

    ///verificar em linha
    int verifyLineLeft(int** field, int ** trashListAux, int color,int line, int column);///verifica recursivo pra esquerda
    int verifyLineRight(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo pra direita
    int verifyLine(int** field, int** trashListAux, int** trashListFinal,int line,int column);///chama a fun��o recursivo pra esquerda e direta e verifica se h� blocos candidatos a destrui��o
    ///verificar em coluna
    int verifyColumnUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima
    int verifyColumnDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo
    int verifyColumn(int** field, int** trashListAux,int** trashListFinal,int line,int column);///chama a fun��o recursivo pra cima e para baixo se h� blocos candidatos a destrui��o
    ///verifica em diagonal principal e secundaria
    int verifyMainDiagUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima na diagonal primaria
    int verifyMainDiagDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo na diagonal primaria
    int verifySecondDiagUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima na diagonal secundaria
    int verifySecondDiagDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo na diagonal secundaria
    int verifyMainDiag(int** field, int** trashListAux,int** trashListFinal,int line,int column);///chama as fun��es de verifica recursivo na diagonal primaria
    int verifySecondDiag(int** field, int** trashListAux, int ** trashListFinal,int line,int column);///chama as fun��es de verifica recursivo na diagonal secundaria
    bool verifyCoord(int x,int y,int** trash);///verifica se a coordenada esta dentro da matriz
    void clearTrashListAux(int ** trashListAux);///limpa a matriz de coordenadas de blocos
    void copyToTrashListFinal(int** trashListAux, int** trashListFinal);

public:
    void drawField();
    void displayGame(int width, int height, int moveX, int moveY, bool &shift, int typeShift, float animationMove,float rotationX, float rotationY,float distOrigem);
    void displayGame2Players(int width, int height, int moveX, int moveY, bool &shift, int typeShift);
    void addColor(int i, int j, int color);
    Game();
    ~Game();
    int getColor(int i, int j);///retorna a cor da posi��o i e j
    bool isGameOver();///verifica se o jogo acabou
    void printMatrix();///para teste
    bool verifyMoveLeft(int i,int j);///verifica se mover para esquerda � valido
    bool verifyMoveRight(int i,int j);///verifica se mover para direita � valido
    void readjust(int** field);///reajusta a matriz ap�s destrui��o
    int verifyAll(int** field, int** trashListAux,int** trashListFinal,int line,int column);///verifica todas as dire��es
    int fatorialPoints(int i);///calcula os pontos em fatorial de blocos destruidos
    void drawMenu();///desenha menu
    int getPoints();///retorna os pontos
    void clearTrashListFinal(int ** trashListFinal);///limpa a matriz de coordenadas para destrui��o
    void clear(int **trashListFinal);///destr�i os blocos nas coordenadas que estiver dentro da matriz de coordenadas
    void runVerification(int** field, int** trashListAux, int **trashListFinal);///chama a fun��o verifyAll e chama recursivo caso houver destrui��o
    int getGameState();///retorna o estado de jogo 0 - tela inicial 1 - jogo executando 2 - ranking 3 - fim de jogo 4 - tela de op��o de quantos players, 5 - 2 players
    void setGameState(int gameState);
    void drawStartScreen(int w,int h);///desenha tela inicial
    void drawStartScreenPlayerOption(int w, int h);
    void displayGameOver(int w, int h);///desenha tela de fim de jogo
    void scoreDisplay (int posx, int posy, int posz, int space_char, int scorevar);///escreve numeros na tela
    void displayRanking(int w, int h);///desenha tela de ranking
    void drawPoints(int w,int h);///desenha na tela de jogo os pontos, blocos destruidos e nivel
    Ranking* getRanking();
    ///gets e sets
    Piece* getPiece();
    Piece* getNextPiece();
    void setPiece(Piece* p);
    void setNextPiece(Piece* p);
    void createNextPiece();///cria a proxima pe�a
    void resetGame();///reseta os valores de game para os valores iniciais
    int getLevel();///retorna o nivel
    bool getPause();
    void setPause(bool p);
    int** getField();
    int** getField2();
    int** getTrashListAux();
    int** getTrashListAux2();
    int** getTrashListFinal();
    int** getTrashListFinal2();
    int getAnimationOn();
    void redrawPiece(int column,float moveY);
    int readjustCalculation(int** mat, int column);
    int getCoord(int** mat,int column);
};

#endif // GAME_H_INCLUDED
