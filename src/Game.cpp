#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
    /// 1- vermelho, 2-Verde, 3-Azul, 4- Amarelo, 5-Magenta , 0-Vazio
    for(int i = 0; i < 18; i++)
    {
        for(int j =0; j < 7; j++)
            field[i][j] = 0 ;
    }
    lineCount = 0;
    columnCount = 0;
    mainDiagCount = 0;
    secondDiagCount = 0;
    points = 0 ;
    trashCount = 0;
    gameState = 0;
    clearTrashListColumn();
    clearTrashListLine();
    clearTrashList();
    clearTrashListMainDiag();
    clearTrashListSecondDiag();
    ranking = new Ranking();
}

void Game::drawCubeColor(int i, int j, float positionX, float positionY)
{
    ///desenhar a cor do cubo
    switch(this->field[i][j])
    {
    case 0:
        glColor3f(0,0,0);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(6.9);
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

//    cout<<"Points: "<<points;
}

void Game::addColor(int i, int j, int color)
{
    this->field[i][j] = color ;
}

int Game::getColor(int i, int j)
{
    return this->field[i][j];
}

void Game::isGameOver()
{
    for(int i = 0; i < 7; i++)
    {
        if(field[15][i] != 0)
            this->gameState=3;
    }
}

void Game::printMatrix()
{
    for(int i = 0; i < 18; i++)
    {
        for(int j =0; j < 7; j++)
            cout << field[i][j] << ";";
        cout  << endl;
    }

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
    if(color == field[line][column - 1])
    {
        trashListLine[lineCount][0] = line;
        trashListLine[lineCount][1] = column - 1;
        lineCount++;
        return 1 + verifyLineLeft(color,line,column - 1);
    }
    return 0;
}

int Game::verifyLineRight(int color,int line, int column)
{
    if(color == field[line][column + 1])
    {
        trashListLine[lineCount][0] = line;
        trashListLine[lineCount][1] = column + 1;
        lineCount++;
        return 1 + verifyLineRight(color,line,column + 1);
    }
    return 0;
}

void Game::verifyLine(int line, int column)
{
    int countC = 1;
    trashListLine[lineCount][0] = line;
    trashListLine[lineCount][1] = column;
    lineCount++;
    countC += verifyLineLeft(field[line][column],line,column);
    countC += verifyLineRight(field[line][column],line,column);
    cout << countC <<  endl;
    if(countC < 3)
        clearTrashListLine();
    else
    {
        copyLineToTrashList(trashListLine,countC);
        points += fatorialPoints(countC-2);
    }

}

void Game::copyLineToTrashList(int matriz[7][2],int c)
{
    for(int i = 0; i < c; i++)
    {
        if(!verifyCoord(matriz[i][0],matriz[i][1]))
        {
            trashList[trashCount][0] = matriz[i][0];
            trashList[trashCount][1] = matriz[i][1];
            trashCount++;
        }
    }
    clearTrashListLine();
}

//reseta a matriz com as coordenadas
void Game::clearTrashListLine()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 2; j++)
            trashListLine[i][j] = -1;
    }
    lineCount = 0;
}///FIM verifica Linha

///verifica em coluna
int Game::verifyColumnDown(int color,int line,int column)
{
    if(color == field[line - 1][column])
    {
        trashListColumn[columnCount][0] = line - 1;
        trashListColumn[columnCount][1] = column;
        columnCount++;
        return 1 + verifyColumnDown(color,line - 1,column);
    }
    return 0;
}

int Game::verifyColumnUp(int color,int line,int column)
{
    if(color == field[line + 1][column])
    {
        trashListColumn[columnCount][0] = line + 1;
        trashListColumn[columnCount][1] = column;
        columnCount++;
        return 1 + verifyColumnUp(color,line + 1,column);
    }
    return 0;
}

void Game::verifyColumn(int line, int column)
{
    int countC = 1;
    trashListColumn[columnCount][0] = line;
    trashListColumn[columnCount][1] = column;
    columnCount++;
    countC += verifyColumnDown(field[line][column],line,column);
    countC += verifyColumnUp(field[line][column],line,column);
    if(countC < 3)
        clearTrashListColumn();
    else
    {
        copyColumnToTrashList(trashListColumn,countC);
        points += fatorialPoints(countC-2);
    }
}

void Game::copyColumnToTrashList(int matriz[15][2],int c)
{
    for(int i = 0; i < c; i++)
    {
        if(!verifyCoord(matriz[i][0],matriz[i][1]))
        {
            trashList[trashCount][0] = matriz[i][0];
            trashList[trashCount][1] = matriz[i][1];
            trashCount++;
        }
    }
    clearTrashListColumn();
}

void Game::clearTrashListColumn()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 2; j++)
            trashListColumn[i][j] = -1;
    }
    columnCount = 0;
}///FIM verifica em coluna

///verificar em diagonal primaria
void Game::clearTrashListMainDiag()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 2; j++)
            trashListMainDiag[i][j] = -1;
    }
    mainDiagCount = 0;
}

void Game::copyMainDiagToTrashList(int matriz[7][2],int c)
{
    for(int i = 0; i < c; i++)
    {
        if(!verifyCoord(matriz[i][0],matriz[i][1]))
        {
            trashList[trashCount][0] = matriz[i][0];
            trashList[trashCount][1] = matriz[i][1];
            trashCount++;
        }
    }
    clearTrashListMainDiag();
}

void Game::verifyMainDiag(int line, int column)
{
    int countC = 1;
    trashListMainDiag[mainDiagCount][0] = line;
    trashListMainDiag[mainDiagCount][1] = column;
    mainDiagCount++;
    countC += verifyMainDiagUp(field[line][column],line,column);
    countC += verifyMainDiagDown(field[line][column],line,column);
    if(countC < 3)
        clearTrashListMainDiag();
    else
    {
        copyMainDiagToTrashList(trashListMainDiag,countC);
        points += fatorialPoints(countC-2);
    }
}

int Game::verifyMainDiagUp(int color,int line, int column)
{
    if(color == field[line - 1][column + 1])
    {
        trashListMainDiag[mainDiagCount][0] = line - 1;
        trashListMainDiag[mainDiagCount][1] = column + 1;
        mainDiagCount++;
        return 1 + verifyMainDiagUp(color,line - 1,column + 1);
    }
    return 0;
}

int Game::verifyMainDiagDown(int color,int line, int column)
{
    if(color == field[line + 1][column - 1])
    {
        trashListMainDiag[mainDiagCount][0] = line + 1;
        trashListMainDiag[mainDiagCount][1] = column - 1;
        mainDiagCount++;
        return 1 + verifyMainDiagDown(color,line + 1,column - 1);
    }
    return 0;
}///FIM verifica em diagonal primaria

///Verificar em diagonal secundaria
void Game::clearTrashListSecondDiag()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 2; j++)
            trashListSecondDiag[i][j] = -1;
    }
    secondDiagCount = 0;
}

void Game::copySecondDiagToTrashList(int matriz[7][2],int c)
{
    for(int i = 0; i < c; i++)
    {
        if(!verifyCoord(matriz[i][0],matriz[i][1]))
        {
            trashList[trashCount][0] = matriz[i][0];
            trashList[trashCount][1] = matriz[i][1];
            trashCount++;
        }
    }
    clearTrashListSecondDiag();
}

void Game::verifySecondDiag(int line,int column)
{
    int countC = 1;
    trashListSecondDiag[secondDiagCount][0] = line;
    trashListSecondDiag[secondDiagCount][1] = column;
    secondDiagCount++;
    countC += verifySecondDiagUp(field[line][column],line,column);
    countC += verifySecondDiagDown(field[line][column],line,column);
    if(countC < 3)
        clearTrashListSecondDiag();
    else
    {
        copySecondDiagToTrashList(trashListSecondDiag,countC);
        points += fatorialPoints(countC-2);
    }
}

int Game::verifySecondDiagDown(int color,int line,int column)
{
    if(color == field[line - 1][column - 1])
    {
        trashListSecondDiag[secondDiagCount][0] = line - 1;
        trashListSecondDiag[secondDiagCount][1] = column - 1;
        secondDiagCount++;
        return 1 + verifySecondDiagDown(color,line - 1,column - 1);
    }
    return 0;
}

int Game::verifySecondDiagUp(int color,int line,int column)
{
    if(color == field[line + 1][column + 1])
    {
        trashListSecondDiag[secondDiagCount][0] = line + 1;
        trashListSecondDiag[secondDiagCount][1] = column + 1;
        secondDiagCount++;
        return 1 + verifySecondDiagUp(color,line + 1,column + 1);
    }
    return 0;
}///FIM verifica em diagonal secundaria

void Game::clearTrashList()
{
    for(int i = 0; i < 105; i++)
    {
        for(int j = 0; j < 2; j++)
            trashList[i][j] = -1;
    }
    trashCount = 0;
}

bool Game::verifyCoord(int x,int y)
{
    for(int  i = 0; i < 105; i++)
    {
        if(trashList[i][0] == x && trashList[i][1] == y)
            return true;
    }
    return false;
}

void Game::clear()
{
    for(int i = 0; i < trashCount; i++)
    {
        if(trashList[i][0] != -1 && trashList[i][1] != -1)
            addColor(trashList[i][0],trashList[i][1],0);
    }
    clearTrashList();
}

void Game::verifyAll(int line, int column)
{
    verifyColumn(line,column);
    verifyLine(line,column);
    verifyMainDiag(line,column);
    verifySecondDiag(line,column);
    clear();
}

void Game::runVerification()
{
    for(int k = 0; k < 10; k++)
    {
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(field[i][j] != 0)
                {
                    verifyAll(i,j);
                    readjust();
                }
            }
        }
        drawField();
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
void Game::drawStartScreen(){

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(0.0, 300.0, -200.0, 50.0, -1.0, 1.0);
   //gluPerspective(1,2,50,500);
    glColor3f(0.2549,0.4117,1);

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

    for (int i = 0; i < 5; i++){
        glRasterPos3f (posX + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
    }

     glColor3f(0.2549,0.4117,1);


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

    for (int i = 0; i < 7; i++){
        glRasterPos3f (posX + i*6,-50, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ranking[i]);
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

    for (int i = 0; i < 4; i++){
        glRasterPos3f (posX + i*6,-80, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, sair[i]);
    }

}
void Game :: scoredisplay (int posx, int posy, int posz, int space_char, int scorevar){
    int j=0,p,k;
    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

    p = scorevar;
    j = 0;
    k = 0;
    while(p > 9){
        k = p % 10;
        glRasterPos3f ((posx-(j*space_char)),posy, posz);
        glutBitmapCharacter(font_style1,48+k);
        j++;
        p /= 10;
    }
    glRasterPos3f ((posx-(j*space_char)), posy, posz);
    glutBitmapCharacter(font_style1,48+p);

}

void Game:: displayGameOver(){
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(0.0, 300.0, -200.0, 50.0, -1.0, 1.0);
    glClearColor(0.19,0.19,0.80,1.0);
    char gameover[] = "GAME OVER";

    glColor3f(1,1,1);

    for (int i = 0; i < 9; i++){
        glRasterPos3f (125 + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameover[i]);
    }

    char time_1[] = "Your time was  ";

    for (int i = 0; i < 14; i++){
        glRasterPos3f (110 + i*5,-40, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, time_1[i]);
    }

    scoredisplay(190,-40,0,5,1);

    char enterName[] = "Enter your name:";
    for (int i = 0; i < 16; i++){
        glRasterPos3f (110 + i*5,-60, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, enterName[i]);
    }

    for (int i = 0; ranking->getCurrentName(i); i++){
        glRasterPos3f (125 + i*5,-80, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ranking->getCurrentName(i));
    }
}

void Game::displayRanking(){
    glClearColor(0.19,0.19,0.80,1.0);
    char rankingText[] = "TOP SCORES";

    glColor3f(1,1,1);

    for (int i = 0; i < 10; i++){
        glRasterPos3f (125 + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rankingText[i]);
    }

    for (int i = 0; i < 10; i++){

        for (int j = 0; ranking->getScores()[i].name[j]; j++){
            glRasterPos3f (100 + j*5,-130+i*10, 0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ranking->getScores()[i].name[j]);
        }
        scoredisplay(200,-130+i*10,0,5,ranking->getScores()[i].score);
    }

}

