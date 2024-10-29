# Fast Tic Tac Toe

Extremely fast implementation of the game Tic Tac Toe in C++
using bitwise operations, precomputed winning conditions and very few branches

## Implementation

The game consists of a board of 9 slots so all we need to represent it is 9 bits
Each player gets their own board (playerBitboard) which has 1 for played and 0 for not played in the corresponding position
For instance, if player X's bitboard looked like this: 000000111 that means they have put 3 Xs on the top row

To check if the current player won, all we have to do is take the current player's bitboard and check if it's included in the precomputed winning bitboards array
The array is true on all winning combinations and false otherwise. For example, from the previous example, 000000111 is a winning board
That means the array has true (1) on the index number 000000111 (7)

Every turn we swap the current and the other player bitboard and character
to work faster with current player instead of always checking which player's turn it is

## Important notes and assumptions

This is not the fastest possible implementation purely code-wise, in the sense that there are some things
that are implied/assumed because the compiler will almost always do them for us with optimizations

Such things include:
  - Function inlining: Of course it would be faster not to have functions at all to avoid call overhead. I added functions purely for readability purposes
  - Usage of CPU registers instead of variables stored in RAM: The compiler will or should use registers for the variables declared in the code

Furthermore, the most amount of time in this program is spent on I/O (printing things to the console and user input)
This of course can be improved by either using a more efficient library instead of the standard one or better yet directly make the syscalls
I didn't do that here because the goal of the project was to make the code of the game itself faster not the I/O

## Potential Improvements

  - Removing the precomputed array for the winning check: if the array is not put into the cache, the memory access itself will be pretty slow
    Instead we can check all winning conditions manually
    
    ```cpp
    bool checkWin(int playerBitboard)
    {
        return  ((playerBitboard &  448)  == 448)     |
                ((playerBitboard &  56)   == 56)      |
                ((playerBitboard &  7)    == 7)       |
                ((playerBitboard &  292)  == 292)     |
                ((playerBitboard &  146)  == 146)     |
                ((playerBitboard &  73)   == 73)      |
                ((playerBitboard &  273)  == 273)     |
                ((playerBitboard &  84)   == 84);
    }
    ```
    
    This doesn't involve any memory access but can be slower than the previous version if the array ends up in the cache
  - Making the board a char array in the printing function (stack allocated) instead of global (static) and constructing it right at that moment
    before the printing to have a higher chance of it being in the cache??? Will have to benchmark it
  - Using SSE/AVX instructions with intrinsics for the winning conditions
