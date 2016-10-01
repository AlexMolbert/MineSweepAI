#ifndef MINESWEEPER_H
#define MINESWEEPER_H


// Values for userBoard;
#define COVERED_SPACE 0
#define UNCOVERED_SPACE 1
#define FLAGGED_SPACE 2

#define ONGOING 0
#define FAILURE 1
#define SUCCESS 2

#include <vector>

typedef unsigned int ui;

using namespace std;

class MineSweeper
{
    public:
        MineSweeper();
        void gameLoop();


    private:
        vector<vector<int> > gameBoard; // Underlying game board
        vector<vector<int> > userBoard; // The board that the user interacts with
        int size, mine;
        int state;

        void getDifficulty();
        void changeSize(int newSize);
        void print();
        void generateGame(int x, int y);
        void uncover(int x, int y);
        void makeMove();
        void checkClear();
        void flagSpace(int x, int y);
        void recursiveUncover(int x, int y);
};

#endif // MINESWEEPER_H
