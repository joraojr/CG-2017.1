#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>
#include <GL/glut.h>
#include "Ranking.h"
#include "Piece.h"

class Game
{
private:

    int** trashListAux;
    int** trashListFinal;
    int** trashListAux2;
    int** trashListFinal2;
    int** trashReadjust;
    int** trashReadjust2;
    int** field1;
    int** field2;

    int gameView;
    int trashCount1;
    int trashCount2;
    int points;
    int gameState;
    int brokenBlocks1;
    int brokenBlocks2;
    int level;
    bool pause;
    int animationOn;
    int animationOn2;
    Ranking *ranking;
    Piece* piece;
    Piece* piece2;
    Piece* nextPiece;
    Piece* nextPiece2;

    void drawCubeColor(int ** field,int i, int j,float positionX, float positionY);
    void getPosition(int** field,int** trashf,int** trashr,int x,int y);
    void getReadjustPosition(int** field,int** trashf,int** trashr);
    void clearTrashReadjust();

    ///verificar em linha
    int verifyLineLeft(int** field, int ** trashListAux, int color,int line, int column);///verifica recursivo pra esquerda
    int verifyLineRight(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo pra direita
    int verifyLine(int** field, int** trashListAux, int** trashListFinal,int *trashCount,int line,int column);///chama a função recursivo pra esquerda e direta e verifica se há blocos candidatos a destruição
    ///verificar em coluna
    int verifyColumnUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima
    int verifyColumnDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo
    int verifyColumn(int** field, int** trashListAux,int** trashListFinal,int *trashCount,int line,int column);///chama a função recursivo pra cima e para baixo se há blocos candidatos a destruição
    ///verifica em diagonal principal e secundaria
    int verifyMainDiagUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima na diagonal primaria
    int verifyMainDiagDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo na diagonal primaria
    int verifySecondDiagUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima na diagonal secundaria
    int verifySecondDiagDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo na diagonal secundaria
    int verifyMainDiag(int** field, int** trashListAux,int** trashListFinal,int *trashCount,int line,int column);///chama as funções de verifica recursivo na diagonal primaria
    int verifySecondDiag(int** field, int** trashListAux, int ** trashListFinal,int *trashCount,int line,int column);///chama as funções de verifica recursivo na diagonal secundaria
    bool verifyCoord(int x,int y,int** trash);///verifica se a coordenada esta dentro da matriz
    void clearTrashListAux(int ** trashListAux);///limpa a matriz de coordenadas de blocos
    void copyToTrashListFinal(int** trashListAux, int** trashListFinal, int *trashCount);
    void lineBlock(int player, int trashCount);

public:
    Piece* getPiece2();
    void drawField(int ** field,int** trashr,float animationMove,int animation);
    void displayGame(int width, int height, int moveX, int moveY, bool &shift, int typeShift, float animationMove,float rotationX, float rotationY,float distOrigem);
    void displayGame2Players(int width, int height, int moveX, int moveY, bool &shift, int typeShift,float animationMove,int moveX2,int moveY2,bool &shift2,float distOrigem,float rotationX, float rotationY,float animationMove2);
    void addColor(int ** field,int i, int j, int color);
    Game();
    ~Game();
    int getColor(int** field,int i, int j);///retorna a cor da posição i e j
    int isGameOver(int player);///verifica se o jogo acabou
    void printMatrix();///para teste
    bool verifyMoveLeft(int** field,int i,int j);///verifica se mover para esquerda é valido
    bool verifyMoveRight(int** field,int i,int j);///verifica se mover para direita é valido
    void readjust(int** field);///reajusta a matriz após destruição
    int verifyAll(int** field, int** trashListAux,int** trashListFinal,int *trashCount,int line,int column);///verifica todas as direções
    int exponencialPoints(int i);///calcula os pontos em fatorial de blocos destruidos
    void drawMenu();///desenha menu
    int getPoints();///retorna os pontos
    void clearTrashListFinal(int ** trashListFinal,int *trashCount);///limpa a matriz de coordenadas para destruição
    void clear(int** field,int **trashListFinal,int *trashCount);///destrói os blocos nas coordenadas que estiver dentro da matriz de coordenadas
    int runVerification(int** field, int** trashListAux, int **trashListFinal,int player);///chama a função verifyAll e chama recursivo caso houver destruição
    int getGameState();///retorna o estado de jogo 0 - tela inicial 1 - jogo executando 2 - ranking 3 - fim de jogo 4 - tela de opção de quantos players, 5 - 2 players
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
    Piece* getNextPiece2();
    void setPiece(Piece* p);
    void setPiece2(Piece* p);
    void setNextPiece(Piece* p);
    void createNextPiece();///cria a proxima peça
    void resetGame();///reseta os valores de game para os valores iniciais
    int getLevel();///retorna o nivel
    bool getPause();
    void setPause(bool p);
    int** getField1();
    int** getField2();
    int** getTrashListAux();
    int** getTrashListAux2();
    int** getTrashListFinal();
    int** getTrashListFinal2();
    int getAnimationOn();
    void setAnimationOn(int a);
    int getAnimationOn2();
    void setAnimationOn2(int a);
    int getCoord(int** mat,int column);
    void setGameView(int gv);
    int getGameView();
    int getTrashCount();
    int getTrashCount2();
    int getBrokenBlocks();
    int getBrokenBlocks2();
    int** getTrashReadjust();
    int** getTrashReadjust2();
    void displayGameOver2Players(int w,int h);
    void drawLevel(int w,int h);
    void updateFieldReadjust(int** field,int** trash);
    void updateReadjust(int** field,int** trash);
    bool verifyReadjust(int** trash);
    void lineBlockRemove(int player, int trashCount);
};

#endif // GAME_H_INCLUDED
