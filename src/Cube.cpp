#include "Cube.h"
#include <GL/glui.h>

Cube::Cube(float r, float g, float b){
    size = 7;
    color = new float[3];
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Cube::drawCube(float positionX,float positionY){
    glColor3fv(color);
    glPushMatrix();
        glTranslatef(positionX,positionY,0.0);
        glutSolidCube(size);
    glPopMatrix();
}

float* Cube::getColor(){
    return color;
}

void Cube::setColor(float* c){
    color = c;
}
