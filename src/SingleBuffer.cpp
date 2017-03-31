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
#include <GL/glui.h>
#include <math.h>

float theta = 0, minorR = 3, bigR = 5, d = 5, x, y, speed = 0.005;
int type = 3; /// 1 - Epitrochoid 2 - Hypotrochoid
int idleOn = 0, main_window;

GLUI *glui;
GLUI_Panel *obj_panel;

void idle(void){
    if(idleOn){
        if(type == 1){
            x = (bigR + minorR)*cos(theta) - d*cos(((bigR + minorR)/minorR)*theta);
            y = (bigR + minorR)*sin(theta) - d*sin(((bigR + minorR)/minorR)*theta);
        }else if(type == 2){
            x = (bigR - minorR)*cos(theta) + d*cos(((bigR - minorR)/minorR)*theta);
            y = (bigR - minorR)*sin(theta) - d*sin(((bigR - minorR)/minorR)*theta);
        }

        theta += speed;
    }

    if ( glutGetWindow() != main_window )
        glutSetWindow(main_window);
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
        idleOn = 1;
        break;
    case '2':
        type = 2;
        idleOn = 1;
        break;
    case '3':
        type =3;
        idleOn = 0;
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
    glutInitWindowSize(680,680);
    main_window = glutCreateWindow("Espirógrafo");
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    ///GLUI code
    glui = GLUI_Master.create_glui_subwindow( main_window,GLUI_SUBWINDOW_RIGHT );
    obj_panel = new GLUI_Rollout(glui, "Parametros", true );
    ///Raio da esfera maior
    GLUI_Spinner *spinnerBigR = new GLUI_Spinner( obj_panel, "R:", &bigR);
    spinnerBigR->set_alignment( GLUI_ALIGN_CENTER );
    spinnerBigR->set_float_limits(0.0,40.0);
    ///Raio da esfera menor
    GLUI_Spinner *spinnerMinorR = new GLUI_Spinner( obj_panel, "r:", &minorR);
    spinnerMinorR->set_alignment( GLUI_ALIGN_CENTER );
    spinnerMinorR->set_float_limits(0.0,40.0);
    ///Distancia do centro da esfera menor até o ponto de desenho
    GLUI_Spinner *spinnerD = new GLUI_Spinner( obj_panel, "d:", &d);
    spinnerD->set_alignment( GLUI_ALIGN_CENTER );
    spinnerD->set_float_limits(0.0,40.0);

    GLUI_Master.set_glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

