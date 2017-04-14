#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED
#include "Cube.h"

class Piece{
    private:
        Cube* c[3];
        int shiftCount;
    public:
        Piece();
        ~Piece();
        void drawPiece(float moveX,float moveY);
        void shiftColor();
        float ** getCubesColor();
}
;

#endif // PIECE_H_INCLUDED
