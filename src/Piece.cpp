#include "Piece.h"
#include <GL/glut.h>
#include <ctime>

Piece::Piece()
{
    c[0] = new Cube();
    c[1] = new Cube();
    c[2] = new Cube();
}

void Piece::drawPiece(float moveX,float moveY)
{
    glPushMatrix();
    glTranslatef(moveX,moveY,0.0);
    c[0]->drawCube(24.5,122.5);
    c[1]->drawCube(24.5,115.5);
    c[2]->drawCube(24.5,108.5);
    glPopMatrix();
}

void Piece::shiftColor()
{
    float* aux;
    aux = c[0]->getColor();
    c[0]->setColor(c[1]->getColor());
    c[1]->setColor(c[2]->getColor());
    c[2]->setColor(aux);
}

void Piece::shiftColorMouse(){
    float* aux;
    aux = c[2]->getColor();
    c[2]->setColor(c[1]->getColor());
    c[1]->setColor(c[0]->getColor());
    c[0]->setColor(aux);

}

int * Piece::getCubesColor()
{
    int colors[5];

    for(int i = 0;i < 3;i++){

        if(this->c[i]->getColor()[0] == 1.0 && this->c[i]->getColor()[1] == 0.0 && this->c[i]->getColor()[2] == 0.0)
            colors[i] = 1;
        else if(this->c[i]->getColor()[0] == 0.0 && this->c[i]->getColor()[1] == 1.0 && this->c[i]->getColor()[2] == 0.0)
            colors[i] = 2;
        else if(this->c[i]->getColor()[0] == 0.0 && this->c[i]->getColor()[1] == 0.0 && this->c[i]->getColor()[2] == 1.0)
            colors[i] = 3;
        else if(this->c[i]->getColor()[0] == 1.0 && this->c[i]->getColor()[1] == 1.0 && this->c[i]->getColor()[2] == 0.0)
            colors[i] = 4;
        else if(this->c[i]->getColor()[0] == 1.0 && this->c[i]->getColor()[1] == 0.0 && this->c[i]->getColor()[2] == 1.0)
            colors[i] = 5;
    }

    return colors;
}


