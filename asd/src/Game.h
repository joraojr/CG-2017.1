#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>
#include <GL/glut.h>
#include "Ranking.h"
#include "Piece.h"
#include "glcTexture.h"

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
    GLfloat env_color[4] = {0.0,0.0,0.0,1.0};
    glcTexture *textureManager;
    int lineblock;
    int lineblock2;
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
    void clearTrashReadjust(int** trashr);

    ///verificar em linha
    int verifyLineLeft(int** field, int ** trashListAux, int color,int line, int column);///verifica recursivo pra esquerda
    int verifyLineRight(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo pra direita
    int verifyLine(int** field, int** trashListAux, int** trashListFinal,int *trashCount,int line,int column);///chama a fun��o recursivo pra esquerda e direta e verifica se h� blocos candidatos a destrui��o
    ///verificar em coluna
    int verifyColumnUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima
    int verifyColumnDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo
    int verifyColumn(int** field, int** trashListAux,int** trashListFinal,int *trashCount,int line,int column);///chama a fun��o recursivo pra cima e para baixo se h� blocos candidatos a destrui��o
    ///verifica em diagonal principal e secundaria
    int verifyMainDiagUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima na diagonal primaria
    int verifyMainDiagDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo na diagonal primaria
    int verifySecondDiagUp(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para cima na diagonal secundaria
    int verifySecondDiagDown(int** field, int** trashListAux,int color,int line, int column);///verifica recursivo para baixo na diagonal secundaria
    int verifyMainDiag(int** field, int** trashListAux,int** trashListFinal,int *trashCount,int line,int column);///chama as fun��es de verifica recursivo na diagonal primaria
    int verifySecondDiag(int** field, int** trashListAux, int ** trashListFinal,int *trashCount,int line,int column);///chama as fun��es de verifica recursivo na diagonal secundaria
    bool verifyCoord(int x,int y,int** trash);///verifica se a coordenada esta dentro da matriz
    void clearTrashListAux(int ** trashListAux);///limpa a matriz de coordenadas de blocos
    void copyToTrashListFinal(int** trashListAux, int** trashListFinal, int *trashCount);
    void lineBlock(int player, int trashCount);
    void drawBorder(int x);
    void drawCylinder(float transX, float transY,float transZ, float scaleX, float scaleY, float scaleZ,float rotation);
    void drawFieldBackGround(int x);
    void drawMainViewport(int width, int height);
    void drawAuxViewport(int width,int height,float rotation);
public:
    Piece* getPiece2();
    void drawField(int ** field,int** trashr,float animationMove,int animation,int x);
    void displayGame(int width, int height, int moveX, int moveY, bool &shift, int typeShift, float animationMove,float rotationX, float rotationY,float distOrigem,float &moveLightX,float &moveLightY,float &moveLightZ);
    void displayGame2Players(int width, int height, int moveX, int moveY, bool &shift, int typeShift,float animationMove,int moveX2,int moveY2,bool &shift2,float distOrigem,float rotationX, float rotationY,float animationMove2,float &moveLightX,float &moveLightY,float &moveLightZ);
    void addColor(int ** field,int i, int j, int color);
    Game();
    ~Game();
    int getColor(int** field,int i, int j);///retorna a cor da posi��o i e j
    int isGameOver(int player);///verifica se o jogo acabou
    void printMatrix();///para teste
    bool verifyMoveLeft(int** field,int i,int j);///verifica se mover para esquerda � valido
    bool verifyMoveRight(int** field,int i,int j);///verifica se mover para direita � valido
    void readjust(int** field);///reajusta a matriz ap�s destrui��o
    int verifyAll(int** field, int** trashListAux,int** trashListFinal,int *trashCount,int line,int column);///verifica todas as dire��es
    int exponencialPoints(int i);///calcula os pontos em fatorial de blocos destruidos
    void drawMenu();///desenha menu
    int getPoints();///retorna os pontos
    void clearTrashListFinal(int ** trashListFinal,int *trashCount);///limpa a matriz de coordenadas para destrui��o
    void clear(int** field,int **trashListFinal,int *trashCount);///destr�i os blocos nas coordenadas que estiver dentro da matriz de coordenadas
    int runVerification(int** field, int** trashListAux, int **trashListFinal,int player);///chama a fun��o verifyAll e chama recursivo caso houver destrui��o
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
    Piece* getNextPiece2();
    void setPiece(Piece* p);
    void setPiece2(Piece* p);
    void setNextPiece(Piece* p);
    void createNextPiece();///cria a proxima pe�a
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
    void addBlockLine(int player,int trash);
    void removeBlockLine(int player,int trash);
    void readjustUp(int player,int trash);
    void setMaterial(GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat *shininess);
    void initTexture();
};

#endif // GAME_H_INCLUDED
