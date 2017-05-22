#include "Ranking.h"
#include <iostream>

using namespace std;

Ranking::Ranking()
{
    //ctor
}

Ranking::~Ranking()
{
    //dtor
}

static int charCount = 0;
int amountOfScores = 0;
static Score currentRanking;

void Ranking::addChar(char key){
    if (charCount >= 10) charCount = 9;
    currentRanking.name[charCount] = key;
    charCount++;
    currentRanking.name[charCount] = 0;
}

void Ranking::writeOnFile(){
    FILE *pFile;
    pFile = fopen("TopScores.txt" , "w");
    for (int i =0; i < 10; i++){
        fprintf (pFile, "%d %s\n", scores[i].score, scores[i].name);
    }
}

void Ranking::addScore(){
    int aux;
    char* auxName = new char[21];
    charCount = 0;
    for(int i = 9 ; i>=0 ; i --){
        if(currentRanking.score > scores[i].score){
            aux = scores[i].score;
            strcpy(auxName,scores[i].name);
            scores[i].score = currentRanking.score;
            strcpy(scores[i].name,currentRanking.name);
            currentRanking.score = aux;
            strcpy(currentRanking.name,auxName);
        }
    }
    strcpy(currentRanking.name,"");
    writeOnFile();
}

void Ranking::readFromFile(){
    FILE * pFile;

    pFile = fopen("TopScores.txt" , "r");

    for (int i = 0; i < 10; i++){
        fscanf (pFile, "%d %s", &scores[i].score, scores[i].name);
    }
}

char Ranking::getCurrentName(int i){
    return currentRanking.name[i];
}

void Ranking::addPointsToCurrentRanking(int points){
    currentRanking.score = points;
}

Score* Ranking::getScores(){
    return this->scores;
}
