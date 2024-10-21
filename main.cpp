#include <iostream>

// True on all winning board numbers
constexpr bool MagicArray[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

char board[] =
{
    '\n',
    '1', ' ', '|', ' ', '2', ' ', '|', ' ', '3', '\n',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '\n',
    '4', ' ', '|', ' ', '5', ' ', '|', ' ', '6', '\n',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '\n',
    '7', ' ', '|', ' ', '8', ' ', '|', ' ', '9', '\n',
    '\n'
};

bool checkWin(int playerBitboard);
bool makeMove(int& playerBitboard, int fullBitboard, char playerChar, int position);
void displayBoard();
void printResults(bool gameWon, char currentPlayerCharacter);

int main()
{
    int currentBitboard{ 0 }, otherBitboard{ 0 };
    char currentPlayerCharacter{ 'X' }, otherPlayerCharacter{ 'O' };

    bool gameWon{ false };
    int movesLeft{ 9 };

    while (movesLeft)
    {
        displayBoard();

        std::cout << "Player " << currentPlayerCharacter << ", enter your move (1-9): ";
        int move{};
        std::cin >> move;

        if (!makeMove(currentBitboard, currentBitboard | otherBitboard, currentPlayerCharacter, move)) [[unlikely]]
        {
            std::cout << "Invalid move! Try again.\n";
            continue;
        }
        if (checkWin(currentBitboard)) [[unlikely]]
        {
            gameWon = true;
            break;
        }

        // Switch player
        std::swap(currentBitboard, otherBitboard);
        std::swap(currentPlayerCharacter, otherPlayerCharacter);
        --movesLeft;
    }

    printResults(gameWon, currentPlayerCharacter);
    return 0;
}

bool checkWin(int playerBitboard)
{
    return MagicArray[playerBitboard];
}

bool makeMove(int& playerBitboard, int fullBitboard, char playerChar, int position)
{
    --position;

    int bitmask = (1 << position);
    if (position < 0 || position > 8 || (fullBitboard & bitmask)) [[unlikely]]
        return false;

    playerBitboard |= bitmask;
    
    int boardIndex = ((position << 2) + 1) + ((position / 3) << 3);
    board[boardIndex] = playerChar;

    return true;
}

void displayBoard()
{
    std::cout << board;
}

void printResults(bool gameWon, char currentPlayerCharacter)
{
    displayBoard();

    if (gameWon)
    {
        std::cout << "Player " << currentPlayerCharacter << " wins!\n";
    }
    else
    {
        std::cout << "It's a tie!\n";
    }
}

/*
    If we want to save some space we can use a 64 byte array instead of a 512 byte one
    constexpr int MagicArray[] = 
    { 
        8421504,    385876096,  1928374912, 393218688, 
        1154252928, 386662528,  276046336,  1311232, 
        715817088,  389697776,  309987840,  1179728, 
        103677952,  135216,     1513239,    23
    };

    bool checkWin(int playerBitboard)
    {
        return MagicArray[playerBitboard >> 5] & (1 << (playerBitboard & 31));
    }

*/