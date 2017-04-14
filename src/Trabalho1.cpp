#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Piece.h"
#include "Game.h"

using namespace std;
float moveX = 0.0,moveY = 0.0;
float yMin=-84.0;
float linha=3, coluna=0;
int time = 500.0;
bool shift = false;
Piece *p = new Piece();
Game *game = new Game();



void drawField()
{
    glColor3f(0.0,0.0,0.3);
    game->drawField();

}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT);

    drawField();

    if(shift)
    {
        p->shiftColor();
        shift = false;
    }

    p->drawPiece(moveX,moveY);

    glutSwapBuffers();
}

void timer(int value)
{
    if(moveY > yMin)
    {
        moveY -= 3.5;
        coluna +=0.5;
    }
    else
    {
        moveX=0.0;
        moveY=0.0;
    }
    glutPostRedisplay();
    glutTimerFunc(time,timer,1);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}
void specialKeysRelease(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        time = 500.0;
        break;

    default:
        cout << "Tecla sem função" << endl;
        break;
    }
}
void specialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if(moveX > -21.0 && moveY > yMin)
        {
            moveX -= 7;
            coluna -=1;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(moveX < 21 && moveY > yMin)
        {
            moveX += 7;
            coluna +=1;

        }
        break;
    case GLUT_KEY_DOWN:
        time = 100;
        break;

    case GLUT_KEY_UP:
        shift = true;
        break;

    default:
        cout << "Tecla sem função" << endl;
        break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
    case 3:
        shift = true;
        break;
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN)
            time = 100;
        else
            time = 500;
        break;

    }
}

void controlCallback(int control) {}

void init()
{

    glClearColor(0.0,0.0,0.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,105.0,-1.0,105.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main (int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860,680);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TetrisCrush");
    init();

    glutKeyboardFunc(keyboard);
//    glutKeyboardUpFunc( keyboardRelease );
    glutSpecialFunc(specialKey);
    glutSpecialUpFunc( specialKeysRelease );
    glutMouseFunc(mouse);

    glutTimerFunc(time,timer,1);
    glutDisplayFunc(display);

    glutMainLoop();
}
