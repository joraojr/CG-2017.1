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
float linha = 15;
int coluna = 3;
bool timeOn = true,fullScreen = false,shift = false,shiftMouse = false;
int animationTime = 500.0,animationAux = 500,fastSpeed = 10;
int typeShift = 0;
Game* game;
int height = 680,width = 860;

void timer (int value);
void displayGame();

void resetAll(){
    moveX = 0.0;
    moveY = 0.0;
    linha = 15;
    coluna = 3;
    animationTime = 500;
    animationAux = 500;
}

void drawState(){
    switch (game->getGameState()){
    case 0:
        resetAll();
        game->drawStartScreen(width,height);
        break;
    case 1:
        game->displayGame(width,height,moveX,moveY,shift,typeShift);

        if(timeOn){
            glutTimerFunc(animationTime,timer,1);
            timeOn = false;
        }

        break;
    case 2:
        game->displayRanking(width,height);
        break;
    case 3:
        game->displayGameOver(width,height);
        timeOn = true;
        break;
    case 4:
        resetAll();
        game->drawStartScreenPlayerOption(width,height);
        break;
    case 5:
        game->displayGame2Players(width,height,moveX,moveY,shift,typeShift);

          if(timeOn){
            glutTimerFunc(animationTime,timer,1);
            timeOn = false;
        }
        break;
    }

}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    drawState();

    glutSwapBuffers();
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}

void timer(int value)
{
    if (!game->isGameOver())
    {
        if(game->getColor(linha - 1,coluna) == 0 && moveY > yMin)
        {
            if(!game->getPause()){
                moveY -= 3.5;
                linha -=0.5;
            }
        }
        else if(!game->getPause())
        {

            int* cubeColors = game->getPiece()->getCubesColor();

            game->addColor(linha,coluna,cubeColors[2]);
            game->addColor(linha + 1,coluna,cubeColors[1]);
            game->addColor(linha + 2,coluna,cubeColors[0]);
            game->runVerification(game->field,game->trashListAux,game->trashListFinal);
            animationTime = animationAux/game->getLevel();
            moveX = 0.0;
            moveY = 0.0;
            linha = 15, coluna = 3;
            game->setPiece(game->getNextPiece());
            game->createNextPiece();
        }

        glutPostRedisplay();
        glutTimerFunc(animationTime,timer,1);
    }
    else
    {
        game->setGameState(3);
        glutPostRedisplay();
    }
}

void reshape(int w,int h){
    height = h;
    width = w;
    //cout << height << " " << width << endl;
}



void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        game->setGameState(0);
        game->resetGame();
        resetAll();
        glutPostRedisplay();
        break;
    case 'a' ... 'z':
    case 'A' ... 'Z':
        if (game->getGameState() == 3)
        {
            game->getRanking()->addChar(key);
            glutPostRedisplay();
        }else if(game->getGameState() == 1 && key == 'p'){
            game->setPause(!game->getPause());
        }
        break;
    case 13:
        if(game->getGameState() == 3)
        {
            game->getRanking()->addScore();
            game->setGameState(0);
            glutPostRedisplay();
        }
        break;
    case 32:
        if(!fullScreen)
        {
            glutFullScreen();
            fullScreen = true;
        }
        else
        {
            glutInitWindowPosition(0,0);
            glutReshapeWindow(860,680);
            fullScreen = false;
        }
        glutPostRedisplay();
        break;

    }
}

void specialKeysRelease(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        animationTime = animationAux/game->getLevel();
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
        animationTime = fastSpeed;
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
        if(state==GLUT_DOWN && game->getGameState() == 0){
            if (x > width*0.41 && x < width*0.58){
                if (y > height*0.19 && y < height*0.31){
                    game->setGameState(4);
                }
                if (y < height*0.43 && y > height*0.32){
                    game->setGameState(2);
                }
                if (y < height*0.55 && y> height*0.44)
                    exit(1);
            }
        }else if(state==GLUT_DOWN && game->getGameState() == 4){
            if (x > width*0.41 && x < width*0.63){
                if (y > height*0.19 && y < height*0.31){
                    game->setGameState(1);
                }
                if (y < height*0.43 && y > height*0.32){
                    game->setGameState(5);
                }
            }
        }
        else if (state==GLUT_DOWN && game->getGameState() == 1)
            animationTime = fastSpeed;
        else if (state==GLUT_UP && game->getGameState() == 1)
            animationTime = animationAux/game->getLevel();
        break;
}
}

void controlCallback(int control) {}

int main (int argc,char *argv[])
{
    srand((unsigned)time(NULL));
    game = new Game();
    game->getRanking()->readFromFile();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TetrisCrush");

    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutSpecialUpFunc( specialKeysRelease );
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();
}
