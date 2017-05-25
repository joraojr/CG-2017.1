#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
    /// 1- vermelho, 2-Verde, 3-Azul, 4- Amarelo, 5-Magenta , 0-Vazio
    field = new int*[18];
    for(int i = 0; i < 18; i++)
    {
        field[i] = new int[7];
        for(int j =0; j < 7; j++)
            field[i][j] = 0 ;
    }

    trashListAux = new int*[15];
    trashListFinal = new int*[15];
    for(int i = 0; i < 15; i++)
    {
        trashListAux[i] = new int[7];
        trashListFinal[i] = new int[7];
        for(int j =0; j < 7; j++)
        {
            trashListAux[i][j] = 0;
            trashListFinal[i][j] = 0;
        }
    }

    points = 0 ;
    trashCount = 0;
    gameState = 0;
    level = 1;
    pause = false;
    ranking = new Ranking();
    brokenBlocks = 0;
    piece = new Piece();
    nextPiece = new Piece();
}

void Game::drawCubeColor(int i, int j, float positionX, float positionY)
{
    ///desenhar a cor do cubo
    switch(field[i][j])
    {
    case 0:
        glColor3f(0,0,0);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(7.0);
        glPopMatrix();
        break;
    case 1:
        glColor3f(1,0,0);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(7.0);
        glPopMatrix();
        break;
    case 2:
        glColor3f(0,1,0);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(7.0);
        glPopMatrix();
        break;
    case 3:
        glColor3f(0,0,1);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(7.0);
        glPopMatrix();
        break;
    case 4:
        glColor3f(1,1,0);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(7.0);
        glPopMatrix();
        break;
    case 5:
        glColor3f(1,0,1);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(7.0);
        glPopMatrix();
        break;
    }

}

void Game::drawField()
{
    float x = 0.0;
    float y = 0.0;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            this->drawCubeColor(i,j,x+3.5,y+3.5);
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

void Game:: drawPoints(int w,int h)
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

    scoreDisplay(800,-50,0,25,this->brokenBlocks);

    char lvl [] = "LEVEL: ";

    for ( int i = 0; i < 7; i++)
    {
        glRasterPos3f ( x + i*40,50, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lvl[i]);
    }

    scoreDisplay(550,50,0,25,this->level);
}

void Game::addColor(int i, int j, int color)
{
    field[i][j] = color ;
}

int Game::getColor(int i, int j)
{
    if(i == -1 || j == 7 || j == -1)
        return -1;
    return field[i][j];
}

bool Game::isGameOver()
{
    for(int i = 0; i < 7; i++)
    {
        if(field[15][i] != 0)
            return true;
    }
    return false;
}

void Game::printMatrix()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j =0; j < 2; j++)
            cout << trashListFinal[i][j] << ";";
        cout  << "]]";
    }
    cout << endl;
}

bool Game::verifyMoveLeft(int line,int column)
{
    if(field[line][column-1] == 0)
        return true;
    return false;
}

bool Game::verifyMoveRight(int line,int column)
{
    if(field[line][column+1] == 0)
        return true;
    return false;
}
///verificar em linha
int Game::verifyLineLeft(int color,int line, int column)
{
    if(column - 1 >= 0)
    {
        if(color == field[line][column - 1])
        {
            trashListAux[line][column - 1] = 1;
            return 1 + verifyLineLeft(color,line,column - 1);
        }
    }
    return 0;
}

int Game::verifyLineRight(int color,int line, int column)
{
    if(column + 1 < 7)
    {
        if(color == field[line][column + 1])
        {
            trashListAux[line][column + 1] = line;
            return 1 + verifyLineRight(color,line,column + 1);
        }
    }
    return 0;
}

int Game::verifyLine(int line, int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifyLineLeft(field[line][column],line,column);
    countC += verifyLineRight(field[line][column],line,column);

    if(countC < 3)
        clearTrashListAux();
    else
    {
        copyToTrashListFinal(trashListAux);
        return 1;
    }
    return 0;
}

void Game::copyToTrashListFinal(int** matriz)
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(trashListAux[i][j] == 1 && !verifyCoord(i,j,trashListFinal))
            {
                trashListFinal[i][j] = 1;
                trashCount += 1;
            }
        }
    }
    clearTrashListAux();
}

//reseta a matriz com as coordenadas
void Game::clearTrashListAux()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
            trashListAux[i][j] = 0;
    }
}///FIM verifica Linha

///verifica em coluna
int Game::verifyColumnDown(int color,int line,int column)
{
    if(line - 1 >= 0)
    {
        if(color == field[line - 1][column])
        {
            trashListAux[line - 1][column] = 1;
            return 1 + verifyColumnDown(color,line - 1,column);
        }
    }
    return 0;
}

int Game::verifyColumnUp(int color,int line,int column)
{
    if(line + 1 < 15)
    {
        if(color == field[line + 1][column])
        {
            trashListAux[line + 1][column] = 1;
            return 1 + verifyColumnUp(color,line + 1,column);
        }
    }
    return 0;
}

int Game::verifyColumn(int line, int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifyColumnDown(field[line][column],line,column);
    countC += verifyColumnUp(field[line][column],line,column);

    if(countC < 3)
        clearTrashListAux();
    else
    {
        copyToTrashListFinal(trashListAux);
        return 1;
    }
    return 0;
}
///FIM verifica em coluna

///verificar em diagonal primaria


int Game::verifyMainDiag(int line, int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifyMainDiagUp(field[line][column],line,column);
    countC += verifyMainDiagDown(field[line][column],line,column);
    if(countC < 3)
        clearTrashListAux();
    else
    {
        copyToTrashListFinal(trashListAux);
        return 1;
    }
    return 0;
}

int Game::verifyMainDiagUp(int color,int line, int column)
{
    if(line - 1 >= 0 && column + 1 < 7)
    {
        if(color == field[line - 1][column + 1])
        {
            trashListAux[line - 1][column + 1] = 1;
            return 1 + verifyMainDiagUp(color,line - 1,column + 1);
        }
    }
    return 0;
}

int Game::verifyMainDiagDown(int color,int line, int column)
{
    if(line + 1 < 15 && column - 1 >= 0)
    {
        if(color == field[line + 1][column - 1])
        {
            trashListAux[line + 1][column - 1] = 1;
            return 1 + verifyMainDiagDown(color,line + 1,column - 1);
        }
    }
    return 0;
}///FIM verifica em diagonal primaria

///Verificar em diagonal secundaria
int Game::verifySecondDiag(int line,int column)
{
    int countC = 1;
    trashListAux[line][column] = 1;
    countC += verifySecondDiagUp(field[line][column],line,column);
    countC += verifySecondDiagDown(field[line][column],line,column);
    if(countC < 3)
        clearTrashListAux();
    else
    {
        copyToTrashListFinal(trashListAux);
        return 1;
    }
    return 0;
}

int Game::verifySecondDiagDown(int color,int line,int column)
{
    if(line - 1 >= 0 && column - 1 >= 0)
    {
        if(color == field[line - 1][column - 1])
        {
            trashListAux[line - 1][column - 1] = 1;
            return 1 + verifySecondDiagDown(color,line - 1,column - 1);
        }
    }
    return 0;
}

int Game::verifySecondDiagUp(int color,int line,int column)
{
    if(line + 1 < 15 && column + 1 < 7)
    {
        if(color == field[line + 1][column + 1])
        {
            trashListAux[line + 1][column + 1] = 1;
            return 1 + verifySecondDiagUp(color,line + 1,column + 1);
        }
    }
    return 0;
}///FIM verifica em diagonal secundaria

void Game::clearTrashListFinal()
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

void Game::clear()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
            if(trashListFinal[i][j] == 1)
            {
                addColor(i,j,0);
                trashListFinal[i][j] = 0;
            }
    }
    trashCount = 0;
}

int Game::verifyAll(int line, int column)
{
    int trash = 0;
    int trashColumn = verifyColumn(line,column);
    int trashLine = verifyLine(line,column);
    int trashMainDiag = verifyMainDiag(line,column);
    int trashSecondDiag = verifySecondDiag(line,column);
    if(trashColumn == 1 || trashLine == 1 || trashMainDiag == 1 || trashSecondDiag == 1)
    {
        trash = 1;
    }

    return trash;
}

void Game::runVerification()
{
    int trash = 0;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(field[i][j] != 0)
            {
                if(trash == 0)
                {
                    trash = verifyAll(i,j);
                }
                else
                {
                    verifyAll(i,j);
                }
            }
        }
    }
    brokenBlocks += trashCount;
    int brokenBlocksPoints = trashCount;
    clear();///limpa o trashcount
    readjust();
    drawField();
    if(trash == 1)
    {
        points += fatorialPoints(brokenBlocksPoints);
        if(points/level > 250)
        {
            level += 1;
        }
        runVerification();
    }
}

void Game::readjust()
{
    bool aux = false;
    for(int i = 0; i < 7; i++)
    {
        for(int k = 0; k < 15; k++)
        {
            for(int j = 0; j < 17; j++)
            {
                if(field[j][i] == 0)
                {
                    field[j][i] = field[j + 1][i];
                    aux = true;
                }
                if(aux)
                {
                    field[j][i] = field[j + 1][i];
                }
            }
            aux = false;
            field[17][i] = 0;
        }
    }
}

int Game::fatorialPoints(int i)
{
    if(i < 2)
        return 1;
    else
        return i*fatorialPoints(i - 1);
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
void Game::drawStartScreen(int w,int h)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
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

void Game::displayRanking(int w,int h)
{
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

}

Ranking* Game::getRanking()
{
    return ranking;
}

Piece* Game::getPiece()
{
    return piece;
}

Piece* Game::getNextPiece()
{
    return nextPiece;
}

void Game::setPiece(Piece* p)
{
    piece = p;
}

void Game::createNextPiece()
{
    nextPiece = new Piece();
}

void Game::resetGame()
{
    for(int i = 0; i < 18; i++)
    {
        for(int j =0; j < 7; j++)
            field[i][j] = 0 ;
    }
    points = 0 ;
    trashCount = 0;
    gameState = 0;
    level = 1;
    pause = false;
    clearTrashListAux();
    clearTrashListFinal();

    brokenBlocks = 0;
    piece = new Piece();
    nextPiece = new Piece();
}

int Game::getLevel()
{
    return level;
}

bool Game::getPause()
{
    return pause;
}

void Game::setPause(bool p)
{
    pause = p;
}
void Game::displayGame(int width, int height, int moveX, int moveY, bool &shift, int typeShift )
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,60.0,-1.0,105.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) width*0.55, (int) height);

    this->drawField();
    this->getPiece()->drawPiece(moveX,moveY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(20.0,55.0,20,60.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) width*0.79, (int) height*0.71, (int) width*0.21, (int) height*0.29);
    this->getNextPiece()->drawPiece(0,-80);


    this->drawPoints(width,height);
    if(shift)
    {
        if(typeShift == 0)
            this->getPiece()->shiftColor();
        else
            this->getPiece()->shiftColorMouse();
        shift = false;
        glutPostRedisplay();
    }
}
void Game::displayGame2Players(int width, int height, int moveX, int moveY, bool &shift, int typeShift )
{
    ///player1
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,60.0,-1.0,105.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) width*0.53, (int) height);

    this->drawField();
    this->getPiece()->drawPiece(moveX,moveY);

    ///player2
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,60.0,-1.0,105.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) width*0.55, (int) 0, (int) width*0.53 ,(int) height);
    this->drawField();
    this->getNextPiece()->drawPiece(moveX,moveY);

}
Game::~Game()
{

}
