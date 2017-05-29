#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED
#include "glm.h"

class Cube{
    private:
        int size;///tamanho do bloco
        int type;
        void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,GLfloat *brilho);
    public:
        Cube();
        ~Cube();
        void drawCube(float positionX,float positionY);///desenha o cubo e translada para posição x e y
        void drawSphere(float positionX,float positionY);
        void drawTorus(float positionX,float positionY);
        void drawCone(float positionX,float positionY);
        void drawTeapot(float positionX,float positionY);
        void drawObject(int t,float positionX,float positionY);
        int getType();
        void setType(int t);
        void randomObject();
};


#endif // CUBE_H_INCLUDED
