#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene::Scene()
{

}

///Para teste..area da cena
void Scene::drawScene()
{
    this->drawTable();
    this->drawTeapot();
    this->drawTorus();
}

void Scene::drawTable(){
    ///Desenha mesa simples
    float x =0 , y= 0, z =0;
    glColor3f(0.7, 0.3, 0.3);
    glPushMatrix();
        glRotatef(-45,0,1,0);
        glRotatef(90,1,0,0);
        //tampod da mesa
        glPushMatrix();
            glTranslatef(x+0.5,y+2.5,z);
            glScalef(2,7,0.5);
            glutSolidCube(1);
        glPopMatrix();
        //Pes da mesa
        glPushMatrix();
            glPushMatrix();
                glPushMatrix();
                    glTranslatef(x,y,z+1);
                    glRotatef(90,0,1,0);
                    glScalef (2.0, 0.5, 0.5);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(x+1,y,z+1);
                    glRotatef(90,0,1,0);
                    glScalef (2.0, 0.5, 0.5);
                    glutSolidCube(1);
                glPopMatrix();
            glPopMatrix();
            glTranslated(x,y+5,z);
            glPushMatrix();
                glPushMatrix();
                    glTranslatef(x+1,y,z+1);
                    glRotatef(90,0,1,0);
                    glScalef (2.0, 0.5, 0.5);
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(x,y,z+1);
                    glRotatef(90,0,1,0);
                    glScalef (2.0, 0.5, 0.5);
                    glutSolidCube(1);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Scene::drawTeapot(){
    glColor3f(0.0, 0.3, 0.3);
    glPushMatrix();
        glTranslatef(0.0,0.45,0.0);
        glRotatef(20,0.0,1.0,0.0);
        glutSolidTeapot(0.3);
    glPopMatrix();
}

void Scene::drawTorus(){
    glColor3f(0.5, 0.0, 0.3);
    glPushMatrix();
        glTranslatef(-0.5,0.3,1.0);
        glRotatef(90,1.0,0.0,0.0);
        glutSolidTorus(0.1,0.3,100,100);
    glPopMatrix();
}

Scene::~Scene()
{

}
