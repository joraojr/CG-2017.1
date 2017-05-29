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
    c[0]->drawObject(0,24.5,122.5);
    c[1]->drawObject(0,24.5,115.5);
    c[2]->drawObject(0,24.5,108.5);
    glPopMatrix();
}

void Piece::shiftColor(){
    int tempType;
    tempType = c[0]->getType();
    c[0]->setType(c[1]->getType());
    c[1]->setType(c[2]->getType());
    c[2]->setType(tempType);
}

void Piece::shiftColorMouse(){
    int tempType;
    tempType = c[2]->getType();
    c[2]->setType(c[1]->getType());
    c[1]->setType(c[0]->getType());
    c[0]->setType(tempType);

}

int* Piece::getCubesColor()
{
    int* colors = new int[3];
    for(int i = 0;i < 3;i++){
        colors[i] = c[i]->getType();
    }

    return colors;
}


