#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Scene.h"

Scene* s = new Scene();
int   last_x, last_y;
float rotationX = 38.0, rotationY = 22.0;
float width = 800,height = 600,distOrigem = 20;
float luzX = s->getLightPosition(0), luzY = s->getLightPosition(1), luzZ = s->getLightPosition(2);


void viewPortPerspective(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);
    gluLookAt (0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 301, (int) 399, (int) 299);

    glPushMatrix();
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
    gluLookAt (20.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 401, (int) 301, (int) 399, (int) 299);

    s->drawScene();
}

void viewPortY(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    int ortho = 10;
    float h = height;
    float w = width;
    glOrtho (-ortho, ortho, -ortho*h/w, ortho*h/w, -100.0, 100.0);
    gluLookAt (0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) 399, (int) 299);

    s->drawScene();
}

void viewPortZ(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    int ortho = 10;
    float h = height;
    float w = width;
    glOrtho (-ortho, ortho, -ortho*h/w, ortho*h/w, -100, 100.0);
    gluLookAt (0.0, 0.0, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 401, (int) 0, (int) 399, (int) 299);

    s->drawScene();
}

void drawPartition(){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho (-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 399, (int) 0, (int) 1, (int) 1200);

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(1,-1,0.0);
        glVertex3f(1,1,0.0);
        glVertex3f(-1,1,0.0);
        glVertex3f(-1,-1,0.0);
    glEnd();

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho (-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 299, (int) 800, (int) 1);

    glBegin(GL_POLYGON);
        glVertex3f(1,-1,0.0);
        glVertex3f(1,1,0.0);
        glVertex3f(-1,1,0.0);
        glVertex3f(-1,-1,0.0);
    glEnd();
}

void init(){
    glClearColor(0.7, 0.8, 0.0, 1.0);
}

void display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///desenha as divisórias
    glDisable(GL_LIGHTING);
    drawPartition();
    glEnable(GL_LIGHTING);

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

void special(int key, int x, int y){
	float step = 0.05f;
    switch (key){
        case GLUT_KEY_LEFT:
             luzX-=step;
        break;
        case GLUT_KEY_RIGHT:
             luzX+=step;
        break;
        case GLUT_KEY_UP:
             luzY+=step;
        break;
        case GLUT_KEY_DOWN:
             luzY-=step;
        break;
        case GLUT_KEY_PAGE_UP:
             luzZ+=step;
        break;
        case GLUT_KEY_PAGE_DOWN:
             luzZ-=step;
        break;
    }
   s->setLightPosition(luzX,luzY,luzZ);
   //printf("\nPosição da luz [x,y,z]: [%.2f, %.2f, %.2f]",light0_position[0], light0_position[1], light0_position[2]);
   glutPostRedisplay();
}


int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Projeções");

    init();
    glutMouseFunc( mouse );
    glutSpecialFunc(special);
    glutMotionFunc( motion );
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
