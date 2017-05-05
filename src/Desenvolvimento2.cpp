#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

int   last_x, last_y;
float rotationX = 38.0, rotationY = 22.0;
Scene* s = new Scene();
float width = 800,height = 800;

void viewPortPerspective(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    int ortho = 10;
    float w = width;
    float h = height;
    glOrtho (-ortho, ortho, -ortho*h/w, ortho*h/w, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 300, (int) 400, (int) 300);
    //gluLookAt (0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    ///Para teste..area da cena
    glPushMatrix();
        glRotatef( rotationY, 1.0, 0.0, 0.0 );
        glRotatef( rotationX, 0.0, 1.0, 0.0 );
        glColor3f(1.0, 1.0, 0.0);
        s->drawScene();
    glPopMatrix();

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
    //viewPortX();
    //viewPortY();
    //viewPortZ();

    glutSwapBuffers();
    glutPostRedisplay();
}

// Motion callback
void motion(int x, int y )
{
   rotationY += (float) (y - last_y);
   rotationX += (float) (x - last_x);

   last_x = x;
   last_y = y;

   glutPostRedisplay();
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
   {
      last_x = x;
      last_y = y;
   }
}


int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Projeções");

    init();
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
