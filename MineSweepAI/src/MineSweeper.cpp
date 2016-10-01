#include "../include/MineSweeper.h"
#include <iostream>
<<<<<<< HEAD
#include <iomanip>
=======
#include <cmath>
#include <random>
#include <iomanip>

>>>>>>> origin/master
MineSweeper::MineSweeper()
{
    size = 16;
}

void MineSweeper::changeSize(ui newSize)
{
    size = newSize;
}

void MineSweeper::print()
{
    cout << "    | ";
    for(int i = 1; i <= size; i++){
        cout << setw(2);
        cout << i << " | ";
    }
    cout << "\n" << "     ";
    for(int i = 0; i <= size * 5; i++){
        cout << "-";
    }
    cout << "\n";

    for(unsigned int i = 0; i < size; i++)
    {
        cout << setw(3);
        cout << i + 1 << " |";
        for(unsigned int j = 0; j <size; j++)
        {
            if(userBoard[i][j] == 1){
                cout << " *   ";
            }
            else if(userBoard[i][j] == 2)
            {
                cout << " F   ";
            }
            else
            {
                if(gameBoard[i][j] == 0)
                {
                    cout << " ?   ";
                }
                else
                    cout << " " << gameBoard[i][j] << "   ";
            }
        }
        cout << " |" << "\n";
    }
    cout << "     ";
    for(int i = 0; i <= size * 5; i++){
        cout << "-";
    }
    return;
}

void MineSweeper::generateGame(ui x, ui y)
{
    gameBoard.resize(size);
    userBoard.resize(size);

    for (ui i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i].resize(size);
    }

    for (ui i = 0; i < userBoard.size(); i++)
    {
        userBoard[i].resize(size);
    }

    for (ui i = 0; i < userBoard.size(); i++)
    {
        for (ui j = 0; j < userBoard.size(); j++)
        {
            userBoard[i][j] = COVERED_SPACE;
        }
    }
    random_device rd;

    for (ui i = 0; i < 40; i++)
    {
        bool validGen = false;
        while(!validGen)
        {
            ui gx, gy;
            gx = rd() % size;
            gy = rd() % size;

            if (x != gx && y != gy)
            {
                if (gameBoard[gx][gy] != -1)
                {
                    gameBoard[gx][gy] = -1;
                    validGen = true;
                }
            }
        }
    }

    for (int i = 0; i < gameBoard.size(); i++)
    {
        for (int j = 0; j < gameBoard.size(); j++)
        {
            if (gameBoard[i][j] != -1)
            {

                int count = 0;

                if (i - 1 > 0)
                {
                    if ((j - 1) > 0 && gameBoard[i - 1][j - 1] == -1)
                        count++;
                    if (gameBoard[i - 1][j] == -1)
                        count++;
                    if (j + 1 < size && gameBoard[i - 1][j + 1] == -1)
                        count++;
                }

                if (j - 1 > 0 && gameBoard[i][j - 1] == -1)
                    count++;
                if (j + 1 < size && gameBoard[i][j + 1] == -1)
                    count++;

                if (i + 1 < size)
                {
                    if (j - 1 > 0 && gameBoard[i + 1][j - 1] == -1)
                        count++;
                    if (gameBoard[i + 1][j] == -1)
                        count++;
                    if (j + 1 < size && gameBoard[i + 1][j + 1] == -1)
                        count++;
                }

                gameBoard[i][j] = count;
            }
        }
    }

    for (auto i : gameBoard)
    {
        for (auto j : i)
        {
            cout << setw(3) << j;
        }
        cout << endl;
    }
}

bool MineSweeper::uncoverSpace()
{

}

bool MineSweeper::flagSpace()
{

}

void MineSweeper::recursiveUncover()
{

}
