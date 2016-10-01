#include "../include/MineSweeper.h"
#include <iostream>
#include <iomanip>
MineSweeper::MineSweeper()
{
    //ctor
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

void generateGame()
{
    return;
}

bool uncoverSpace()
{

}

bool flagSpace()
{

}

void recursiveUncover()
{

}
