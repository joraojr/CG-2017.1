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
    clearTrashListColumn();
    clearTrashListLine();
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
}

void Game::addColor(int i, int j, int color){
    this->field[i][j] = color ;
}

int Game::getColor(int i, int j){
    return this->field[i][j];
}

bool Game::isGameOver(){
    for(int i = 0;i < 7;i++){
        if(field[15][i] != 0)
            return true;
    }
    return false;
}

void Game::printMatrix(){
    for(int i = 0; i < 18; i++)
    {
        for(int j =0; j < 7; j++)
            cout << field[i][j] << ";";
        cout  << endl;
    }

}

bool Game::verifyMoveLeft(int line,int column){
    if(field[line][column-1] == 0)
        return true;
    return false;
}

bool Game::verifyMoveRight(int line,int column){
    if(field[line][column+1] == 0)
        return true;
    return false;
}
///verificar em linha
int Game::verifyLineLeft(int color,int line, int column){
    if(color == field[line][column - 1]){
        trashListLine[lineCount][0] = line;
        trashListLine[lineCount][1] = column - 1;
        lineCount++;
        return 1 + verifyLineLeft(color,line,column - 1);
    }
    return 0;
}

int Game::verifyLineRight(int color,int line, int column){
    if(color == field[line][column + 1]){
        trashListLine[lineCount][0] = line;
        trashListLine[lineCount][1] = column + 1;
        lineCount++;
        return 1 + verifyLineRight(color,line,column + 1);
    }
    return 0;
}

void Game::verifyLine(int line, int column){
    int countC = 1;
    trashListLine[lineCount][0] = line;
    trashListLine[lineCount][1] = column;
    lineCount++;
    countC += verifyLineLeft(field[line][column],line,column);
    countC += verifyLineRight(field[line][column],line,column);
    if(countC < 3)
        clearTrashListLine();
    clearLine();
}
///apaga a linha
void Game::clearLine(){
    for(int i = 0; i < 7; i++){
        if(trashListLine[i][0] != -1 && trashListLine[i][1] != -1)
            addColor(trashListLine[i][0],trashListLine[i][1],0);
    }
    clearTrashListLine();
}
///reseta a matriz com as coordenadas
void Game::clearTrashListLine(){
    for(int i = 0; i < 7;i++){
        for(int j = 0;j < 2;j++)
            trashListLine[i][j] = -1;
    }
    lineCount = 0;
}

///verifica em coluna
int Game::verifyColumnDown(int color,int line,int column){
    if(color == field[line - 1][column]){
        trashListColumn[columnCount][0] = line - 1;
        trashListColumn[columnCount][1] = column;
        columnCount++;
        return 1 + verifyColumnDown(color,line - 1,column);
    }
    return 0;
}

int Game::verifyColumnUp(int color,int line,int column){
    if(color == field[line + 1][column]){
        trashListColumn[columnCount][0] = line + 1;
        trashListColumn[columnCount][1] = column;
        columnCount++;
        return 1 + verifyColumnUp(color,line + 1,column);
    }
    return 0;
}

void Game::verifyColumn(int line, int column){
    int countC = 1;
    trashListColumn[columnCount][0] = line;
    trashListColumn[columnCount][1] = column;
    columnCount++;
    countC += verifyColumnDown(field[line][column],line,column);
    countC += verifyColumnUp(field[line][column],line,column);
    if(countC < 3)
        clearTrashListColumn();
    clearColumn();
}

void Game::clearColumn(){
    for(int i = 0; i < 15; i++){
        if(trashListColumn[i][0] != -1 && trashListColumn[i][1] != -1)
            addColor(trashListColumn[i][0],trashListColumn[i][1],0);
    }
    clearTrashListColumn();
}

void Game::clearTrashListColumn(){
    for(int i = 0; i < 15;i++){
        for(int j = 0;j < 2;j++)
            trashListColumn[i][j] = -1;
    }
    columnCount = 0;
}

void Game::readjust(){
    bool aux = false;
    for(int i = 0; i < 7; i++){
        for(int k = 0; k < 15; k++){
            for(int j = 0; j < 17; j++){
                if(field[j][i] == 0){
                    field[j][i] = field[j + 1][i];
                    aux = true;
                }
                if(aux){
                    field[j][i] = field[j + 1][i];
                }
            }
            aux = false;
            field[17][i] = 0;
        }
    }
}

int Game::fatorialPoints(int i){
    if(i < 2)
        return 1;
    else
        return i*fatorialPoints(i - 1);
}

