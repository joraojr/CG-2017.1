#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene::Scene()
{
    for(int i = 0; i < 11; i ++)
    {
        pmodel[i] = NULL;
    }
}

///Para teste..area da cena
void Scene::drawScene()
{
    this->drawTable();
    this->drawTeapot();
    this->drawTorus();
    this->drawChairs();
    this->drawFlower();
    this->drawPlates();

}

void Scene::drawTable()
{
    char objectName[100] = {"/home/joraojr/Documentos/CG-2017.1/data/objFiles/table.obj"};

    glColor3f(0.0,1.0,0.0);
    if (!pmodel[0])
    {
        pmodel[0] = glmReadOBJ(objectName);
        if (!pmodel[0]) exit(0);
        glmUnitize(pmodel[0]);
        glmFacetNormals(pmodel[0]);
        glmVertexNormals(pmodel[0], 90.0);
        glmScale(pmodel[0], 2);
    }
    glmDraw(pmodel[0], GLM_SMOOTH | GLM_MATERIAL);
}
void Scene::drawFlower()
{
    char objectName[100] = {"/home/joraojr/Documentos/CG-2017.1/data/objFiles/flowers.obj"};
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(0,2,0);
    if (!pmodel[1])
    {
        pmodel[1] = glmReadOBJ(objectName);
        if (!pmodel[1]) exit(0);
        glmUnitize(pmodel[1]);
        glmFacetNormals(pmodel[1]);
        glmVertexNormals(pmodel[1], 90.0);
        glmScale(pmodel[1], 1);
    }
    glmDraw(pmodel[1], GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void Scene::drawChairs()
{
    char objectName[100] = {"/home/joraojr/Documentos/CG-2017.1/data/objFiles/chair.obj"};


    for(int i = 0 ; i < 4; i ++)
    {
        glPushMatrix();
        if(i%2 == 0)
            glTranslatef(-1 +i ,0.6,-1);
        else
        {
            glRotatef(180,0,1,0);
            if(i == 1)
                glTranslatef(-1,0.6,-1);
            else
                glTranslatef(1,0.6,-1);
        }
        glColor3f(0.0,0.0,1.0);
        if (!pmodel[2+i])
        {
            pmodel[2+i] = glmReadOBJ(objectName);
            if (!pmodel[2+i]) exit(0);
            glmUnitize(pmodel[2+i]);
            glmFacetNormals(pmodel[2+i]);
            glmVertexNormals(pmodel[2+i], 90.0);
            glmScale(pmodel[2+i], 1.7);
        }
        glmDraw(pmodel[2+i], GLM_SMOOTH | GLM_MATERIAL);
        glPopMatrix();
    }
//	}

}

void Scene::drawPlates()
{
    char objectName[100] = {"/home/joraojr/Documentos/CG-2017.1/data/objFiles/plate-and-ustensils.obj"};


    for(int i = 0 ; i < 4; i ++)
    {
        glPushMatrix();
        if(i%2 == 0)
        {
            glRotatef(180,0,1,0);
            glTranslatef(-1 +i ,1.3,1);
        }
        else
        {
            if(i == 1)
                glTranslatef(-1,1.3,1);
            else
                glTranslatef(1,1.3,1);
        }
        glColor3f(1.0,1.0,1.0);
        if (!pmodel[6+i])
        {
            pmodel[6+i] = glmReadOBJ(objectName);
            if (!pmodel[6+i]) exit(0);
            glmUnitize(pmodel[6+i]);
            glmFacetNormals(pmodel[6+i]);
            glmVertexNormals(pmodel[6+i], 90.0);
            glmScale(pmodel[6+i], 0.5);
        }
        glmDraw(pmodel[6+i], GLM_SMOOTH | GLM_MATERIAL);
        glPopMatrix();
    }

}
void Scene::drawTeapot()
{
    glColor3f(0.0, 0.3, 0.3);
    glPushMatrix();
    glTranslatef(0.0,0.45,0.0);
    glRotatef(20,0.0,1.0,0.0);
    glutSolidTeapot(0.3);
    glPopMatrix();
}

void Scene::drawTorus()
{
    glColor3f(0.5, 0.0, 0.3);
    glPushMatrix();
    glTranslatef(-0.5,1,1.0);
    glRotatef(90,1.0,0.0,0.0);
    glutSolidTorus(0.1,0.3,100,100);
    glPopMatrix();
}



Scene::~Scene()
{

}
