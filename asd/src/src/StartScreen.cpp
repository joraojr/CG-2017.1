#include "StartScreen.h"
#include <GL/glut.h>

void drawStartScreen(){
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(0.0, 300.0, -200.0, 50.0, -1.0, 1.0);
   //gluPerspective(1,2,50,500);
    glColor3f(0.2549,0.4117,1);

    glBegin(GL_QUADS);
          glVertex3f (125, 0, 0.0);
          glVertex3f (125, -30, 0.0);
          glVertex3f (175, -30, 0.0);
          glVertex3f (175, 0, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
          glVertex3f (125, 0, 0.0);
          glVertex3f (125, -30, 0.0);
          glVertex3f (175, -30, 0.0);
          glVertex3f (175, 0, 0.0);
    glEnd();

    int posX = 137;

    char start[] = "START";

    for (int i = 0; i < 5; i++){
        glRasterPos3f (posX + i*5,-20, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
    }

     glColor3f(0.2549,0.4117,1);


    glBegin(GL_QUADS);
          glVertex3f (125, -60, 0.0);
          glVertex3f (125, -30, 0.0);
          glVertex3f (175, -30, 0.0);
          glVertex3f (175, -60, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
          glVertex3f (125, -60, 0.0);
          glVertex3f (125, -30, 0.0);
          glVertex3f (175, -30, 0.0);
          glVertex3f (175, -60, 0.0);
    glEnd();

    posX = 130;

    char ranking[] = "RANKING";

    for (int i = 0; i < 7; i++){
        glRasterPos3f (posX + i*6,-50, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ranking[i]);
    }

      glColor3f(0.2549,0.4117,1);


    glBegin(GL_QUADS);
          glVertex3f (125, -90, 0.0);
          glVertex3f (125, -60, 0.0);
          glVertex3f (175, -60, 0.0);
          glVertex3f (175, -90, 0.0);
    glEnd();


    glColor3f(1.0,1,1);
    glBegin(GL_LINE_LOOP);
          glVertex3f (125, -90, 0.0);
          glVertex3f (125, -60, 0.0);
          glVertex3f (175, -60, 0.0);
          glVertex3f (175, -90, 0.0);
    glEnd();

    posX = 137;

    char sair[] = "SAIR";

    for (int i = 0; i < 4; i++){
        glRasterPos3f (posX + i*6,-80, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, sair[i]);
    }

}
