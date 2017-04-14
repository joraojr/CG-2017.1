#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Piece.h"

using namespace std;
float moveX = 0.0,moveY = 0.0;
int time = 500.0;
bool shift = false;
Piece *p = new Piece();


void drawField(){
    glColor3f(0.0,0.0,0.3);

    float x = 0.0;
    float y = 0.0;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 7; j++){
            glBegin(GL_LINE_LOOP);
                glVertex3f(x,y,0.0);
                glVertex3f(x + 7.0,y,0.0);
                glVertex3f(x + 7.0,y + 7.0,0.0);
                glVertex3f(x,y + 7.0,0.0);
            glEnd();
            x += 7.0;
        }
        y += 7.0;
        x = 0.0;
    }
}

void display(){
    glClear (GL_COLOR_BUFFER_BIT);

    drawField();

    if(shift){
        p->shiftColor();
        shift = false;
    }
    p->drawPiece(moveX,moveY);

    glutSwapBuffers();
}

void timer(int value){
    if(moveY > -84.0)
        moveY -= 3.5;
    glutPostRedisplay();
    glutTimerFunc(time,timer,1);
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 27:
            exit(0);
        break;
    }
    glutPostRedisplay();
}

void specialKey(int key, int x, int y){
    switch (key){
        case GLUT_KEY_LEFT:
            if(moveX > -21.0 && moveY > -84)
                moveX -= 7;
        break;
        case GLUT_KEY_RIGHT:
            if(moveX < 21 && moveY > -84)
                moveX += 7;
        break;
        case GLUT_KEY_DOWN:
            time = 100;
        break;

        case GLUT_KEY_UP:
            shift = true;
            time = 500;///Apenas para teste
        break;

        default:
            cout << "Tecla sem função" << endl;
        break;
    }
    glutPostRedisplay();
}

void mouse(){}

void controlCallback(int control){}

void init(){

    glClearColor(0.0,0.0,0.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,105.0,-1.0,105.0,0.0,10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main (int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860,680);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TetrisCrush");
    init();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutTimerFunc(time,timer,1);
    glutDisplayFunc(display);

    glutMainLoop();
}
