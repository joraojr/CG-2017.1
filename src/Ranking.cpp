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
    int i = 0;
    while (currentRanking.score < scores[i+1].score && i < 9){
        scores[i].score = scores[i+1].score;
        strcpy(scores[i].name, scores[i+1].name);
        i++;
    }
    if (currentRanking.score < scores[i].score) {
        scores[i].score = currentRanking.score;
        strcpy(scores[i].name, currentRanking.name );
    }
    writeOnFile();
}

void Ranking::readFromFile(){
    FILE * pFile;

    pFile = fopen("TopScores.txt" , "r");

    for (int i = 0; i < 10; i++){
        fscanf (pFile, "%d %s", &scores[i].score, &scores[i].name);
    }
}

char Ranking::getCurrentName(int i){
    return currentRanking.name[i];
}

void Ranking::printRanking(){
    for(int i = 0; i < 10; i++){
        cout << scores[i].name << " - ";
        cout << scores[i].score << endl;
    }
}

void Ranking::ordering(){
    for(int i = 0; i < 10; i++){
        for(int j = 0 ; j < 9; j++){
            if(scores[j+1].score < scores[j].score){
                int aux = scores[j].score;
                scores[j].score = scores[j+1].score;
                scores[j+1].score = aux;

                swapName(scores[j].name,scores[j+1].name);
            }
        }
    }
}

void Ranking::swapName(char name1[21],char name2[21]){
    char aux [21];
    int i;
    for(int i = 0; i < 21; i++){
        aux[i] = name1[i];
    }

    for(i = 0; i < 21; i++){
        name1[i] = name2[i];
    }

    for(i = 0; i < 21; i++){
        name2[i] = aux[i];
    }
}

void Ranking::addPointsToCurrentRanking(int points){
    currentRanking.score = points;
}

Score* Ranking::getScores(){
    return this->scores;
}
