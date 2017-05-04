#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene::Scene(){

}

///Para teste..area da cena
void Scene::drawScene(){
    glBegin(GL_POLYGON);
        glVertex3f(2.0, 2.0, 0.0);
        glVertex3f(8.0, 2.0, 0.0);
        glVertex3f(2.0, 8.0, 0.0);
    glEnd();
}

Scene::~Scene(){

}
