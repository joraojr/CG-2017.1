#include "Ranking.h"


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

    pFile = fopen ("TopScores.txt" , "r");
    if (pFile == NULL){
        for (int i =0; i < 10; i++){
            scores[i].score = 1000;
            scores[i].name[0] = 'A';
            scores[i].name[1] = 'A';
            scores[i].name[2] = 'A';
            scores[i].name[3] = '\0';
        }
    }
    else{
        for (int i = 0; i < 10; i++){
            fscanf (pFile, "%d %s", &scores[i].score, &scores[i].name);
        }
    }
}

char Ranking::getCurrentName(int i){
    return currentRanking.name[i];
}

Score* Ranking::getScores(){
    return this->scores;
}
