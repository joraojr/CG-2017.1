#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

int   last_x, last_y;
float rotationX = 38.0, rotationY = 22.0;
Scene* s = new Scene();
float width = 800,height = 800,distOrigem = 0;

void viewPortPerspective(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 300, (int) 400, (int) 300);
    gluLookAt (0.0, 0.0, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    ///Para teste..area da cena
    glPushMatrix();
        glTranslatef(0.0,0.0,distOrigem);
        glRotatef( rotationY, 1.0, 0.0, 0.0 );
        glRotatef( rotationX, 0.0, 1.0, 0.0 );
        s->drawScene();
    glPopMatrix();

}

void viewPortX(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    int ortho = 10;
    float h = height;
    float w = width;
    glOrtho (-ortho, ortho, -ortho*h/w, ortho*h/w, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 400, (int) 300, (int) 400, (int) 300);

    glRotatef(-90,0.0,1.0,0.0);
    s->drawScene();
}

void viewPortY(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    int ortho = 10;
    float h = height;
    float w = width;
    glOrtho (-ortho, ortho, -ortho*h/w, ortho*h/w, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) 400, (int) 300);

    glRotatef(90,1.0,0.0,0.0);
    glRotatef(45,0.0,1.0,0.0);
    s->drawScene();
}

void viewPortZ(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    int ortho = 10;
    float h = height;
    float w = width;
    glOrtho (-ortho, ortho, -ortho*h/w, ortho*h/w, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 400, (int) 0, (int) 400, (int) 300);

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
void mouse(int button, int state, int x, int y){
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
      last_x = x;
      last_y = y;
   }
   if(button == 3){
      distOrigem+=0.3;
      if(distOrigem>180) distOrigem=180;
   }
   if(button == 4){
      distOrigem-=0.3;
      if(distOrigem<-20) distOrigem=-20;
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
