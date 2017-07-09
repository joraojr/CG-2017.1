#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED
#include "Cube.h"
#include "glcTexture.h"

lass Piece{
    private:
        Cube* c[3];///vetor de cubos para gerar a peça com 3 cores
    public:
        Piece(glcTexture *texture);
        ~Piece();
        void drawPiece(float moveX,float moveY); ///desenha peça na posição x e y
        void shiftColor();///função para trocar a ordem de cor do bloco
        void shiftColorMouse();///função para mouse para funcionar a troca de cor para baixo
        int * getCubesColor();///retorna um vetor com valor setado para as cores do bloco
};

#endif // PIECE_H_INCLUDED
