#ifndef MINESWEEPER_H
#define MINESWEEPER_H


// Values for userBoard;
#define COVERED_SPACE 0
#define UNCOVERED_SPACE 1
#define FLAGGED_SPACE 2

#include <vector>

using namespace std;

class MineSweeper
{
    public:
        MineSweeper();
        void print();
        void generateGame();
        bool uncoverSpace();
        bool flagSpace();

    private:
        vector<vector<int> > gameBoard; // Underlying game board
        vector<vector<int> > userBoard; // The board that the user interacts with
        int size;
        void recursiveUncover();
};

#endif // MINESWEEPER_H
