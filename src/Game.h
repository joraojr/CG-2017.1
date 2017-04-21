#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GL/glui.h>
#include <GL/glut.h>
#include "Ranking.h"
#include "Piece.h"

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
    int level;
    Ranking *ranking;
    Piece* piece;
    Piece* nextPiece;

    ///verificar em linha
    int verifyLineLeft(int color,int line, int column);///verifica recursivo pra esquerda
    int verifyLineRight(int color,int line, int column);///verifica recursivo pra direita
    int verifyLine(int line,int column);///chama a fun��o recursivo pra esquerda e direta e verifica se h� blocos candidatos a destrui��o
    void clearTrashListLine();///limpa a matriz de coordenadas de blocos em linha
    ///verificar em coluna
    int verifyColumnUp(int color,int line, int column);///verifica recursivo para cima
    int verifyColumnDown(int color,int line, int column);///verifica recursivo para baixo
    void clearTrashListColumn();///limpa a matriz de coordenadas de blocos em linha
    int verifyColumn(int line,int column);///chama a fun��o recursivo pra cima e para baixo se h� blocos candidatos a destrui��o
    ///verifica em diagonal principal e secundaria
    int verifyMainDiagUp(int color,int line, int column);///verifica recursivo para cima na diagonal primaria
    int verifyMainDiagDown(int color,int line, int column);///verifica recursivo para baixo na diagonal primaria
    int verifySecondDiagUp(int color,int line, int column);///verifica recursivo para cima na diagonal secundaria
    int verifySecondDiagDown(int color,int line, int column);///verifica recursivo para baixo na diagonal secundaria
    int verifyMainDiag(int line,int column);///chama as fun��es de verifica recursivo na diagonal primaria
    int verifySecondDiag(int line,int column);///chama as fun��es de verifica recursivo na diagonal secundaria
    bool verifyCoord(int x,int y);///verifica se a coordenada esta dentro da matriz
    void clearTrashListMainDiag();///limpa a matriz de coordenadas de blocos em diagonal primaria
    void clearTrashListSecondDiag();///limpa a matriz de coordenadas de blocos em diagonal secundaria
    ///copia as coordenadas da matriz passada por parametro para matriz trashList
    void copyColumnToTrashList(int matriz[15][2],int c);
    void copyLineToTrashList(int matriz[7][2],int c);
    void copyMainDiagToTrashList(int matriz[7][2],int c);
    void copySecondDiagToTrashList(int matriz[7][2],int c);

public:
    void drawField();
    void addColor(int i, int j, int color);
    Game();
    ~Game();
    int getColor(int i, int j);///retorna a cor da posi��o i e j
    bool isGameOver();///verifica se o jogo acabou
    void printMatrix();///para teste
    bool verifyMoveLeft(int i,int j);///verifica se mover para esquerda � valido
    bool verifyMoveRight(int i,int j);///verifica se mover para direita � valido
    void readjust();///reajusta a matriz ap�s destrui��o
    int verifyAll(int line,int column);///verifica todas as dire��es
    int fatorialPoints(int i);///calcula os pontos em fatorial de blocos destruidos
    void drawMenu();///desenha menu
    int getPoints();///retorna os pontos
    void clearTrashList();///limpa a matriz de coordenadas para destrui��o
    void clear();///destr�i os blocos nas coordenadas que estiver dentro da matriz de coordenadas
    void runVerification();///chama a fun��o verifyAll e chama recursivo caso houver destrui��o
    int getGameState();///retorna o estado de jogo 0 - tela inicial 1 - jogo executando 2 - ranking 3 - fim de jogo
    void setGameState(int gameState);
    void drawStartScreen();///desenha tela inicial
    void displayGameOver();///desenha tela de fim de jogo
    void scoreDisplay (int posx, int posy, int posz, int space_char, int scorevar);///escreve numeros na tela
    void displayRanking();///desenha tela de ranking
    void drawPoints();///desenha na tela de jogo os pontos, blocos destruidos e nivel
    Ranking* getRanking();
    ///gets e sets
    Piece* getPiece();
    Piece* getNextPiece();
    void setPiece(Piece* p);
    void setNextPiece(Piece* p);
    void createNextPiece();///cria a proxima pe�a
    void resetGame();///reseta os valores de game para os valores iniciais
    int getLevel();///retorna o nivel

};

#endif // GAME_H_INCLUDED
