#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>

using namespace std;

void display(){
    glClear (GL_COLOR_BUFFER_BIT);


    glPushMatrix();
        glTranslatef(0.0,50.0,0.0);
        glColor3f(1.0,0.0,0.0);
        glutSolidCube(5);
    glPopMatrix();

    glutSwapBuffers ();
}

void idle(){}

void keyboard(){}

void mouse(){}

void controlCallback(int control){}

void init(){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,50.0,0.0,50.0,1.0,50.0);

    glClearColor(1.0,1.0,1.0,0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main (int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(860,680);
    glutCreateWindow("Quadrado");
    init();

    glutDisplayFunc(display);

    glutMainLoop();
}
