#include "Cube.h"
#include <GL/glui.h>
#include <cstdlib>
#include <iostream>
#include <time.h>

Cube::Cube(){
    size = 7;
    randomObject();
}

void Cube::setMaterial(GLfloat *ambient, GLfloat *diffuse, GLfloat *specular,
					  GLfloat *shininess){
   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void Cube::drawObject(int t,float positionX,float positionY){
    int object;
    if(t != 0){
        object = t;
    }else{
        object = type;
    }

    switch(object){
        case 1:
            drawCube(positionX,positionY);
            break;
        case 2:
            drawTorus(positionX,positionY);
            break;
        case 3:
            drawSphere(positionX,positionY);
            break;
        case 4:
            drawTeapot(positionX,positionY);
            break;
        case 5:
            drawCone(positionX,positionY);
            break;
        case 6:
            drawGrayCube(positionX,positionY);
            break;
    }
}

void Cube::drawGrayCube(float positionX,float positionY){
    GLfloat objeto_ambient[]   = { 0.4145, 0.41175, 0.41175, 1.0 };
    GLfloat objeto_difusa[]    = { 0.39424, 0.38136, 0.38136, 1.0 };
    GLfloat objeto_especular[] = { 0.67811, 0.226959, 0.126959, 1.0 };
    GLfloat objeto_brilho[]    = { 90.0f };



    glPushMatrix();
        setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);
        glTranslatef(positionX,positionY,3.5);
        glutSolidCube(size*0.8);
    glPopMatrix();
}

void Cube::drawCube(float positionX,float positionY){
    GLfloat objeto_ambient[]   = { 0.9745, 0.11175, 0.11175, 1.0 };
    GLfloat objeto_difusa[]    = { 0.71424, 0.24136, 0.24136, 1.0 };
    GLfloat objeto_especular[] = { 0.67811, 0.226959, 0.126959, 1.0 };
    GLfloat objeto_brilho[]    = { 90.0f };


    glPushMatrix();
        setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);
        glTranslatef(positionX,positionY,3.5);
        glutSolidCube(size*0.8);
    glPopMatrix();
}

void Cube::drawSphere(float positionX,float positionY){
    GLfloat objeto_ambient[]   = { 0.08745, 0.11175, 0.91175, 1.0 };
    GLfloat objeto_difusa[]    = { 0.071424, 0.24136, 0.84136, 1.0 };
    GLfloat objeto_especular[] = { 0.067811, 0.226959, 0.726959, 1.0 };
    GLfloat objeto_brilho[]    = { 128.0f };

    setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);

    glPushMatrix();
        glTranslatef(positionX,positionY,3.5);
        glutSolidSphere(size/2,20,20);
    glPopMatrix();
}

void Cube::drawTeapot(float positionX,float positionY){

    GLfloat objeto_ambient[]   = { 0.93231, 0.93554, 0.02132, 0.5 };
    GLfloat objeto_difusa[]    = { 0.83221, 0.85431, 0.0211, 0.6 };
    GLfloat objeto_especular[] = { 0.73125, 0.7888, 0.021, 0.6 };
    GLfloat objeto_brilho[]    = { 90.0f };

    setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);

    glPushMatrix();
        glTranslatef(positionX,positionY,3.5);
        glutSolidTeapot(size*0.29);
    glPopMatrix();
}

void Cube::drawTorus(float positionX,float positionY){

    GLfloat objeto_ambient[]   = { 0.1745, 0.901175, 0.11175, 1.0 };
    GLfloat objeto_difusa[]    = { 0.21424, 0.824136, 0.24136, 1.0 };
    GLfloat objeto_especular[] = { 0.127811, 0.7226959, 0.126959, 1.0 };
    GLfloat objeto_brilho[]    = { 90.0f };

    setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);

    glPushMatrix();
        glTranslatef(positionX,positionY,3.5);
        glutSolidTorus(size*0.14,size*0.28,20,20);
    glPopMatrix();
}

void Cube::drawCone(float positionX,float positionY){

    GLfloat objeto_ambient[]   = { 0.91745, 0.01175, 0.971175, 1.0 };
    GLfloat objeto_difusa[]    = { 0.821424, 0.24136, 0.854136, 1.0 };
    GLfloat objeto_especular[] = { 0.7127811, 0.226959, 0.7826959, 1.0 };
    GLfloat objeto_brilho[]    = { 90.0f };

    setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);
    glPushMatrix();
        glTranslatef(positionX,positionY - 2,3.5);
        glRotatef(-90,1.0,0.0,0.0);
        glutSolidCone(size/2,size*0.64,20,20);
    glPopMatrix();
}

int Cube::getType(){
    return type;
}

void Cube::randomObject(){
    int aleatorio = 1 + rand()%5;
    switch(aleatorio){
        case 1:
            type = 1;
            break;
        case 2:
            type = 2;
            break;
        case 3:
            type = 3;
            break;
        case 4:
            type = 4;
            break;
        case 5:
            type = 5;
            break;
    }
}

void Cube::setType(int t){
    type = t;
}

Cube::~Cube(){

}
