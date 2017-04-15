#include "Game.h"

Game::Game()
{
    /// 1- vermelho, 2-Verde, 3-Azul , 0-Vazio
    for(int i = 0; i < 15; i++)
    {
        for(int j =0; j < 7; j++)
            field[i][j] = 0 ;
    }
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
        glutSolidCube(6.9);
        glPopMatrix();

        break;
    case 2:
        glColor3f(0,1,0);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(6.9);
        glPopMatrix();

        break;
    case 3:
        glColor3f(0,0,1);
        glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(6.9);
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
