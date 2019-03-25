#include <stdio.h>
#include "game_logic.h"

void printLine();

/*
 * Returns the first letter associated with the colour of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the colour of the token
 */
char print_token(token t) {
	if (t.col == RED)    return 'R';
  	if (t.col == BLUE)   return 'B';
  	if (t.col == GREEN)  return 'G';
	if (t.col == YELLOW) return 'Y';
	if (t.col == PINK)   return 'P';
  	if (t.col == ORANGE) return 'O';
  	return '\0';
}

/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]) {
  	printf("\n                THE BOARD\n");
  	for (int i = 0; i < NUM_ROWS; i++) {
    	//prints an horizontal line
    	printLine();
    	//prints the row number
    	printf(" %d ", i + 1);

		/*if the square (i,j) is occupied, c is assigned the initial of 
		  the colour of the token that occupies the square*/
    	char c = '\0' ;
    	
    	for (int j = 0; j < NUM_COLUMNS; j++) {
			//if stack is not empty, print token at the top of the stack 
      		if (board[i][j].top != -1) {
        		c = print_token(board[i][j].stack[board[i][j].top]);
      		}
      		//if the square (i,j) is empty
      		else {
        		//c is assigned 'X' if the square represents an obstacle
        		if (board[i][j].type == OBSTACLE)
        			c = 'X';
        		//c is assigned an empty space otherwise
        		else
        			c = ' ';
      		}
      		printf("| %c ", c);
    	}
    	printf ("|\n");
  	}
  	printLine();
  	//prints the number of the columns at the end of the board
  	printf("     1   2   3   4   5   6   7   8   9\n");
}

void printLine() {
  	printf("   -------------------------------------\n");
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
	//total number of tokens
	int numTokens = numPlayers * 4;
	//stores row number entered by player
	int nrow;
	//used to validate scanf input
	int r; 
	//flag to chek if row is valid to place token
	int flag;
	//used to check if a non-empty square is chosen, even though empty ones exist
	int empty_sq;
	//stores the height of the lowest stack in the first column
	int lowest_stack = 0;
	
	do {
		//ask players to place tokens (clockwise order, one by one)
		for (int i = 0; i < numPlayers; i++) {
			do {
				printf("\n%s's turn, choose a row to place token: ", players[i].name);
				fflush(stdout);
				//take input and store number of entered items for validation
				r = scanf("%d", &nrow); 

				//reset flag to 0
				flag = 0;
				//reset square to non-empty
				empty_sq = 0;	

				if (nrow > 0 && nrow < 7) {
					for (int i = 0; i < 6; i++) {
						//calculate the height of the lowest stack in the column
						if (board[i][0].top < lowest_stack) {
							lowest_stack = board[i][0].top;
						}
						//set empty_sq to 1 if chosen sqaure is non-empty, but empty sqaures exist
						if (board[i][0].top == -1 && board[nrow-1][0].top != -1) {
							empty_sq = 1;
						}
					}

					//set flag if player doesn't place token as low as possible 
					//(exception: player is not forced to block their own tokens)
					if (empty_sq == 1 || (board[nrow-1][0].top != -1 &&
					     	(board[nrow-1][0].stack[board[nrow-1][0].top].col == players[i].col ||
						 		 board[nrow-1][0].top != lowest_stack))) {
						flag = 1;
						printf("\nYou are not forced to block yourself.");
						printf("\nToken must be placed as low as possible!\n");
					}
				}
			} while(r != 1 || nrow < 1 || nrow > 6 || flag == 1);
			
			//temporary token
			token t;
			//assign player's token colour to temporary token 
			t.col = players[i].col; 

			//place token on top of the chosen square
			board[nrow-1][0].stack[++board[nrow-1][0].top] = t;

			//decrement the number of tokens left to be placed
			numTokens--;

			//increment the size of the lowest stack
			lowest_stack++;

			print_board(board);
		}
	} while (numTokens != 0); 
}


/*
 * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
  	//TO BE IMPLEMENTED
}
