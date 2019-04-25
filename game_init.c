#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game_init.h"
/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 */
void initialise_board(square board[NUM_ROWS][NUM_COLUMNS]) {

    //iterate through all the rows and columns of the board
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLUMNS; j++) {
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if ((i == 0 && j == 3) || (i == 1 && j == 6) || (i == 2 && j == 4)
                    || (i == 3 && j == 5) || (i == 4 && j == 2) || (i == 5 && j == 7)) {
                board[i][j].type = OBSTACLE;
            }
            else {
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
    char *colours[6] = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "ORANGE"};
    int flag[6] = {0}; //array to store which colours have already been chosen
    int choice = 0; //stores user's token colour choice

    printf("Welcome to game, Igel Argern!\n");
    printf("Please enter the number of players to continue (2-6): ");
    fflush(stdout);

    while ((scanf("%d", &numPlayers) != 1 || numPlayers < 2 || numPlayers > 6)) { //validation check
        printf("Please enter the number of players to continue (2-6): ");
        while (getchar() != '\n'); //removes invalid input from buffer
    }

    for (int i = 0; i < numPlayers; i++) {

        getchar(); //gets rid of newline character
        printf("\nPlease enter the name of player #%d: ", i + 1);
        fgets(players[i].name, 70, stdin); //get player's name with spaces
        if (strlen(players[i].name) != 69) { //check if the string is full (no newline char)
            players[i].name[strlen(players[i].name) - 1] = '\0'; //remove newline character from name
        }

        choice = 0;
        printf("\nAvailable token colours:\n");
        for (int j = 0; j < 6; j++) {
            if (flag[j] == 0) { //if colour is available
                printf("Colour %d: %s\n", j+1, colours[j]); //display available colours
            }
        }
        printf("Please choose one of the above colours: ");
        fflush(stdout);

        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 6 || flag[choice - 1] == 1) { //validation check
            printf("Please choose one of the above colours: ");
            while(getchar() != '\n'); //removes invalid input from buffer
        }
        //from colour options, remove colour that has already been chosen
        flag[choice - 1] = 1;

        //assign colour to current player
        players[i].col = (enum colour) (choice - 1);
        //initialise the player's tokens in the last column to 0
        players[i].numTokensLastCol = 0;
        printf("Your token colour is %s!\n", colours[choice - 1]);
    }
    return numPlayers;
}

/*
 * This function free all  allocated memory after the game ends
 *
 * Input: the board
 * Output: -
 */
void cleanup(square board[NUM_ROWS][NUM_COLUMNS]) {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLUMNS; j++) {
      // skips the square if there are no tokens (board[i][j].stack == NULL)
      if (board[i][j].stack != NULL) {
        // keep freeing the tokens until the square is empty (board[i][j].stack == NULL)
        while (board[i][j].stack != NULL) {
          //make temporary pointer the top pointer
          token *temp = board[i][j].stack;
          //let topmost pointer point to 2nd topmost pointer
          board[i][j].stack = (board[i][j].stack)->nextPtr;
          //get rid of the temporary pointer
          free(temp);
        }
      }
    }
  }
}
