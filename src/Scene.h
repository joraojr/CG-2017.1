#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "glm.h"

class Scene{
    private:
        GLMmodel* pmodel[11];
        GLfloat* light0_position;
        void drawTable();
        void drawTeapot();
        void drawTorus();
        void drawFlower();
        void drawChairs();
        void drawPlates();
        void drawRose();
        void drawFloor();
        void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,GLfloat *brilho);
        void drawTable2();
    public:
        Scene();
        ~Scene();
        void drawScene();
        void setLightPosition(float x,float y,float z);
        float getLightPosition(int i);

};

#endif // SCENE_H_INCLUDED
