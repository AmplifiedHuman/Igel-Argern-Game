#include <stdio.h>
#include "game_init.h"
/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 */
void initialise_board(square board[NUM_ROWS][NUM_COLUMNS]) {
   for (int i = 0; i< NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLUMNS; j++) {
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if ((i == 0 && j == 3) || (i == 1 && j == 6) || (i ==2 && j == 4)
                    || (i == 3 && j ==5) || (i == 4 && j == 2) || (i == 5 && j == 7)) {
                board[i][j].type = OBSTACLE;
            } else {
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            //initialise stack pointer to null
            board[i][j].stack = NULL;
            //set initial number of tokens to 0
            board[i][j].numTokens = 0;
        }
    }
}


/*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialised
 * Output: The number of players of the game
 */
int initialise_players(player players[]) {
    //number of players
    int numPlayers = 0; 
    //names of token colours
    char *tokenCol[6] = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "ORANGE"};

    printf("Welcome to the game!\n");
    printf("Please enter the number of players to continue (2-6): ");
    fflush(stdout);

    while ((scanf("%d", &numPlayers) != 1 || numPlayers < 2 || numPlayers > 6)) { //validation check
        printf("Please enter the number of players to continue (2-6): ");
        while (getchar() != '\n'); //removes invalid input from buffer
    }

    for (int i = 0; i < numPlayers; i++) {
        printf("Please enter the name of player #%d: ", i + 1);
        scanf("%69s", players[i].name);

        players[i].col = (enum colour) i;
        players[i].numTokensLastCol = 0;
        printf("Token colour: %s\n", tokenCol[players[i].col]);
    }

    return numPlayers;
}
