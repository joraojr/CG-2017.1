/*
  Name:        SingleBuffer.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 23/03/2017
  Release:     23/03/2017
  Description: Use single buffer without clearing window
*/

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float var=0.0;
float step = 0.0001;
float theta = 0, minorR = 3, bigR = 5, d = 5, x, y, speed = 0.005;
int type = 3; /// 1 - Epitrochoid 2 - Hypotrochoid

void idle(void)
{
    if(type == 1)
    {
        x = (bigR + minorR)*cos(theta) - d*cos(((bigR + minorR)/minorR)*theta);
        y = (bigR + minorR)*sin(theta) - d*sin(((bigR + minorR)/minorR)*theta);
    }
    else if(type == 2)
    {
        x = (bigR - minorR)*cos(theta) + d*cos(((bigR - minorR)/minorR)*theta);
        y = (bigR - minorR)*sin(theta) - d*sin(((bigR - minorR)/minorR)*theta);
    }

    theta += speed;

    glutPostRedisplay();
}

void display()
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    glFinish();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case '1':
        type = 1;
        break;
    case '2':
        type =2;
        break;
    case '3':
        type =3;
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    }
}

void init()
{
    glPointSize(2.0);

    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-20.0,20.0,-1.0,1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Single Buffer - Not clearing Buffer (ESC to Exit)");
    init();
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

