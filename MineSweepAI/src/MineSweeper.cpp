#include "../include/MineSweeper.h"
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <chrono>

MineSweeper::MineSweeper()
{
    size = 16;
}

void MineSweeper::changeSize(int newSize)
{
    size = newSize;
}

void MineSweeper::print()
{
    cout << "      ";
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
                {
                    if(gameBoard[i][j] == -1){
                        cout << " B   ";
                    }
                    else
                        cout << " " << gameBoard[i][j] << "   ";
                }
            }
        }
        cout << " |" << "\n";
    }
    cout << "     ";
    for(int i = 0; i <= size * 5; i++){
        cout << "-";
    }
    cout << "\n\n";
    return;
}

void MineSweeper::generateGame(int x, int y)
{
    state = ONGOING;
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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator (seed);

    int lowx = max(0, x - 2);
    int lowy = max(0, y - 2);
    int highx = min(size - 1, x + 2);
    int highy = min(size - 1, y + 2);

    for (ui i = 0; i < mine; i++)
    {
        bool validGen = false;
        while(!validGen)
        {
            int gx, gy;
            gx = generator() % size;
            gy = generator() % size;

            if (highx >= gx && gx >= lowx && highy >= gy && gy >= lowy)
            {

            }

            else if (gameBoard[gy][gx] != -1)
            {
                    gameBoard[gy][gx] = -1;
                    validGen = true;
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

                if (i - 1 >= 0)
                {
                    if ((j - 1) >= 0 && gameBoard[i - 1][j - 1] == -1)
                        count++;
                    if (gameBoard[i - 1][j] == -1)
                        count++;
                    if (j + 1 < size && gameBoard[i - 1][j + 1] == -1)
                        count++;
                }

                if (j - 1 >= 0 && gameBoard[i][j - 1] == -1)
                    count++;
                if (j + 1 < size && gameBoard[i][j + 1] == -1)
                    count++;

                if (i + 1 < size)
                {
                    if (j - 1 >= 0 && gameBoard[i + 1][j - 1] == -1)
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
    print();
    cout << "Make your next move: ";
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
        cout << "Invalid Space!" << endl;
        makeMove();
        return;
    }

    if (userBoard[y][x] == FLAGGED_SPACE && (choice == 'U' || choice == 'u'))
    {
        cout << "Don't wanna do that kiddo." << endl;
        makeMove();
        return;
    }

    if (choice == 'U' || choice == 'u')
    {
        uncover(x, y);
    }

    else
    {
        flagSpace(x, y);
    }
}

void MineSweeper::flagSpace(int x, int y)
{
    if (userBoard[y][x] == COVERED_SPACE)
        userBoard[y][x] = FLAGGED_SPACE;
    else
        userBoard[y][x] = COVERED_SPACE;
}


void MineSweeper::gameLoop(){
    int x, y;
    getDifficulty();
    if(!checkAI()){
        aiLoop();
        return;
    }

    cout << "Make your first move: ";
    cin >> x >> y;
    x--;
    y--;
    generateGame(x, y);

    recursiveUncover(x, y);

    while(state == ONGOING){
        makeMove();
        checkClear();
    }

    print();
    if(state == FAILURE)
        cout << "You hit a bomb dummy";
    if(state == SUCCESS)
        cout << "All out. ";

}

void MineSweeper::getDifficulty() {
    string difficulty;
    cout << "Enter your difficulty level - \n (Easy - 8x8 and 10 mines, Medium - 16x16 and 40 mines, Expert - 24x24 and 99 miness): ";
    cin >> difficulty;

    if(difficulty == "easy" || difficulty == "Easy" || difficulty == "8x8"){
        changeSize(8);
        mine = 10;
    }

    else if(difficulty == "medium" || difficulty == "Medium" || difficulty == "16x16"){
        changeSize(16);
        mine = 40;
    }

    else if(difficulty == "expert" || difficulty == "Expert" || difficulty == "24x24"){
        changeSize(24);
        mine = 99;
    }
    else {
        cout << "Bad Input. \n";
        getDifficulty();
        return;
    }


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

void MineSweeper::checkClear()
{
    for (unsigned int i = 0; i < userBoard.size(); i++)
    {
        for (unsigned int j = 0; j < userBoard.size(); j++)
        {
            if (userBoard[i][j] == COVERED_SPACE && gameBoard[i][j] != -1)
            {
                return;
            }
        }
    }

    state = SUCCESS;
}

void MineSweeper::uncover(int x, int y)
{
    if (gameBoard[y][x] == -1)
    {
        state = FAILURE;
        for (unsigned int i = 0; i < userBoard.size(); i++)
        {
            for (unsigned int j = 0; j < userBoard.size(); j++)
            {
                userBoard[i][j] = UNCOVERED_SPACE;
            }
        }
    }

    else
    {
        recursiveUncover(x, y);
    }
}

bool MineSweeper::checkAI(){
    string choice;
    cout << "Do you need help stupid human? (Get the help of a bot) Yes/No? ";
    cin >> choice;

    while(choice != "Yes" && choice != "yes" && choice != "No" && choice != "no" ){
        if(choice == "Yes" || choice == "yes")
            return true;
        else if(choice == "No" || choice == "no")
            return false;
        else {
            cout << "Bad input. Yes or No? ";
            cin >> choice;
        }
    }

}

void MineSweeper::aiLoop(){

}
