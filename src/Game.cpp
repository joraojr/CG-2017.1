#include "Game.h"
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds


Game::Game()
{
    /// 1- vermelho cube, 2-Verde torus, 3-Azul sphere, 4- Amarelo teapot, 5-Magenta cone, 0-Vazio
    field1 = new int*[18];
    field2 = new int*[18];
    for(int i = 0; i < 18; i++)
    {
        field1[i] = new int[7];
        field2[i] = new int[7];
        for(int j =0; j < 7; j++)
        {
            field1[i][j] = 0 ;
            field2[i][j] = 0 ;
        }
    }
    gameView = 0;
    trashListAux = new int*[15];
    trashListFinal = new int*[15];
    trashListAux2 = new int*[15];
    trashListFinal2 = new int*[15];
    trashReadjust = new int*[15];
    trashReadjust2 = new int*[15];
    for(int i = 0; i < 15; i++)
    {
        trashListAux[i] = new int[7];
        trashListFinal[i] = new int[7];
        trashListAux2[i] = new int[7];
        trashListFinal2[i] = new int[7];
        trashReadjust[i] = new int[7];
        trashReadjust2[i] = new int[7];
        for(int j =0; j < 7; j++)
        {
            trashListAux[i][j] = 0;
            trashListFinal[i][j] = 0;
            trashListAux2[i][j] = 0;
            trashListFinal2[i][j] = 0;
            trashReadjust[i][j] = 0;
            trashReadjust2[i][j] = 0;
        }
    }
    lineblock = 0;
    lineblock2 = 0;
    animationOn = 0;
    animationOn2 = 0;
    points = 0 ;
    trashCount1 = 0;
    trashCount2 = 0;
    gameState = 0;
    level = 1;
    pause = false;
    ranking = new Ranking();
    brokenBlocks1 = 0;
    brokenBlocks2 = 0;
    piece = new Piece();
    piece2 = new Piece();
    nextPiece = new Piece();
    nextPiece2 = new Piece();
}

void Game::drawCubeColor(int** field,int i, int j, float positionX, float positionY)
{
    Cube* c;
    ///desenhar a cor do cubo
    glEnable(GL_LIGHTING);
    switch(field[i][j])
    {
    case 1:
        glPushMatrix();
        c = new Cube();
        c->drawObject(1,positionX,positionY);
        glPopMatrix();
        break;
    case 2:
        glPushMatrix();
        c = new Cube();
        c->drawObject(2,positionX,positionY);
        glPopMatrix();
        break;
    case 3:
        glPushMatrix();
        c = new Cube();
        c->drawObject(3,positionX,positionY);
        glPopMatrix();
        break;
    case 4:
        glPushMatrix();
        c = new Cube();
        c->drawObject(4,positionX,positionY);
        glPopMatrix();
        break;
    case 5:
        glPushMatrix();
        c = new Cube();
        c->drawObject(5,positionX,positionY);
        glPopMatrix();
        break;
    case 6:
        glPushMatrix();
        c = new Cube();
        c->drawObject(6,positionX,positionY);
        glPopMatrix();
        break;
    default:
        break;
    }
}

void Game::drawField(int ** field,int** trashr,float animationMove, int animation)
{

    if(animation == 0)
    {
        float x = 0.0;
        float y = 0.0;
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                this->drawCubeColor(field,i,j,x+3.5,y+3.5);
                glDisable(GL_LIGHTING);
                glColor3f(0.0,0.0,0.3);
                glBegin(GL_LINE_LOOP);
                glVertex3f(x,y,0.0);
                glVertex3f(x + 7.0,y,0.0);
                glVertex3f(x + 7.0,y + 7.0,0.0);
                glVertex3f(x,y + 7.0,0.0);
                glEnd();
                x += 7.0;
            }
            y += 7.0;
            x = 0.0;
        }
    }
    else
    {
        float x = 0.0;
        float y = 0.0;
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(trashr[i][j] != 0)
                {
                    this->drawCubeColor(field,i,j,x+3.5,y+3.5 - animationMove);
                    glDisable(GL_LIGHTING);
                    glColor3f(0.0,0.0,0.3);
                    glBegin(GL_LINE_LOOP);
                    glVertex3f(x,y,0.0);
                    glVertex3f(x + 7.0,y,0.0);
                    glVertex3f(x + 7.0,y + 7.0,0.0);
                    glVertex3f(x,y + 7.0,0.0);
                    glEnd();
                }
                else
                {
                    this->drawCubeColor(field,i,j,x+3.5,y+3.5);
                    glDisable(GL_LIGHTING);
                    glColor3f(0.0,0.0,0.3);
                    glBegin(GL_LINE_LOOP);
                    glVertex3f(x,y,0.0);
                    glVertex3f(x + 7.0,y,0.0);
                    glVertex3f(x + 7.0,y + 7.0,0.0);
                    glVertex3f(x,y + 7.0,0.0);
                    glEnd();
                }
                x += 7.0;
            }
            y += 7.0;
            x = 0.0;
        }
    }
}

void Game::setGameView(int gv)
{
    gameView = gv;
}

int Game::getGameView()
{
    return gameView;
}

int Game::getCoord(int** mat, int column)
{
    int coord = 0;
    for(int i = 0; i < 15; i++)
    {
        if(mat[i][column] == 1)
        {
            coord = i;
            break;
        }
    }
    return coord;
}

void Game::addColor(int** field, int i, int j, int color)
{
    field[i][j] = color ;
}

int Game::getColor(int** field,int i, int j)
{
    if(i == -1 || j == 7 || j == -1)
        return -1;
    return field[i][j];
}

int Game::isGameOver(int player)
{
    int loser = 0;
    if(player == 1)
    {
        for(int i = 0; i < 7; i++)
        {
            if(field1[15][i] != 0)
                loser = 1;
        }
    }
    else
    {
        for(int i = 0; i < 7; i++)
        {
            if(field2[15][i] != 0)
                loser = 2;
        }
    }

    return loser;
}

void Game::printMatrix()
{
    for(int i = 0; i < 15; i++)
    {
        cout << "[";
        for(int j =0; j < 7; j++)
            cout << trashReadjust[i][j] << ";";
        cout  << "]" << endl;
    }
    cout << endl;
}

bool Game::verifyMoveLeft(int** field,int line,int column)
{
    if(field[line][column-1] == 0)
        return true;
    return false;
}

bool Game::verifyMoveRight(int** field,int line,int column)
{
    if(field[line][column+1] == 0)
        return true;
    return false;
}
///verificar em linha
int Game::verifyLineLeft(int** field, int** trashListAux, int color,int line, int column)
{
    if(column - 1 >= 0)
    {
        if(color == field[line][column - 1])
        {
            trashListAux[line][column - 1] = 1;
            return 1 + verifyLineLeft(field, trashListAux,color,line,column - 1);
        }
    }
    return 0;
}

int Game::verifyLineRight(int** field, int** trashListAux,int color,int line, int column)
{
    if(column + 1 < 7)
    {
        if(color == field[line][column + 1])
        {
            trashListAux[line][column + 1] = line;
            return 1 + verifyLineRight(field,trashListAux,color,line,column + 1);
        }
    }
    return 0;
}

int Game::verifyLine(int** field, int** trashListAux, int ** trashListFinal,int *trashCount,int line, int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifyLineLeft(field,trashListAux,field[line][column],line,column);
    countC += verifyLineRight(field,trashListAux,field[line][column],line,column);

    if(countC < 3)
        clearTrashListAux(trashListAux);
    else
    {
        copyToTrashListFinal(trashListAux,trashListFinal, trashCount);
        return 1;
    }
    return 0;
}

void Game::copyToTrashListFinal(int** trashListAux, int** trashListFinal, int* trashCount)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(trashListAux[i][j] == 1 && !verifyCoord(i,j,trashListFinal))
            {
                trashListFinal[i][j] = 1;
                *trashCount += 1;
            }
        }
    }
    clearTrashListAux(trashListAux);
}

//reseta a matriz com as coordenadas
void Game::clearTrashListAux(int** trashListAux)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
            trashListAux[i][j] = 0;
    }
}///FIM verifica Linha

///verifica em coluna
int Game::verifyColumnDown(int** field, int** trashListAux,int color,int line,int column)
{
    if(line - 1 >= 0)
    {
        if(color == field[line - 1][column])
        {
            trashListAux[line - 1][column] = 1;
            return 1 + verifyColumnDown(field,trashListAux,color,line - 1,column);
        }
    }
    return 0;
}

int Game::verifyColumnUp(int** field, int** trashListAux,int color,int line,int column)
{
    if(line + 1 < 15)
    {
        if(color == field[line + 1][column])
        {
            trashListAux[line + 1][column] = 1;
            return 1 + verifyColumnUp(field,trashListAux,color,line + 1,column);
        }
    }
    return 0;
}

int Game::verifyColumn(int** field, int** trashListAux, int ** trashListFinal, int* trashCount,int line, int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifyColumnDown(field,trashListAux,field[line][column],line,column);
    countC += verifyColumnUp(field,trashListAux,field[line][column],line,column);

    if(countC < 3)
        clearTrashListAux(trashListAux);
    else
    {
        copyToTrashListFinal(trashListAux,trashListFinal,trashCount);
        return 1;
    }
    return 0;
}
///FIM verifica em coluna

///verificar em diagonal primaria


int Game::verifyMainDiag(int** field, int** trashListAux,int ** trashListFinal,int* trashCount,int line, int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifyMainDiagUp(field, trashListAux,field[line][column],line,column);
    countC += verifyMainDiagDown(field,trashListAux,field[line][column],line,column);
    if(countC < 3)
        clearTrashListAux(trashListAux);
    else
    {
        copyToTrashListFinal(trashListAux,trashListFinal,trashCount);
        return 1;
    }
    return 0;
}

int Game::verifyMainDiagUp(int** field, int** trashListAux,int color,int line, int column)
{
    if(line - 1 >= 0 && column + 1 < 7)
    {
        if(color == field[line - 1][column + 1])
        {
            trashListAux[line - 1][column + 1] = 1;
            return 1 + verifyMainDiagUp(field,trashListAux,color,line - 1,column + 1);
        }
    }
    return 0;
}

int Game::verifyMainDiagDown(int** field, int** trashListAux,int color,int line, int column)
{
    if(line + 1 < 15 && column - 1 >= 0)
    {
        if(color == field[line + 1][column - 1])
        {
            trashListAux[line + 1][column - 1] = 1;
            return 1 + verifyMainDiagDown(field,trashListAux,color,line + 1,column - 1);
        }
    }
    return 0;
}///FIM verifica em diagonal primaria

///Verificar em diagonal secundaria
int Game::verifySecondDiag(int** field, int** trashListAux, int** trashListFinal,int* trashCount,int line,int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifySecondDiagUp(field,trashListAux,field[line][column],line,column);
    countC += verifySecondDiagDown(field, trashListAux,field[line][column],line,column);
    if(countC < 3)
        clearTrashListAux(trashListAux);
    else
    {
        copyToTrashListFinal(trashListAux,trashListFinal,trashCount);
        return 1;
    }
    return 0;
}

int Game::verifySecondDiagDown(int** field, int** trashListAux,int color,int line,int column)
{
    if(line - 1 >= 0 && column - 1 >= 0)
    {
        if(color == field[line - 1][column - 1])
        {
            trashListAux[line - 1][column - 1] = 1;
            return 1 + verifySecondDiagDown(field,trashListAux,color,line - 1,column - 1);
        }
    }
    return 0;
}

int Game::verifySecondDiagUp(int** field, int** trashListAux,int color,int line,int column)
{
    if(line + 1 < 15 && column + 1 < 7)
    {
        if(color == field[line + 1][column + 1])
        {
            trashListAux[line + 1][column + 1] = 1;
            return 1 + verifySecondDiagUp(field,trashListAux,color,line + 1,column + 1);
        }
    }
    return 0;
}///FIM verifica em diagonal secundaria

void Game::clearTrashListFinal(int** trashListFinal,int* trashCount)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
            trashListFinal[i][j] = 0;
    }
    trashCount = 0;
}

bool Game::verifyCoord(int x,int y,int** trash)
{
    if(trash[x][y] == 1)
        return true;
    return false;
}

void Game::clear(int ** field,int** trashListFinal, int* trashCount)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
            if(trashListFinal[i][j] == 1)
            {
                addColor(field,i,j,0);
                trashListFinal[i][j] = 0;
            }
    }
    *trashCount = 0;
}

int Game::verifyAll(int** field, int** trashListAux, int** trashListFinal,int* trashCount,int line, int column)
{
    int trash = 0;
    int trashColumn = verifyColumn(field,trashListAux, trashListFinal,trashCount,line,column);
    int trashLine = verifyLine(field,trashListAux,trashListFinal,trashCount,line,column);
    int trashMainDiag = verifyMainDiag(field,trashListAux,trashListFinal,trashCount,line,column);
    int trashSecondDiag = verifySecondDiag(field,trashListAux,trashListFinal,trashCount,line,column);
    if(trashColumn == 1 || trashLine == 1 || trashMainDiag == 1 || trashSecondDiag == 1)
    {
        trash = 1;
    }

    return trash;
}

int Game::runVerification(int** field, int** trashListAux1, int** trashListFinal1, int player)
{
    int trash = 0;
    if(player == 1)
    {
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(field[i][j] != 0 && field[i][j] != 6)
                {
                    if(trash == 0)
                    {
                        trash = verifyAll(field,trashListAux1, trashListFinal1,&trashCount1,i,j);
                    }
                    else
                    {
                        verifyAll(field,trashListAux1, trashListFinal1,&trashCount1,i,j);
                    }
                }
            }
        }

        brokenBlocks1 += trashCount1;
        int brokenBlocksPoints = trashCount1;
        if(trash == 1)
        {
            if(gameState == 5){
                lineBlock(1,trashCount1);
                }
            points += exponencialPoints(brokenBlocksPoints);
            if(points/level > 250)
            {
                level += 1;
            }
            getReadjustPosition(field,trashListFinal1,trashReadjust);
            clear(field,trashListFinal1,&trashCount1);
            animationOn = 1;
        }
    }
    else if(player == 2)
    {
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(field[i][j] != 0 && field[i][j] != 6)
                {
                    if(trash == 0)
                    {
                        trash = verifyAll(field,trashListAux1, trashListFinal1,&trashCount2,i,j);
                    }
                    else
                    {
                        verifyAll(field,trashListAux1, trashListFinal1,&trashCount2,i,j);
                    }
                }
            }
        }

        brokenBlocks2 += trashCount2;
        int brokenBlocksPoints2 = trashCount2;

        if(trash == 1){
            lineBlock(2,trashCount2);
            points += exponencialPoints(brokenBlocksPoints2);
            if(points/level > 250)
            {
                level += 1;
            }
            getReadjustPosition(field,trashListFinal1,trashReadjust2);
            clear(field,trashListFinal1,&trashCount2);
            animationOn2 = 1;
        }

    }
    return trash;
}

void Game::clearTrashReadjust(int** trashr)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
            trashr[i][j] = 0;
    }
}

void Game::getPosition(int** field,int** trashf,int** trashr,int x, int y)
{
    for(int i = y + 1; i < 15; i++)
    {
        if(field[i][x] != 0 && !verifyCoord(i,x,trashf))
            trashr[i][x] = field[i][x];
    }
}

void Game::getReadjustPosition(int** field,int** trashf,int** trashr)
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(trashf[j][i] == 1)
            {
                getPosition(field,trashf,trashr,i,j);
            }
        }
    }
}

void Game::updateFieldReadjust(int** field,int** trash)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(i == 14)
            {
                trash[i][j] = 0;
            }
            else
            {
                if(getColor(field,i,j) == 0 && trash[i + 1][j] != 0)
                {
                    trash[i][j] = trash[i + 1][j];
                    trash[i + 1][j] = 0;
                    field[i + 1][j] = 0;
                    field[i][j] = trash[i][j];
                }
            }
        }
    }
}

void Game::updateReadjust(int** field,int** trash)
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(j == 0)
            {
                trash[j][i] = 0;
            }
            else if(j > 0 && getColor(field,j - 1,i) == 0 && trash[j][i] != 0)
            {
                break;
            }
            else
            {
                trash[j][i] = 0;
            }
        }
    }
}

bool Game::verifyReadjust(int** trash)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(trash[i][j] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

int** Game::getTrashReadjust()
{
    return trashReadjust;
}

int** Game::getTrashReadjust2()
{
    return trashReadjust2;
}

int** Game::getField1()
{
    return field1;
}

int** Game::getField2()
{
    return field2;
}

int** Game::getTrashListAux()
{
    return trashListAux;
}

int** Game::getTrashListAux2()
{
    return trashListAux2;
}

int** Game::getTrashListFinal()
{
    return trashListFinal;
}

int** Game::getTrashListFinal2()
{
    return trashListFinal2;
}

int Game::exponencialPoints(int i)
{
    return pow(2,i-1);
}
int Game::getPoints()
{
    return this->points;
}
void Game::setGameState(int gameState)
{
    this->gameState = gameState;
}
int Game::getGameState()
{
    return this->gameState;
}


Ranking* Game::getRanking()
{
    return ranking;
}

Piece* Game::getPiece()
{
    return piece;
}

Piece* Game::getPiece2()
{
    return piece2;
}

Piece* Game::getNextPiece()
{
    return nextPiece;
}
Piece* Game::getNextPiece2()
{
    return nextPiece2;
}


void Game::setPiece(Piece* p)
{
    this->piece = p;
}
void Game::setPiece2(Piece* p)
{
    this->piece2 = p;
}

void Game::createNextPiece()
{
    nextPiece = new Piece();
    nextPiece2 = new Piece();
}

void Game::resetGame()
{
    for(int i = 0; i < 18; i++)
    {
        for(int j =0; j < 7; j++)
        {
            field1[i][j] = 0;
            field2[i][j] = 0;
        }
    }
    points = 0 ;
    trashCount1 = 0;
    trashCount2 = 0;
    level = 1;
    pause = false;

    lineblock = 0;
    lineblock2 = 0;

    clearTrashListAux(this->trashListAux);
    clearTrashListFinal(this->trashListFinal,&trashCount1);
    clearTrashListAux(this->trashListAux2);
    clearTrashListFinal(this->trashListFinal2,&trashCount2);
    clearTrashReadjust(trashReadjust);
    clearTrashReadjust(trashReadjust2);

    brokenBlocks1 = 0;
    brokenBlocks2 = 0;
    piece = new Piece();
    nextPiece = new Piece();
}

int Game::getLevel()
{
    return level;
}

int Game::getAnimationOn()
{
    return animationOn;
}

int Game::getAnimationOn2()
{
    return animationOn2;
}


bool Game::getPause()
{
    return pause;
}

void Game::setPause(bool p)
{
    pause = p;
}

void Game::displayGame(int width, int height, int moveX, int moveY, bool &shift, int typeShift,float animationMove,float rotationX, float rotationY,float distOrigem)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);///z-buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(gameView == 0){
        glOrtho(-1.0,50.0,-1.0,105.0,-10.0,10.0);
    }else{
        gluPerspective(60.0, (GLfloat) (width/2)/(GLfloat) height, 1.0, 200.0);
        gluLookAt (25.0, 40.0, distOrigem, 25.0, 35.0, 0.0, 0.0, 1.0, 0.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) width*0.55, (int) height);

    glEnable(GL_LIGHTING);

    GLfloat cor0[] = {1.0,1.0,1.0,1.0};
    GLfloat corAmbient[] = {0.5,0.5,0.5,1.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,corAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR , cor0);

    float light0_position [3] = {18.0,105.0,1.0};
    glPushMatrix();
    ///luz mexe junto com a camera
    //glLoadIdentity();
    glTranslatef(light0_position[0], light0_position[1], light0_position[2]);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.05, 10, 10);
    glPopMatrix();



    glPushMatrix();
    if(gameView != 0)
    {
        glRotatef( rotationY, 1.0, 0.0, 0.0 );
        glRotatef( rotationX, 0.0, 1.0, 0.0 );
    }

    this->drawField(field1,trashReadjust,animationMove,animationOn);
    glEnable(GL_LIGHTING);
    this->getPiece()->drawPiece(moveX,moveY);
    glPopMatrix();



    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(20.0,55.0,20,60.0,-10.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) width*0.79, (int) height*0.71, (int) width*0.21, (int) height*0.29);
    this->getNextPiece()->drawPiece(0,-80);

    glDisable(GL_LIGHTING);
    this->drawPoints(width,height);
    if(shift)
    {
        if(typeShift == 0)
            this->getPiece()->shiftColor();
        else
            this->getPiece()->shiftColorMouse();
        shift = false;
    }
    glutPostRedisplay();
}

void Game::displayGame2Players(int width, int height, int moveX, int moveY, bool &shift, int typeShift,float animationMove,int moveX2, int moveY2, bool &shift2,float distOrigem,float rotationX, float rotationY,float animationMove2)
{
    ///player1
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    if(gameView == 0)
    {
        glOrtho(-1.0,50.0,-1.0,105.0,-10.0,10.0);
    }
    else
    {
        gluPerspective(60.0, (GLfloat) (width/2)/(GLfloat) height, 1.0, 200.0);
        gluLookAt (25.0, 40.0, distOrigem, 25.0, 35.0, 0.0, 0.0, 1.0, 0.0);
    }


    glEnable(GL_LIGHTING);

    GLfloat cor0[] = {1.0,1.0,1.0,1.0};
    GLfloat corAmbient[] = {0.5,0.5,0.5,1.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,corAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR , cor0);

    float light0_position [3] = {18.0,105.0,1.0};
    glPushMatrix();
    ///luz mexe junto com a camera
    //glLoadIdentity();
    glTranslatef(light0_position[0], light0_position[1], light0_position[2]);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.05, 10, 10);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) width*0.45, (int) height);

    glPushMatrix();
    if(gameView != 0)
    {
        glRotatef( rotationY, 1.0, 0.0, 0.0 );
        glRotatef( rotationX, 0.0, 1.0, 0.0 );
    }
    this->drawField(this->field1,trashReadjust,animationMove,animationOn);
    glEnable(GL_LIGHTING);
    this->getPiece()->drawPiece(moveX,moveY);
    glPopMatrix();

    drawLevel(width,height);

    ///player2
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(gameView == 0)
    {
        glOrtho(-1.0,50.0,-1.0,105.0,-10.0,10.0);
    }
    else
    {
        gluPerspective(60.0, (GLfloat) (width/2)/(GLfloat) height, 1.0, 200.0);
        gluLookAt (25.0, 40.0, distOrigem, 25.0, 35.0, 0.0, 0.0, 1.0, 0.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) width*0.55, (int) 0, (int) width*0.45 ,(int) height);
    glPushMatrix();
    if(gameView != 0)
    {
        glRotatef( rotationY, 1.0, 0.0, 0.0 );
        glRotatef( rotationX, 0.0, 1.0, 0.0 );
    }
    this->drawField(this->field2,trashReadjust2,animationMove2,animationOn2);
    glEnable(GL_LIGHTING);
    this->getPiece2()->drawPiece(moveX2,moveY2);
    glPopMatrix();



    if(shift)
    {
        piece->shiftColor();
        shift = false;
    }

    if(shift2)
    {
        piece2->shiftColor();
        shift2 = false;
    }

    glutPostRedisplay();

}

void Game::drawLevel(int w,int h)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0,1100.0,-300,200.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) w*0.45, (int) 0, (int) w*0.10, (int) h);
    glColor3f(1,1,1);
    char lvl [] = "LVL: ";
    int x = -100;
    for ( int i = 0; i < 5; i++)
    {
        glRasterPos3f ( x + i*250,50, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lvl[i]);
    }

    scoreDisplay(1000,50,0,180,this->level);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Game::drawPoints(int w,int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0,1100.0,-300,200.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) w*0.46, (int) h*0.44, (int) w*0.55, (int) h*0.29);

    glColor3f(1,1,1);
    int x  = 100;
    char rankingPoints [] = "POINTS: ";
    for ( int i = 0; i < 8; i++)
    {
        glRasterPos3f ( x + i*40,-150, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rankingPoints[i]);
    }

    scoreDisplay(650,-150,0,25,this->points);

    char rankingBlocks [] = "BROKEN BLOCKS: ";

    for ( int i = 0; i < 15; i++)
    {
        glRasterPos3f ( x + i*40,-50, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rankingBlocks[i]);
    }

    scoreDisplay(800,-50,0,25,brokenBlocks1);

    char lvl [] = "LEVEL: ";

    for ( int i = 0; i < 7; i++)
    {
        glRasterPos3f ( x + i*40,50, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lvl[i]);
    }

    scoreDisplay(550,50,0,25,this->level);
}

void Game::drawStartScreen(int w,int h)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Proje\E7\E3o
    glLoadIdentity();
    glOrtho(0.0,300.0, -200.0, 50.0, -1.0, 1.0);
    glColor3f(1.0,0.0,0.0);
    glViewport ((int) 0, (int) 0, (int) w, (int) h);

    glBegin(GL_QUADS);
    glVertex3f (125, 0, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (175, -30, 0.0);
    glVertex3f (175, 0, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f (125, 0, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (175, -30, 0.0);
    glVertex3f (175, 0, 0.0);
    glEnd();


    int posX = 137;

    char start[] = "START";

    for (int i = 0; i < 5; i++)
    {
        glRasterPos3f (posX + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, start[i]);
    }

    glColor3f(0.0,0.5,0.0);


    glBegin(GL_QUADS);
    glVertex3f (125, -60, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (175, -30, 0.0);
    glVertex3f (175, -60, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f (125, -60, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (175, -30, 0.0);
    glVertex3f (175, -60, 0.0);
    glEnd();

    posX = 130;

    char ranking[] = "RANKING";

    for (int i = 0; i < 7; i++)
    {
        glRasterPos3f (posX + i*6,-50, 0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ranking[i]);
    }

    glColor3f(0.2549,0.4117,1);


    glBegin(GL_QUADS);
    glVertex3f (125, -90, 0.0);
    glVertex3f (125, -60, 0.0);
    glVertex3f (175, -60, 0.0);
    glVertex3f (175, -90, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f (125, -90, 0.0);
    glVertex3f (125, -60, 0.0);
    glVertex3f (175, -60, 0.0);
    glVertex3f (175, -90, 0.0);
    glEnd();

    posX = 137;

    char sair[] = "SAIR";

    for (int i = 0; i < 4; i++)
    {
        glRasterPos3f (posX + i*6,-80, 0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sair[i]);
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}

void Game::scoreDisplay(int posx, int posy, int posz, int space_char, int scorevar)
{
    int j=0,p,k;
    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

    p = scorevar;
    j = 0;
    k = 0;
    while(p > 9)
    {
        k = p % 10;
        glRasterPos3f ((posx-(j*space_char)),posy, posz);
        glutBitmapCharacter(font_style1,48+k);
        j++;
        p /= 10;
    }
    glRasterPos3f ((posx-(j*space_char)), posy, posz);
    glutBitmapCharacter(font_style1,48+p);

}

void Game::drawStartScreenPlayerOption(int w,int h)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Proje\E7\E3o
    glLoadIdentity();
    glOrtho(0.0,300.0, -200.0, 50.0, -1.0, 1.0);
    glColor3f(1.0,0.0,0.0);
    glViewport ((int) 0, (int) 0, (int) w, (int) h);

    glBegin(GL_QUADS);
    glVertex3f (125, 0, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (190, -30, 0.0);
    glVertex3f (190, 0, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f (125, 0, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (190, -30, 0.0);
    glVertex3f (190, 0, 0.0);
    glEnd();


    int posX = 137;

    char player1[] = "1 PLAYER";

    for (int i = 0; i < 8; i++)
    {
        glRasterPos3f (posX + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, player1[i]);
    }

    glColor3f(0.0,0.5,0.0);


    glBegin(GL_QUADS);
    glVertex3f (125, -60, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (190, -30, 0.0);
    glVertex3f (190, -60, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f (125, -60, 0.0);
    glVertex3f (125, -30, 0.0);
    glVertex3f (190, -30, 0.0);
    glVertex3f (190, -60, 0.0);
    glEnd();

    posX = 130;

    char player2[] = "2 PLAYERS";

    for (int i = 0; i < 9; i++)
    {
        glRasterPos3f (posX + i*6,-50, 0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, player2[i]);
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}



void Game::displayRanking(int w,int h)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 300.0, -200.0, 50.0, -1.0, 1.0);

    glViewport ((int) 0, (int) 0, (int) w, (int) h);
    char rankingText[] = "TOP SCORES";
    glColor3f(1,1,1);

    for (int i = 0; i < 10; i++)
    {
        glRasterPos3f (125 + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rankingText[i]);
    }

    for (int i = 0; i < 10; i++)
    {

        for (int j = 0; ranking->getScores()[i].name[j]; j++)
        {
            glRasterPos3f (100 + j*5,-130+i*10, 0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ranking->getScores()[i].name[j]);
        }
        scoreDisplay(200,-130+i*10,0,5,ranking->getScores()[i].score);
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

int Game::getTrashCount()
{
    return this->trashCount1;
}
int Game::getTrashCount2()
{
    return this->trashCount2;
}
int Game::getBrokenBlocks()
{
    return this->brokenBlocks1;
}
int Game::getBrokenBlocks2()
{
    return this->brokenBlocks2;
}
void Game::addBlockLine(int player,int trash){
    int lines = trash / 3;

    if(player == 1){
        for(int j = 0; j < lines; j++){
            for(int i = 0; i < 7; i++){
                field1[lineblock][i] = 6;
            }
            lineblock++;
        }
    }else{
        for(int j = 0; j < lines; j++){
            for(int i = 0; i < 7; i++){
                field2[lineblock2][i] = 6;
            }
            lineblock2++;
        }
    }
}

void Game::removeBlockLine(int player,int trash){
    int lines = trash / 3;

    if(player == 1){


        for(int k = 0; k < lines; k++){
            for(int i =0; i < 17; i++){
                for(int j = 0; j < 7; j++){
                    if(lineblock == 0)
                        return;
                    if(i < 17)
                        field1[i][j] = field1[i + 1][j];
                }
            }
            if(lineblock > 0)
                lineblock--;
        }
    }else{
        for(int k = 0; k < lines; k++){
            for(int i =0; i < 17; i++){
                for(int j = 0; j < 7; j++){
                    if(lineblock2 == 0)
                        return;
                    if(i < 17)
                        field2[i][j] = field2[i + 1][j];
                }
            }
            if(lineblock2 > 0)
                lineblock2--;
        }
    }
}

void Game::readjustUp(int player,int trash){
    int lines = trash / 3;
    if(player == 1){
        for(int k = 0; k < lines; k++){
            for(int i =17; i>= 0; i--){
                for(int j = 7; j>= 0; j--){
                    if(i > 0)
                        field1[i][j] = field1[i - 1][j];
                }
            }
        }
    }else{
        for(int k = 0; k < lines; k++){
            for(int i =17; i>= 0; i--){
                for(int j = 7; j>= 0; j--){
                    if(i > 0)
                        field2[i][j] = field2[i - 1][j];
                }
            }
        }
    }
}

void Game::lineBlock(int player, int trashCount){

    if(player == 1){
        removeBlockLine(1,trashCount);
        readjustUp(2,trashCount);
        addBlockLine(2,trashCount);
    }else{
        removeBlockLine(2,trashCount);
        readjustUp(1,trashCount);
        addBlockLine(1,trashCount);
    }
}

void Game::displayGameOver2Players(int w,int h)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Proje\E7\E3o
    glLoadIdentity();
    glOrtho(0.0, 300.0, -200.0, 50.0, -1.0, 1.0);

    glViewport ((int) 0, (int) 0, (int) w, (int) h);
    char msg[] = "CONGRATULATIONS";

    glColor3f(1,1,1);

    for (int i = 0; i < 15; i++)
    {
        glRasterPos3f (125 + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);
    }

    char player [15];
    if(isGameOver(2) == 2)
    {
        strcpy(player,"Player One won!");
    }
    else if(isGameOver(1) == 1)
    {
        strcpy(player,"Player Two won!");
    }

    //
    for (int i = 0; i < 15; i++)
    {
        glRasterPos3f (110 + i*5,-40, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, player[i]);
    }

    char leave[] = "Press esc to leave to main menu";
    for (int i = 0; i < 31; i++)
    {
        glRasterPos3f (110 + i*5,-100, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leave[i]);
    }

}

void Game::displayGameOver(int w,int h)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Proje\E7\E3o
    glLoadIdentity();
    glOrtho(0.0, 300.0, -200.0, 50.0, -1.0, 1.0);

    glViewport ((int) 0, (int) 0, (int) w, (int) h);
    char gameover[] = "GAME OVER";

    ranking->addPointsToCurrentRanking(points);
    glColor3f(1,1,1);

    for (int i = 0; i < 9; i++)
    {
        glRasterPos3f (125 + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameover[i]);
    }

    char time_1[] = "Your score was  ";

    for (int i = 0; i < 14; i++)
    {
        glRasterPos3f (110 + i*5,-40, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, time_1[i]);
    }
    scoreDisplay(200,-40,0,5,this->points);

    if(points >= ranking->getScores()[0].score)
    {
        char enterName[] = "Enter your name:";
        for (int i = 0; i < 16; i++)
        {
            glRasterPos3f (110 + i*5,-60, 0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, enterName[i]);
        }

        for (int i = 0; ranking->getCurrentName(i); i++)
        {
            glRasterPos3f (125 + i*5,-80, 0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ranking->getCurrentName(i));
        }

        char save[] = "Press enter to save";
        for (int i = 0; i < 19; i++)
        {
            glRasterPos3f (110 + i*5,-100, 0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, save[i]);
        }
    }
    else
    {
        char leave[] = "Press esc to leave to main menu";
        for (int i = 0; i < 31; i++)
        {
            glRasterPos3f (110 + i*5,-100, 0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, leave[i]);
        }
    }
}

void Game::setAnimationOn(int a)
{
    animationOn = a;
}

void Game::setAnimationOn2(int a)
{
    animationOn2 = a;
}

Game::~Game()
{

}
