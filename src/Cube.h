#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED


class Cube{
    private:
        int size;
        float* color;
    public:
        Cube();
        ~Cube();
        void drawCube(float positionX,float positionY);
        float* getColor();
        void setColor(float* color);
        float* randomColor();
};


#endif // CUBE_H_INCLUDED
