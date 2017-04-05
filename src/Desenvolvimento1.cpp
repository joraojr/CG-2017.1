/*
  Name:        Desenvolvimento1.cpp
  Copyright:   Version 0.1
  Author:      Jorão Gomes Junior e Lucas Rodrigues Frank
  Last Update: 05/04/2017
  Release:     05/04/2017
  Description: Desenvolvimento 1 da matéria de  Computação Gráfica 2017.01
*/

/*
  References :
    https://sites.google.com/site/computacaograficaufjf/arquivos
    https://en.wikipedia.org/wiki/Hypotrochoid
    https://en.wikipedia.org/wiki/Epitrochoid
    https://pt.wikipedia.org/wiki/RGB
    https://www.codeproject.com/Articles/20286/GLUI-Window-Template
    http://www-h.eng.cam.ac.uk/help/tpl/graphics/using_glui.html
    https://www.experts-exchange.com/questions/23246383/c-opengl-using-Glut.html

  GitHub:
    https://github.com/joraojr/CG-2017.1
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
int listbox_item_id = 0;
float color [3] = {1.0,1.0,1.0} ;
float colorAux [3] = {0.0,0.0,0.0};

float theta = 0, minorR = 3, bigR = 5, d = 5, x, y, speed = 0.005;
int type = 0; /// 0 - Epitrochoid 1 - Hypotrochoid
int idleOn = 0, main_window,cleanScreen = 0;
int position = 30.0;
int scale = 0;

GLUI *glui;
GLUI_Panel *obj_panel;
GLUI_Panel *obj_panel_color;
GLUI_RadioGroup *radio;
GLUI_RadioGroup *radio_colors;

void idle(void)
{
    ///Desenha Epitrochoid e Hypotrochoid
    if(idleOn)
    {

        color[0] = colorAux[0];
        color[1] = colorAux[1];
        color[2] = colorAux[2];
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
    ///Para conseguir alterar o ortho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-position - scale,position + scale,-position - scale,position + scale,-1.0,1.0);

    glViewport ((int) 0, (int) 0, (int) 680, (int) 680);
    glPointSize(3);
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

void setColorToWhite()
{
    color[0] = 1.0;
    color[1] = 1.0;
    color[2] = 1.0;
}

void init()
{
    glPointSize(2.0);

    glClearColor(1.0,1.0,1.0,0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
}

///Verificação do ID da requisição da callback para realização do procedimento desejado
void control_callback(int control)
{
    switch(control)
    {
    case DISABLE_ID :
        idleOn = 1;
        obj_panel->disable();
        break;
    case ENABLE_ID:
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
        case 0:
            colorAux[0] = 0.0;
            colorAux[1] = 0.0;
            colorAux[2] = 0.0;
            break;
        case 1:
            colorAux[0] = 0.0;
            colorAux[1] = 0.0;
            colorAux[2] = 255.0;
            break;
        case 2:
            colorAux[0] = 255.0;
            colorAux[1] = 0.0;
            colorAux[2] = 0.0;
            break;
        case 3:
            colorAux[0] = 255.0;
            colorAux[1] = 255.0;
            colorAux[2] = 0.0;
            break;
        case 4:
            colorAux[0] = 0.0;
            colorAux[1] = 255.0;
            colorAux[2] = 0.0;
            break;
        default:
            break;
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

    ///Criacação da interface GLUI
    glui = GLUI_Master.create_glui_subwindow( main_window,GLUI_SUBWINDOW_RIGHT );
    obj_panel = new GLUI_Rollout(glui, "Parametros", true );

    /// Selecionar tipo de Espirógrafo
    radio = new GLUI_RadioGroup(obj_panel,&type,TYPE_ID,control_callback);
    new GLUI_RadioButton(radio,"Epitrochoid");
    new GLUI_RadioButton(radio,"Hypotrochoid");

    ///Escala
    GLUI_Spinner *spinnerEscala = new GLUI_Spinner( obj_panel, "Escala:", &scale);
    spinnerEscala->set_float_limits(0,100);

    ///Raio da esfera maior
    GLUI_Spinner *spinnerBigR = new GLUI_Spinner( obj_panel, "R:", &bigR);

    spinnerBigR->set_float_limits(0.0,40.0);
    ///Raio da esfera menor
    GLUI_Spinner *spinnerMinorR = new GLUI_Spinner( obj_panel, "r:", &minorR);

    spinnerMinorR->set_float_limits(0.0,40.0);
    ///Distancia do centro da esfera menor até o ponto de desenho
    GLUI_Spinner *spinnerD = new GLUI_Spinner( obj_panel, "d:", &d);
    spinnerD->set_float_limits(0.0,40.0);

    ///Cores
    obj_panel_color = new GLUI_Rollout(glui, "Cores", true );

    radio_colors = new GLUI_RadioGroup( obj_panel_color,&listbox_item_id,COLOR_LISTBOX,control_callback);
    new GLUI_RadioButton( radio_colors, "Preto" );
    new GLUI_RadioButton( radio_colors, "Azul" );
    new GLUI_RadioButton( radio_colors, "Vermelho" );
    new GLUI_RadioButton( radio_colors, "Amarelo" );
    new GLUI_RadioButton( radio_colors, "Verde" );

    ///Desenhar-Parar desenho e Limpar
    new GLUI_Button(obj_panel, "Desenhar", DISABLE_ID, control_callback );

    new GLUI_Button(glui, "Parar desenho", ENABLE_ID, control_callback );
    new GLUI_Button(glui, "Limpar desenho", CLEAN_ID, control_callback );


    GLUI_Master.set_glutIdleFunc(idle);
    ///Loop
    glutMainLoop();
    return 0;
}

