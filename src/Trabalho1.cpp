#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Piece.h"
#include "Game.h"
#include <time.h>

using namespace std;
///PLAYER 2
float yMin2 = -105.0;
float linha2 = 15;
int coluna2 = 3;
int animationTime2 = 500;
int animationAux2 = 500;
float moveX2 = 0.0, moveY2 = 0.0;
bool shift2 = false;

void *font = GLUT_BITMAP_TIMES_ROMAN_24;
float moveX = 0.0,moveY = 0.0,animationMove = 1.0;
float yMin = -105.0;
float linha = 15;
int coluna = 3;
int last_x,last_y;
float distOrigem = 60;
float rotationX = 0.0, rotationY = -30.0;
bool timeOn = true,fullScreen = false,shift = false,shiftMouse = false;
int animationTime = 500.0,animationAux = 500,fastSpeed = 10;
int typeShift = 0;
Game* game;
int height = 680,width = 860;

void timer (int value);
void timer2 (int value);
void displayGame();

void resetAll()
{
    game->resetGame();
    moveX = 0.0;
    moveY = 0.0;
    linha = 15;
    coluna = 3;
    animationTime = 500;
    animationAux = 500;

    linha2 = 15;
    coluna2 = 3;
    animationTime2 = 500;
    animationAux2 = 500;
    moveX2 = 0.0;
    moveY2 = 0.0;
}

void drawState()
{
    switch (game->getGameState())
    {
    case 0:
        resetAll();
        game->drawStartScreen(width,height);
        break;
    case 1:
        glutSetCursor(GLUT_CURSOR_NONE);
        game->displayGame(width,height,moveX,moveY,shift,typeShift,animationMove,rotationX,rotationY,distOrigem);
        timeOn = true;
        break;
    case 2:
        game->displayRanking(width,height);
        break;
    case 3:
        game->displayGameOver(width,height);
        resetAll();
        /*
        if(timeOn){
            timer(1);
            timer2(1);
            timeOn = false;
        }*/
        break;
    case 4:
        resetAll();
        game->drawStartScreenPlayerOption(width,height);
        break;
    case 5:
        glutSetCursor(GLUT_CURSOR_NONE);
        game->displayGame2Players(width,height,moveX,moveY,shift,typeShift,animationMove,moveX2,moveY2,shift2,distOrigem,rotationX,rotationY);
        timeOn = true;
        break;
    case 6:
        game->displayGameOver2Players(width,height);
        /*
        if(timeOn){
            timer(1);
            timer2(1);
            timeOn = false;
        }*/
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

void idle()
{
    if(game->getAnimationOn() == 1)
    {
        animationMove += 1.0;
    }
    else
    {

    }
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
}

void timer(int value)
{

    if (game->isGameOver(1) != 1 && game->isGameOver(2) != 2)
    {
        if(game->getColor(game->getField1(),linha - 1,coluna) == 0 && moveY > yMin)
        {
            if(!game->getPause())
            {
                moveY -= 3.5;
                linha -=0.5;
            }
        }
        else if(!game->getPause())
        {
            int* cubeColors = game->getPiece()->getCubesColor();
            game->addColor(game->getField1(),linha,coluna,cubeColors[2]);
            game->addColor(game->getField1(),linha + 1,coluna,cubeColors[1]);
            game->addColor(game->getField1(),linha + 2,coluna,cubeColors[0]);
            game->runVerification(game->getField1(),game->getTrashListAux(),game->getTrashListFinal(),1);
            animationTime = animationAux/game->getLevel();
            moveX = 0.0;
            moveY = 0.0;
            linha = 15, coluna = 3;
            game->setPiece(game->getNextPiece());
            game->createNextPiece();
            //glutTimerFunc(animationTime,timer,1);
        }

        glutPostRedisplay();

    }
    else
    {
        cout << game->getGameState() << endl;
        if(game->getGameState() == 1){
            game->setGameState(3);
        }else{
            ///tela de gameOver de 2 player
            game->setGameState(6);
        }
        glutPostRedisplay();
    }
    glutTimerFunc(animationTime,timer,1);
}


void timer2(int value){
    cout << game->getGameState() << endl;
    if(game->getGameState() == 5){
        if (game->isGameOver(2) != 2 && game->isGameOver(1) != 1){
            if(game->getColor(game->getField2(),linha2 - 1,coluna2) == 0 && moveY2 > yMin2){
                if(!game->getPause()){
                    moveY2 -= 3.5;
                    linha2 -=0.5;
                }
            }
            else if(!game->getPause())
            {
                int* cubeColors2 = game->getPiece2()->getCubesColor();

                game->addColor(game->getField2(),linha2,coluna2,cubeColors2[2]);
                game->addColor(game->getField2(),linha2 + 1,coluna2,cubeColors2[1]);
                game->addColor(game->getField2(),linha2 + 2,coluna2,cubeColors2[0]);

                game->runVerification(game->getField2(),game->getTrashListAux2(),game->getTrashListFinal2(),2);
                animationTime2 = animationAux/game->getLevel();
                moveX2 = 0.0;
                moveY2 = 0.0;
                linha2 = 15, coluna2 = 3;

                game->setPiece2(game->getNextPiece2());

                game->createNextPiece();
            }

            glutPostRedisplay();
            //glutTimerFunc(animationTime2,timer2,1);
        }
        else
        {
            if(game->getGameState() == 1){
                game->setGameState(3);
            }else{
                ///tela de gameOver de 2 player
                game->setGameState(6);
            }
            glutPostRedisplay();
        }
    }
    glutTimerFunc(animationTime2,timer2,1);
}

void reshape(int w,int h)
{
    height = h;
    width = w;
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case '1':
            printf("\n%d\n",game->getGameView());
            if((game->getGameState() == 1 || game->getGameState() == 5) && game->getPause()){
                if(game->getGameView() == 0){
                    game->setGameView(1);
                }else{
                    game->setGameView(0);
                }
            }
            break;
        case 27:
            game->setGameState(0);
            game->resetGame();
            timeOn = true;
            resetAll();
            glutPostRedisplay();
            break;
        case 'a' ... 'z':
        case 'A' ... 'Z':
            if((game->getGameState() == 1 || game->getGameState() == 5) && key == 'p'){
                game->setPause(!game->getPause());
            }else if(game->getGameState() == 5 && !game->getPause()){
                if (key == 'w'){
                    shift2 = true;
                }else if (key == 'd'){
                    if(moveX2 < 21 && moveY2 > yMin2 && game->verifyMoveRight(game->getField2(),linha2,coluna2)){
                        moveX2 += 7;
                        coluna2 += 1;
                    }
                }else if (key == 's'){
                    animationTime2 = fastSpeed;
                }else if (key == 'a'){
                    if(moveX2 > -21.0 && moveY2 > yMin2 && game->verifyMoveLeft(game->getField2(),linha2,coluna2)){
                        moveX2 -= 7;
                        coluna2 -= 1;
                    }
                }
            }else if (game->getGameState() == 3){
                game->getRanking()->addChar(key);
                glutPostRedisplay();
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

void keyboardKeysRelease(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        animationTime2 = animationAux2/game->getLevel();
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
        if(moveX > -21.0 && moveY > yMin && game->verifyMoveLeft(game->getField1(),linha,coluna) && !game->getPause())
        {
            moveX -= 7;
            coluna -= 1;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(moveX < 21 && moveY > yMin && game->verifyMoveRight(game->getField1(),linha,coluna) && !game->getPause())
        {
            moveX += 7;
            coluna += 1;

        }
        break;
    case GLUT_KEY_DOWN:
        animationTime = fastSpeed;
        break;

    case GLUT_KEY_UP:
        if(!game->getPause())
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
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN && game->getGameState() == 0)
        {
            if (x > width*0.41 && x < width*0.58)
            {
                if (y > height*0.19 && y < height*0.31)
                {
                    game->setGameState(4);
                }
                if (y < height*0.43 && y > height*0.32)
                {
                    game->setGameState(2);
                }
                if (y < height*0.55 && y> height*0.44)
                    exit(1);
            }
        }
        else if(state==GLUT_DOWN && game->getGameState() == 4)
        {
            if (x > width*0.41 && x < width*0.63)
            {
                if (y > height*0.19 && y < height*0.31)
                {
                    game->setGameState(1);
                }
                if (y < height*0.43 && y > height*0.32)
                {
                    game->setGameState(5);
                }
            }
        }
        else if (state==GLUT_DOWN && !game->getPause() && (game->getGameState() == 5 || game->getGameState() == 1))
            animationTime2 = fastSpeed;
        else if (state==GLUT_UP && !game->getPause() && (game->getGameState() == 5 || game->getGameState() == 1))
            animationTime2 = animationAux/game->getLevel();
        else if(game->getPause() && (game->getGameState() == 1))
        {
            if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
            {
                last_x = x;
                last_y = y;
            }
        }

        break;
    case 3:
        if(game->getPause())
        {
            distOrigem+=0.3;
            if(distOrigem>100) distOrigem=100;
        }
        else
        {
            shift = true;
            typeShift = 0;
        }
        break;
    case 4:
        if(game->getPause())
        {
            distOrigem-=0.3;
            if(distOrigem<0) distOrigem=0;
        }
        else
        {
            shift = true;
            typeShift = 1;
        }
        break;
    }

}

void motion(int x, int y )
{
    if(game->getPause())
    {
        rotationY += (float) (y - last_y);
        rotationX += (float) (x - last_x);

        last_x = x;
        last_y = y;
    }

    glutPostRedisplay();
}


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
    glutKeyboardUpFunc(keyboardKeysRelease);
    glutSpecialFunc(specialKey);
    glutSpecialUpFunc( specialKeysRelease );
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutTimerFunc(animationTime,timer,1);
    glutTimerFunc(animationTime2,timer2,1);

    glutMainLoop();
}
