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
        bool uncoverSpace();
        bool flagSpace();
        void generateGame(ui x, ui y);

    private:
        vector<vector<int> > gameBoard; // Underlying game board
        vector<vector<int> > userBoard; // The board that the user interacts with
        ui size;
        void recursiveUncover();


};

#endif // MINESWEEPER_H
