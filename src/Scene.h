#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "glm.h"

class Scene{
    private:
        GLMmodel* pmodel;
        void drawTable();
        void drawTeapot();
        void drawTorus();
        void drawFlower();
    public:
        Scene();
        ~Scene();
        void drawScene();
};

#endif // SCENE_H_INCLUDED
