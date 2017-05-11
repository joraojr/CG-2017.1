#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene::Scene(){
    for(int i = 0; i < 11; i++)
    {
        pmodel[i] = NULL;
    }
    light0_position[0] = 1.7f;
    light0_position[1] = 2.75f;
    light0_position[2] = 2.5f;
}

///Para teste..area da cena
void Scene::drawScene(){
    glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	glEnable(GL_LIGHTING);                 // Habilita luz
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

    GLfloat cor0[] = {1.0,1.0,1.0,1.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,cor0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR , cor0);

    ///Desenha a luz
    glPushMatrix();
		glLoadIdentity();
		glTranslatef(light0_position[0], light0_position[1], light0_position[2]);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		glColor3f(1.0, 1.0, 1.0);
		glutWireSphere(0.05, 10, 10);
	glPopMatrix();

    this->drawTable();
    this->drawTeapot();
    //this->drawTorus();
    this->drawChairs();
    this->drawFlower();
    this->drawPlates();
    //this->drawRose();
}

void Scene::drawTable()
{
    char objectName[100] = {"../data/objFiles/table.obj"};

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
void Scene::drawFlower(){
    char objectName[100] = {"../data/objFiles/flowers.obj"};
    glPushMatrix();
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

void Scene::drawRose(){

    char objectName[100] = {"../data/objFiles/rose+vase.obj"};
    glPushMatrix();
    glTranslatef(0,2,0);
    if (!pmodel[11])
    {
        pmodel[11] = glmReadOBJ(objectName);
        if (!pmodel[11]) exit(0);
        glmUnitize(pmodel[11]);
        glmFacetNormals(pmodel[11]);
        glmVertexNormals(pmodel[11], 90.0);
        glmScale(pmodel[11], 1);
    }
    glmDraw(pmodel[11], GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}

void Scene::drawChairs(){
    char objectName[100] = {"../data/objFiles/chair.obj"};

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
}

void Scene::drawPlates()
{
    char objectName[100] = {"../data/objFiles/plate-and-ustensils.obj"};


    for(int i = 0 ; i < 4; i ++)
    {
        glPushMatrix();
        if(i%2 == 0)
        {
            glRotatef(180,0,1,0);
            glTranslatef(-1 +i ,1.34,1);
        }
        else
        {
            if(i == 1)
                glTranslatef(-1,1.34,1);
            else
                glTranslatef(1,1.34,1);
        }
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

void Scene::setMaterial(GLfloat *ambient, GLfloat *diffuse, GLfloat *specular,
					  GLfloat *shininess){
   // Material do objeto (neste caso, ruby). Parametros em RGBA


   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void Scene::drawTeapot(){
    GLfloat objeto_ambient[]   = { .1745, .21175, .01175, 1.0 };
    GLfloat objeto_difusa[]    = { .61424, .84136, .04136, 1.0 };
    GLfloat objeto_especular[] = { .727811, .826959, .626959, 1.0 };
    GLfloat objeto_brilho[]    = { 90.0f };


    setMaterial(objeto_ambient,objeto_difusa,objeto_especular,objeto_brilho);
    glPushMatrix();
    glTranslatef(0.7,1.3,0.0);
    glRotatef(20,0.0,1.0,0.0);
    glutSolidTeapot(0.3);
    glPopMatrix();
}

void Scene::drawTorus()
{
    //glColor3f(0.5, 0.0, 0.3);
    glPushMatrix();
    glTranslatef(-0.5,1,1.0);
    glRotatef(90,1.0,0.0,0.0);
    glutSolidTorus(0.1,0.3,100,100);
    glPopMatrix();
}

void Scene::setLightPosition(float x,float y,float z){
    light0_position[0] = x;
    light0_position[1] = y;
    light0_position[2] = z;
}

float Scene::getLightPosition(int i){
    return light0_position[i];
}

Scene::~Scene()
{

}
