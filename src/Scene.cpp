#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene::Scene(){
    pmodel = NULL;
}

///Para teste..area da cena
void Scene::drawScene(){
    this->drawTable();
    this->drawTeapot();
    this->drawTorus();
    this->drawFlower();
}

void Scene::drawTable(){
    ///Desenha mesa simples
    float x =0 , y= 0, z =0;
    glColor3f(0.7, 0.3, 0.3);
    glRotatef(45,0.0,1.0,0.0);
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

void Scene::drawFlower(){
    char objectName[100] = {"/home/joraojr/Documentos/CG-2017.1/data/objFiles/plate-and-ustensils.obj"};

    glColor3f(0.0,1.0,0.0);
    if (!pmodel) {
		pmodel = glmReadOBJ(objectName);
		if (!pmodel) exit(0);
		glmUnitize(pmodel);
		glmFacetNormals(pmodel);
		glmVertexNormals(pmodel, 90.0);
		glmScale(pmodel, 1);
	}
	glTranslatef(-1.2,1.2,2.0);
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}

Scene::~Scene(){

}
