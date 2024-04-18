#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// define save score path
#define SCORE_PATH "data/Scores/scores.csv"
// define save game path
#define SAVE_PATH "data/SavedGames/save.txt"
using namespace std;

enum class PColor
{
    BLUE,
    YELLOW,
    RED,
    GREEN,
    PURPLE,
    ORANGE,
};

enum class PShape
{
    SQUARE,
    DIAMOND,
    CIRCLE,
    TRIANGLE,
    HEXAGON,
    STAR

};

class Piece
{
public:
    PColor color;
    PShape shape;

    Piece *next;
    Piece *shapePrev;
    Piece *shapeNext;
    Piece *colorPrev;
    Piece *colorNext;
    Piece(PColor c, PShape s);
    static Piece *generateRandomPiece(int PiecePool);
};

// Queue class
class Queue
{
public:
    Queue(int PiecePool);
    ~Queue();
    void initQueue();
    Piece *dequeue();
    void enqueue(Piece *piece);
    Piece *getFront();
    Piece *getRear();

private:
    Piece *front;
    Piece *rear;
    int PiecePool;
};

class GameBoard
{
private:
    int PiecePool;
    Piece **colorhead;
    Piece **shapehead;
    Piece **colortail;
    Piece **shapetail;
    Piece *head;
    Piece *tail;
    int size;
    int score;

public:
    Queue *incomingPieces;
    void init(int PiecePool);
    GameBoard(int PiecePool);
    GameBoard(bool resume);
    ~GameBoard();
    int getPiecePool();
    int getSize();
    int getScore();
    void setScore(int score);
    Piece *getHead();
    Piece *getTail();

    // insert Piece to left or right
    void insert(bool left, Piece *piece);
    // update pointer
    void updatePointers();
    // shift by color
    void shiftByColor(bool left, PColor color);
    // shift by shape
    void shiftByShape(bool left, PShape shape);
    // remove given piece from the board
    void removePiece(Piece *piece);

    // check if there are three or more consecutive pieces of the same color or shape in the board, delete the repeated pieces and update the score (10 * number of pieces deleted)
    int checkMatches();
    // save game
    void saveGame();


    // print board
    void printBoard();
};

// check if there is a saved game
bool checkSavedGame();
// save score to a file in descending order (Format of the csv file: playername,score)
void saveScore(int score, std::string playername);
// check if the score is among Top 10 scores
bool checkScore(int score);
// get Scores
std::vector<std::pair<std::string, int>> getScores();
