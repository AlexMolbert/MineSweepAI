#include "../include/MineSweeper.h"
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

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
            if(userBoard[i][j] == COVERED_SPACE){
                cout << " ?   ";
            }
            else if(userBoard[i][j] == FLAGGED_SPACE)
            {
                cout << " F   ";
            }
            else
            {
                if(gameBoard[i][j] == 0)
                {
                    cout << " *   ";
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
}

void MineSweeper::makeMove()
{
    char choice;
    int x, y;

    cin >> choice >> x >> y;
    x--;
    y--;

    if (choice != 'U' && choice != 'u' && choice != 'F' && choice !='f')
    {
        cout << "Invalid option! Please enter 'u' to uncover or 'f' to flag" << endl;
        makeMove();
        return;
    }

    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        cout << "Invalid coordinate!" << endl;
        makeMove();
        return;
    }

    if (userBoard[y][x] == UNCOVERED_SPACE)
    {
        cout << "Space already uncovered!" << endl;
        makeMove();
        return;
    }

    if (choice == 'U' || choice == 'u')
    {
        recursiveUncover(x, y);
    }

    else
    {
        flagSpace(x, y);
    }
}

void MineSweeper::flagSpace(int x, int y)
{
    userBoard[y][x] = FLAGGED_SPACE;
}

void MineSweeper::recursiveUncover(int x, int y)
{
    if (x < 0 || x >= size)
        return;
    if (y < 0 || y  >= size)
        return;

    if (userBoard[y][x] == UNCOVERED_SPACE)
        return;

    userBoard[y][x] = UNCOVERED_SPACE;

    if (gameBoard[y][x] != 0)
        return;

    recursiveUncover(x - 1, y - 1);
    recursiveUncover(x, y - 1);
    recursiveUncover(x + 1, y - 1);
    recursiveUncover(x - 1, y);
    recursiveUncover(x + 1, y);
    recursiveUncover(x - 1, y + 1);
    recursiveUncover(x, y + 1);
    recursiveUncover(x + 1, y + 1);
}
