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
}
void Scene::drawTable(){
    ///Desenha mesa simples
    float x =0 , y= 0, z =0;
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
Scene::~Scene()
{

}
