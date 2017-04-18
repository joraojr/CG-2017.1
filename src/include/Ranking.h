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
    void addScore();
    void readFromFile();
    void displayRanking();
    void newRanking(int score);
    void addChar(char key);
    char getCurrentName(int i);
    void writeOnFile();
    Score* getScores();
private:
    Score scores[10];

};

#endif // RANKING_H
