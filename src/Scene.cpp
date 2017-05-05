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
    float x =0 , y= 0, z =0;
///Fazer função para utilizar como assento da mesa
    //tampod da mesa
    glPushMatrix();
    glTranslatef(x+0.5,y+3,z);
    glScalef(2,7,0.5);
    glutSolidCube(1);
    glPopMatrix();

    //Pes da mesa
    glPushMatrix();
        glPushMatrix();
            glPushMatrix();
                glTranslatef(x,y,z);
                glRotatef(90,0,1,1);
                glScalef (2.0, 0.5, 0.5);
                glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(x+1,y,z);
                glRotatef(90,0,1,1);
                glScalef (2.0, 0.5, 0.5);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
        glTranslated(x,y+5,z);
        glPushMatrix();
            glPushMatrix();
                glTranslatef(x+1,y,z);
                glRotatef(90,0,1,1);
                glScalef (2.0, 0.5, 0.5);
                glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(x,y,z);
                glRotatef(90,0,1,1);
                glScalef (2.0, 0.5, 0.5);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

Scene::~Scene()
{

}
