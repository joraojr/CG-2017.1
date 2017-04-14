#include "Piece.h"
#include <GL/glut.h>

Piece::Piece(){
    c[0] = new Cube(1.0,0.0,0.0);
    c[1] = new Cube(0.0,1.0,0.0);
    c[2] = new Cube(0.0,0.0,1.0);
    shiftCount = 0;
}

void Piece::drawPiece(float moveX,float moveY){
    glPushMatrix();
        glTranslatef(moveX,moveY,0.0);
        c[0]->drawCube(24.5,101.5);
        c[1]->drawCube(24.5,94.5);
        c[2]->drawCube(24.5,87.5);
    glPopMatrix();
}

void Piece::shiftColor(){
    float* aux;
    aux = c[0]->getColor();
    c[0]->setColor(c[1]->getColor());
    c[1]->setColor(c[2]->getColor());
    c[2]->setColor(aux);
}

float ** Piece::getCubesColor(){
    float* colors[3];
    for(int i =0 ; i <3 ; i ++)
        colors[i] = c[i]->getColor();
    return colors;
}


