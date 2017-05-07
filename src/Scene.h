#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class Scene{
    private:
        void drawTable();
        void drawTeapot();
        void drawTorus();
    public:
        Scene();
        ~Scene();
        void drawScene();
};

#endif // SCENE_H_INCLUDED
