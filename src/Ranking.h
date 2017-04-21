#ifndef RANKING_H
#define RANKING_H

#include <fstream>
#include <string.h>
#include <stdio.h>
#include <GL/glut.h>

using namespace std;

typedef struct ranking
{
    int score;
    char name[21];

} Score;

class Ranking
{
public:
    Ranking();
    ~Ranking();
    void addScore();///verifica a posição no vetor de pontos a ser inserido e escreve no arquivo em seguida
    void readFromFile();///le do arquivo
    void displayRanking();///tela para mostrar o ranking
    void addChar(char key);///função utilizada para adicionar o char digitado no currentranking
    char getCurrentName(int i);///pega cada letra do nome
    void writeOnFile();///escreve no arquivo para guardar os valores do ranking
    Score* getScores();
    void addPointsToCurrentRanking(int points);///adiciona os pontos do jogo atual ao currentranking
private:
    Score scores[10];///vetor de scores que possui quantidade de pontos e nome

};

#endif // RANKING_H
