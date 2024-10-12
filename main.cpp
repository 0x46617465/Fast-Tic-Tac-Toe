#include <iostream>

// True on all winning board numbers
constexpr bool MagicArray[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

char board[] =
{
    '1', ' ', '|', ' ', '2', ' ', '|', ' ', '3', '\n',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '\n',
    '4', ' ', '|', ' ', '5', ' ', '|', ' ', '6', '\n',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '\n',
    '7', ' ', '|', ' ', '8', ' ', '|', ' ', '9', '\n'
};

bool checkWin(int playerBitboard);
bool makeMove(int& playerBitboard, int& fullBitboard, char playerChar, int position);
void displayBoard();
void printResults(bool gameWon, char currentPlayerCharacter);

int main()
{
    constexpr char playerCharacters[]{ 'X', 'O' };

    int playerBitboards[]{ 0, 0 };
    int fullBitboard{ 0 };
    int currentPlayerIndex{ 0 };  // 0 = X, 1 = O
    char currentPlayerCharacter{};

    bool gameWon{ false };
    int movesLeft{ 9 };

    while (movesLeft)
    {
        displayBoard();
        currentPlayerCharacter = playerCharacters[currentPlayerIndex];

        std::cout << "Player " << currentPlayerCharacter << ", enter your move (1-9): ";
        int move{};
        std::cin >> move;

        if (!makeMove(playerBitboards[currentPlayerIndex], fullBitboard, currentPlayerCharacter, move)) [[unlikely]]
        {
            std::cout << "Invalid move! Try again.\n";
            continue;
        }
        if (checkWin(playerBitboards[currentPlayerIndex])) [[unlikely]]
        {
            gameWon = true;
            break;
        }

        currentPlayerIndex ^= 1;  // Switch player: 0->1 and vice versa
        --movesLeft;
    }

    printResults(gameWon, currentPlayerCharacter);
    return 0;
}

bool checkWin(int playerBitboard)
{
    return MagicArray[playerBitboard];
}

bool makeMove(int& playerBitboard, int& fullBitboard, char playerChar, int position)
{
    --position;

    int bitmask = (1 << position);
    if (position < 0 || position > 8 || (fullBitboard & bitmask))
        return false;


    playerBitboard |= bitmask;
    fullBitboard |= bitmask;
    
    int boardIndex = (position << 2) + ((position / 3) << 3);
    board[boardIndex] = playerChar;

    return true;
}

void displayBoard()
{
    std::cout << '\n' << board << '\n';
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