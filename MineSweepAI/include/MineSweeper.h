#ifndef MINESWEEPER_H
#define MINESWEEPER_H


// Values for userBoard;
#define COVERED_SPACE 0
#define UNCOVERED_SPACE 1
#define FLAGGED_SPACE 2

#include <vector>

typedef unsigned int ui;

using namespace std;

class MineSweeper
{
    public:
        MineSweeper();
        void changeSize(ui newSize);
        void print();
        void generateGame(ui x, ui y);

        void makeMove();

    private:
        vector<vector<int> > gameBoard; // Underlying game board
        vector<vector<int> > userBoard; // The board that the user interacts with
        ui size;

        void flagSpace(int x, int y);
        void recursiveUncover(int x, int y);
};

#endif // MINESWEEPER_H
