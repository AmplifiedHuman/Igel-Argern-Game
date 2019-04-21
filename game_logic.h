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
 * Input:     board - a 6x9 array of squares that represents the board
 * 		  minTokens - number of tokens in lowest stack
 * 		        col - player's chosen colour
 */
bool minWithDiffColour(square board[NUM_ROWS][NUM_COLUMNS], int minTokens, enum colour col);

/*
 * Returns true if the given row is empty or if all tokens in the row are blocked
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *          row - the row index of the square being checked
 */
bool emptyRow(square board[NUM_ROWS][NUM_COLUMNS], int row);

/*
 * Returns true if the square in selected row and column is blocked 
 * and no token can be moved from it
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *          row - the row index of the square being checked
 *       column - the column index of the square being checked
 */
bool blocked(square board[NUM_ROWS][NUM_COLUMNS], int row, int column);

/*
 * Return true if a player has at least 3 tokens in last column, i.e.
 * the game has been won
 *
 * Input:    players - the array of players
 *        numPlayers - the number of players
 *            winner - pointer to index of winning player       
 */
bool checkWin(player players[], int numPlayers, int *winner);

/*
 * Place a token on the stack
 *
 * Input: top - pointer to topmost token pointer on stack
 *        col - colour of token to be placed on stack
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
 * Input:     board - a 6x9 array of squares that represents the board
 *          players - the array of the players
 *       numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

/*
 * Manages the logic of the game
 *
 * Input:    board - a 6x9 array of squares that represents the board
 *         players - the array of the players
 *      numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
