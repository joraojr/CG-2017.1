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
#include <iostream>
#define DISABLE_ID 1234
#define ENABLE_ID 4321
#define CLEAN_ID 1111
#define COLOR_LISTBOX 7895
#define TYPE_ID 123

using namespace std;
int listbox_item_id = 6;
float color [3] = {1.0,1.0,1.0} ;


float theta = 0, minorR = 3, bigR = 5, d = 5, x, y, speed = 0.005;
int type = 0; /// 0 - Epitrochoid 1 - Hypotrochoid
int idleOn = 0, main_window,cleanScreen = 0;

GLUI *glui;
GLUI_Panel *obj_panel;
GLUI_RadioGroup *radio;

void idle(void)
{
    if(idleOn)
    {
        color[0] = 0.0;
        if(type == 0)
        {
            x = (bigR + minorR)*cos(theta) - d*cos(((bigR + minorR)/minorR)*theta);
            y = (bigR + minorR)*sin(theta) - d*sin(((bigR + minorR)/minorR)*theta);
        }
        else if(type == 1)
        {
            x = (bigR - minorR)*cos(theta) + d*cos(((bigR - minorR)/minorR)*theta);
            y = (bigR - minorR)*sin(theta) - d*sin(((bigR - minorR)/minorR)*theta);
        }

        theta += speed;

        if(theta > 360)
            theta = 0;
    }

    if (glutGetWindow() != main_window)
        glutSetWindow(main_window);

    if(cleanScreen == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        cleanScreen = 0;
    }


    glutPostRedisplay();
}

void display()
{
    glViewport ((int) 0, (int) 0, (int) 680, (int) 680);
    glColor3fv(color);
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
    default:
        printf("Erro");
    }
}

void setColorToWhite(){
    color[0] = 1.0;
    color[1] = 1.0;
    color[2] = 1.0;
}

void init()
{
    glPointSize(2.0);

    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30.0,30.0,-30.0,30.0,-1.0,1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
}

void control_callback(int control)
{
    switch(control)
    {
        case DISABLE_ID :
            idleOn = 1;
            obj_panel->disable();
            break;
        case ENABLE_ID:
            setColorToWhite();
            idleOn = 0;
            obj_panel->enable();
            break;
        case CLEAN_ID:
            setColorToWhite();
            cleanScreen = 1;
            break;
        case COLOR_LISTBOX:
            switch (listbox_item_id)
            {
            case 1:
                color[0] = 0.0;
                color[1] = 0.0;
                color[2] = 0.0;
                break;
            case 2:
                color[0] = 0.0;
                color[1] = 0.0;
                color[2] = 255.0;
                break;
            case 3:
                color[0] = 255.0;
                color[1] = 0.0;
                color[2] = 0.0;
                break;
            case 4:
                color[0] = 255.0;
                color[1] = 255.0;
                color[2] = 255.0;
                break;
            case 5:
                color[0] = 0.0;
                color[1] = 255.0;
                color[2] = 0.0;
                break;
            case 6:
                color[0] = 255.0;
                color[1] = 255.0;
                color[2] = 255.0;
                break;
            default:
                break;
            }
            break;
        case TYPE_ID:
            if(radio->get_int_val() == 0){
                type = 0;
            }else if(radio->get_int_val() == 1){
                type = 1;
            }
            break;
        default:
            break;
    }

}


int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(860,680);
    main_window = glutCreateWindow("Espirógrafo");
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    ///GLUI code
    glui = GLUI_Master.create_glui_subwindow( main_window,GLUI_SUBWINDOW_RIGHT );
    obj_panel = new GLUI_Rollout(glui, "Parametros", true );

    /// Selecionar tipo de Espirógrafo
    radio = new GLUI_RadioGroup(obj_panel,&type,TYPE_ID,control_callback);
    new GLUI_RadioButton(radio,"Epitrochoid");
    new GLUI_RadioButton(radio,"Hypotrochoid");

    ///Raio da esfera maior
    GLUI_Spinner *spinnerBigR = new GLUI_Spinner( obj_panel, "R:", &bigR);

    spinnerBigR->set_float_limits(0.0,40.0);
    ///Raio da esfera menor
    GLUI_Spinner *spinnerMinorR = new GLUI_Spinner( obj_panel, "r:", &minorR);

    spinnerMinorR->set_float_limits(0.0,40.0);
    ///Distancia do centro da esfera menor até o ponto de desenho
    GLUI_Spinner *spinnerD = new GLUI_Spinner( obj_panel, "d:", &d);
    spinnerD->set_float_limits(0.0,40.0);
    spinnerBigR->set_float_limits(0.0,40.0);
    /*
    ///Cores

/// Cria o listbox de cores dentro do painel
    GLUI_Listbox *color_listbox = glui->add_listbox_to_panel (obj_panel, "Color", &listbox_item_id, COLOR_LISTBOX, control_callback);

///  Adiciona itens no listbox
    color_listbox->add_item (1, "Preto");
    color_listbox->add_item (2, "Azul");
    color_listbox->add_item (3, "Vermelho");
    color_listbox->add_item (4, "Amarelo");
    color_listbox->add_item (5, "Verde");
    color_listbox->add_item (6, "Branco");
    */

    new GLUI_Button(obj_panel, "Desenhar", DISABLE_ID, control_callback );

    new GLUI_Button(glui, "Parar desenho", ENABLE_ID, control_callback );
    new GLUI_Button(glui, "Limpar desenho", CLEAN_ID, control_callback );




    GLUI_Master.set_glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

