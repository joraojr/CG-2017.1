#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene* s = new Scene();

void viewPortPerspective(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1.0, 9.0, -1.0, 9.0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 300, (int) 400, (int) 300);

    ///Para teste..area da cena
    glColor3f(1.0, 1.0, 0.0);
    s->drawScene();
}

void viewPortX(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1.0, 9.0, -1.0, 9.0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 400, (int) 300, (int) 400, (int) 300);


    glColor3f(1.0, 0.0, 0.0);
    s->drawScene();
}

void viewPortY(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1.0, 9.0, -1.0, 9.0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) 400, (int) 300);

    ///Para teste..area da cena
    glColor3f(0.0, 1.0, 0.0);
    s->drawScene();
}

void viewPortZ(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1.0, 9.0, -1.0, 9.0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 400, (int) 0, (int) 400, (int) 300);

    ///Para teste..area da cena
    glColor3f(0.0, 0.0, 1.0);
    s->drawScene();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewPortPerspective();
    viewPortX();
    viewPortY();
    viewPortZ();

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Projeções");
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
