#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Piece.h"
#include "Game.h"
#include <time.h>

using namespace std;

void *font = GLUT_BITMAP_TIMES_ROMAN_24;
float moveX = 0.0,moveY = 0.0;
float yMin = -105.0;
float linha = 15, coluna = 3;
bool timeOn = true;
int animationTime = 500.0;
int typeShift = 0;
bool shift = false,shiftMouse = false;
Game* game = new Game();
Piece* p;
Piece* nextPiece;

void timer (int value);
void displayGame();

void drawState()
{
    switch (game->getGameState())
    {
    case 0:
        game->drawStartScreen();
        break;
    case 1:
        displayGame();

        if(timeOn)
        {
            glutTimerFunc(animationTime,timer,1);
            timeOn = false;
        }

        break;
    case 2:
        game->displayRanking();
        break;

    case 3:
        game->displayGameOver();
        break;
    }

}

void displayGame()
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,60.0,-1.0,105.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 0, (int) 0, (int) 480, (int) 680);

    game->drawField();
    p->drawPiece(moveX,moveY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(20.0,55.0,20,60.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport ((int) 680, (int) 480, (int) 180, (int) 200);

    game->drawPoints();///ajustar essa função

    nextPiece->drawPiece(0,-80);

    if(shift)
    {
        if(typeShift == 0)
            p->shiftColor();
        else
            p->shiftColorMouse();
        shift = false;
    }
}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    drawState();

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}

void timer(int value)
{
    if (!game->isGameOver())
    {
        if(game->getColor(linha - 1,coluna) == 0 && moveY > yMin)///mudar esse if para verificar se há cor na paraada toda
        {
            moveY -= 3.5;
            linha -=0.5;

        }
        else
        {
            int* cubeColors = p->getCubesColor();
            game->addColor(linha,coluna,cubeColors[2]);
            game->addColor(linha + 1,coluna,cubeColors[1]);
            game->addColor(linha + 2,coluna,cubeColors[0]);
            game->runVerification();
            moveX = 0.0;
            moveY = 0.0;
            linha = 15, coluna = 3;
            p = nextPiece;
            nextPiece = new Piece();
        }

        glutPostRedisplay();
        glutTimerFunc(animationTime,timer,1);
    }

    else
    {
        game->setGameState(3);
    }
}





void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        game->setGameState(0);
        game = new Game();
        moveX = 0.0;
        moveY = 0.0;
        linha = 15, coluna = 3;
        timeOn = true;
        break;

    case 'a' ... 'z':
    case 'A' ... 'Z':
        if (game->getGameState() == 3)
            addChar(key);
        break;
        glutPostRedisplay();
    }
}

void specialKeysRelease(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        animationTime = 500.0;
        break;

    default:
        //cout << "Tecla sem função" << endl;
        break;
    }
}
void specialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if(moveX > -21.0 && moveY > yMin && game->verifyMoveLeft(linha,coluna))
        {
            moveX -= 7;
            coluna -= 1;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(moveX < 21 && moveY > yMin && game->verifyMoveRight(linha,coluna))
        {
            moveX += 7;
            coluna += 1;

        }
        break;
    case GLUT_KEY_DOWN:
        animationTime = 100;
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
        typeShift = 0;
        break;
    case 4:
        shift = true;
        typeShift = 1;
        break;
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN && game->getGameState() == 0)
        {
            if (x > 358 && x < 502)
            {
                if (y > 133 && y < 215)
                {
                    game->setGameState(1);
                }
                if (y < 293 && y > 220)
                {
                    game->setGameState(2);
                }
                if (y < 379 && y> 303)
                    exit(1);
            }

        }
        else if (state==GLUT_DOWN && game->getGameState() == 1)
            animationTime = 100;
        else if (state==GLUT_UP &&game->getGameState() == 1)
            animationTime = 500;
        break;
    }
}

void controlCallback(int control) {}

int main (int argc,char *argv[])
{
    srand((unsigned)time(NULL));
    p = new Piece();
    nextPiece = new Piece();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860,680);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TetrisCrush");

    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutSpecialUpFunc( specialKeysRelease );
    glutMouseFunc(mouse);

    glutDisplayFunc(display);

    glutMainLoop();
}
