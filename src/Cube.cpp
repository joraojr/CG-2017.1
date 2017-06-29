#include "Cube.h"
#include <GL/glui.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <math.h>

Cube::Cube(glcTexture *texture)
{
    size = 7;
    randomObject();
    this->textureManager = texture;
}




void Cube::setMaterial(GLfloat *ambient, GLfloat *diffuse, GLfloat *specular,
                       GLfloat *shininess)
{
    // Define os parametros da superficie a ser iluminada
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void Cube::drawObject(int t,float positionX,float positionY)
{
    int object;
    if(t != 0)
    {
        object = t;
    }
    else
    {
        object = type;
    }

    switch(object)
    {
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

void Cube::drawGrayCube(float positionX,float positionY)
{
//    GLfloat objeto_ambient[]   = { 0.4145, 0.41175, 0.41175, 1.0 };
//    GLfloat objeto_difusa[]    = { 0.39424, 0.38136, 0.38136, 1.0 };
//    GLfloat objeto_especular[] = { 0.67811, 0.226959, 0.126959, 1.0 };
//    GLfloat objeto_brilho[]    = { 90.0f };
//
//
//
//    glPushMatrix();
//    setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);
    glTranslatef(positionX,positionY,3.5);
    glutSolidCube(size*0.8);
    glPopMatrix();
}

void Cube::drawCube(float positionX,float positionY)
{
    glDisable(GL_CULL_FACE);

    textureManager->Bind(7);
    glPushMatrix();
    glTranslatef(positionX-3,positionY-3,5.5);
    glScalef(size*0.8,size*0.8,size*0.8);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.0,1.0, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f( 1.0,0.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.0,1.0,0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.0, 1.0, -1.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f( 0.0,0.0, -1.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,0.0,-1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f( 1.0,1.0, -1.0);


    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, 0.0, -1.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,1.0,-1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f( 0.0,1.0, -1.0);


    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0, 0.0, -1.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,1.0,-1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f( 0.0,1.0, -1.0);


    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,0.0,0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f( 1.0,0.0, -1.0);


    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0, 0.0, -1.0);
    glEnd();
    glPopMatrix();
    textureManager->Disable();
    glEnable(GL_CULL_FACE);

}

void Cube::drawSphere(float positionX,float positionY)
{

    textureManager->Bind(11);
    glPushMatrix();
    glTranslatef(positionX,positionY,3.5);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad,1);
    gluSphere(quad,size/2,100,100);
    glPopMatrix();
    textureManager->Disable();
}

void Cube::drawTeapot(float positionX,float positionY)
{
    glDisable(GL_CULL_FACE);

    textureManager->Bind(9);
    int tiles =1.0;
    glPushMatrix();
    ///Balão
    glTranslatef(positionX -2,positionY,1.5);
    glRotated(90,1,0,0);
    glScalef(size*0.6,size*0.6,size*0.4);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3f(0.5, -1.0, 0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0,0.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(1.0,0.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(1.0,0.5,0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0,0.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(1.0,1.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0.5,1.0,0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0,1.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(0.0,1.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(-1.0,0.5,0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0,1.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(0.0,0.0,0.0);
    glEnd();
glPopMatrix();
glPushMatrix();
    glRotatef(180,1.0,0.0,0.0);
    glTranslatef(0,-1,0.0);
    glBegin(GL_TRIANGLES);
        glNormal3f(0.5, -1.0, 0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0,0.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(1.0,0.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(1.0,0.5,0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0,0.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(1.0,1.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0.5,1.0,0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0,1.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(0.0,1.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(-1.0,0.5,0.0);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0,1.0,0.0);

        glTexCoord2f(tiles, 0.0);
        glVertex3f(0.5,0.5,1.0);

        glTexCoord2f(tiles, tiles);
        glVertex3f(0.0,0.0,0.0);
    glEnd();
    glPopMatrix();
glPopMatrix();
    textureManager->Disable();
    glEnable(GL_CULL_FACE);
}

void Cube::drawTorus(float positionX,float positionY)
{

    glDisable(GL_CULL_FACE);
    textureManager->Bind(10);

///cilindro
float pi = 3.14;
float r = 500;
int h = size*0.8;
float a = 0.0;
int numStep = 100;
float u = 0.0;

glPushMatrix();

glTranslatef(positionX ,positionY-2,3.5);
            a = 2*pi*u;
            glBegin(GL_QUAD_STRIP);
                for (int i = 0; i < numStep; i++){
                    glNormal3f(r * cos(a)/180,0.0,r*sin(a)/180);

                    glTexCoord2f(u,0.0);
                    glVertex3f(r * cos(a)/180, 0, r*sin(a)/180);
                    glTexCoord2f(u,1.0);
                    glVertex3f(r * cos(a)/180, h, r*sin(a)/180);

                    u += 0.05;
                    a = 2*pi*u;
                }

            glEnd();
            a = 0;
            u = 0;

            glBegin(GL_TRIANGLE_FAN);
                glVertex3f(0.0,0.0,0.0);
                for (int i = 0; i < numStep; i++){
                    glNormal3f(r * cos(a)/180,-1.0,r*sin(a)/180);

                    glTexCoord2f(u,0.0);
                    glVertex3f(r * cos(a)/180, 0, r*sin(a)/180);

                    u += 0.05;
                    a = 2*pi*u;
                }
            glEnd();
            a = 0;
            u = 0;

            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(u,0.0);
                glVertex3f(0.0,h,0.0);
                for (int i = 0; i < numStep; i++){
                    glNormal3f(r * cos(a)/180,1.0,r*sin(a)/180);
                    glTexCoord2f(u,1.0);

                    glVertex3f(r * cos(a)/180, h, r*sin(a)/180);

                    u += 0.05;
                    a = 2*pi*u;
                }
            glEnd();
            a = 0;
            u = 0;
glPopMatrix();
textureManager->Disable();
    glEnable(GL_CULL_FACE);


}

void Cube::drawCone(float positionX,float positionY)
{
    glDisable(GL_CULL_FACE);

 textureManager->Bind(8);
    glPushMatrix();
    glTranslatef(positionX-3,positionY-3,5.5);
    glRotatef(-90,1.0,0.0,0.0);
    glScalef(size*0.8,size*0.8,size*0.8);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.0,1.0, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f( 1.0,0.0, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, -1.0, 0.0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0,0.0,0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5,0.5,1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0,0.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(1.0,0.5,0.0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0,0.0,0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5,0.5,1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0,1.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.5,1.0,0.0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0,1.0,0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5,0.5,1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.0,1.0,0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(-1.0,0.5,0.0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0,1.0,0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5,0.5,1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.0,0.0,0.0);
    glEnd();
    glPopMatrix();
    textureManager->Disable();
    glEnable(GL_CULL_FACE);

}

int Cube::getType()
{
    return type;
}

void Cube::randomObject()
{
    int aleatorio = 1 + rand()%5;
    switch(aleatorio)
    {
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

void Cube::setType(int t)
{
    type = t;
}

Cube::~Cube()
{

}
