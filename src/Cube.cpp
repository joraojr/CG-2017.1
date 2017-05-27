#include "Cube.h"
#include <GL/glui.h>
#include <cstdlib>
#include <iostream>
#include <time.h>

Cube::Cube(){
    size = 7;
    color = new float[3];
    color = randomColor();
}

void Cube::drawCube(float positionX,float positionY){
    glColor3fv(color);
    glPushMatrix();
        glTranslatef(positionX,positionY,3.5);
        glutSolidCube(size);
    glPopMatrix();
}

float* Cube::getColor(){
    return color;
}

void Cube::setColor(float* c){
    color = c;
}

float* Cube::randomColor(){
    int maior = 5;
    int menor = 1;
    int aleatorio = rand()%(maior - menor + 1) + menor;
    float* rColor = new float[3];
    switch(aleatorio){
        case 1:
            rColor[0] = 1.0;
            rColor[1] = 0.0;
            rColor[2] = 0.0;
        break;
        case 2:
            rColor[0] = 0.0;
            rColor[1] = 1.0;
            rColor[2] = 0.0;
        break;
        case 3:
            rColor[0] = 0.0;
            rColor[1] = 0.0;
            rColor[2] = 1.0;
        break;
        case 4:
            rColor[0] = 1.0;
            rColor[1] = 1.0;
            rColor[2] = 0.0;
        break;
        case 5:
            rColor[0] = 1.0;
            rColor[1] = 0.0;
            rColor[2] = 1.0;
        break;
    }

    return rColor;
}
