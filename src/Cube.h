#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED


class Cube{
    private:
        int size;///tamanho do bloco
        float* color;///vetor que determina cor do bloco
    public:
        Cube();
        ~Cube();
        void drawCube(float positionX,float positionY);///desenha o cubo e translada para posição x e y
        float* getColor();///retorna o vetor de cores
        void setColor(float* color);///seta o vetor de cores
        float* randomColor();///gera cor aleatoria pro cubo
};


#endif // CUBE_H_INCLUDED
