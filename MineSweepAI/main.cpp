#include <iostream>
#include "include/MineSweeper.h"

using namespace std;

int main()
{
    MineSweeper m;
    m.generateGame(0, 0);
    m.print();
    return 0;
}
