#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game_init.h"

/*
 * Prints lines for constructing the board
 */
void printLine();

/*
 * Returns true if there is a square with minimum number of tokens whose colour is 
 * not the same as the player's colour.
 * 
 * Input: board - a 6x9 array of squares that represents the board
 * 		  minTokens - number of tokens in lowest stack 
 * 		  col - player's chosen colour
 */
bool minWithDiffColour(square board[NUM_ROWS][NUM_COLUMNS], int minTokens, enum colour col);

/*
 * Checks how many rows have minimum tokens
 * 
 * Input: board - a 6x9 array of squares that represents the board
 * 		  minTokens - number of tokens in lowest stack 
 * Output: number of rows with minimum tokens
 */
int totalMinSquares(square board[NUM_ROWS][NUM_COLUMNS], int minTokens);


/* 
 * Return true if a player has at least 3 tokens in last column, i.e.
 * the game has been won
 * 
 * Input: players - the array of players
 *        numPlayers - the number of players
 */
bool checkWin(player players[], int numPlayers);


/*
 * Place a token on the stack
 * 
 * Input: top - pointer to topmost token pointer on stack
 */
void push(token **top, enum colour col);


/*
 * Remove a token from the stack
 * 
 * Input: top - pointer to topmost token pointer on stack
 */
void pop(token **top);


/*
 * Prints the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);


/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);



/*
 * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
