#include "Game.h"

Game::Game(){
    field = new int*[15];

    for(int i = 0; i < 15; i++){
        field[i] = new int[7];
    }
}
