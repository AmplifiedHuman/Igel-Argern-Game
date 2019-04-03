#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game_logic.h"

//function prototypes
void printLine();
int totalMinTokens(square board[NUM_ROWS][NUM_COLUMNS], int minNumOfTokens);
bool checkWin(player players[], int numPlayers);
void push(token **startPointer, enum colour col);
void pop(token **startPointer);

/*
* Returns the first letter associated with the color of the token
*
* Input: t - pointer to a token
* Output: initial of the color of the token
*/
char print_token(token *t) {
	if (t->col == RED)    return 'R';
  	if (t->col == BLUE)   return 'B';
  	if (t->col == GREEN)  return 'G';
	if (t->col == YELLOW) return 'Y';
	if (t->col == PINK)   return 'P';
  	if (t->col == ORANGE) return 'O';
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
      		if (board[i][j].stack != NULL) {
        		c = print_token(board[i][j].stack);
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

  	int minNumOfTokens = 0;
  	int selectedSquare = 0;
  	bool isValidInput = false; //boolean to check for valid input
  	int flag = 0; //indicate if scanf has received valid input

  	for (int i = 0; i < 4; i++) {
    	for (int j = 0; j < numPlayers; j++) {

      		isValidInput = false;

      		while (!isValidInput) {
     			printf("Player %d, %s please select a square (1-6): ", j + 1, players[j].name);
        		fflush(stdout);
        		flag = scanf("%d", &selectedSquare);
        		selectedSquare--;

        		if (flag != 1 || selectedSquare < 0 || selectedSquare > 5) {
          			printf("Input must be in range (1 - 6).\n");
        		} 
						//checks if theres only one free spot
				else if (totalMinTokens(board, minNumOfTokens) != 1 && 
						//checks if stack is null
        				board[selectedSquare][0].stack != NULL &&  
						//checks if player color matches square colour
        				board[selectedSquare][0].stack->col == players[j].col) { 
          			printf("Token can't be placed on the square with the same colour.\n");
        		} 
				else if (board[selectedSquare][0].numTokens != minNumOfTokens) {
          			printf("Token must be placed on the lowest stack.\n");
        		} 
				else {
          			isValidInput = true; //if none  of these cases happen, input is valid
        		}

        		while (getchar() != '\n'); //removes invalid input from buffer
        		puts("");
     		}

      		push(&board[selectedSquare][0].stack, players[j].col);
      		board[selectedSquare][0].numTokens++;

      		//need some time to understand, write formula on paper, very smart
      		//basically find the min number of tokens at each iteration/round
      		if (((numPlayers * i) + j + 1) % NUM_ROWS == 0) {
        		minNumOfTokens++;
      		}
      		print_board(board);
    	}
  	}
}


/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
  	srand(time(NULL));
  	int diceRoll;
  	for (int i  = 0; i < numPlayers; i++) {
    	print_board(board);
    	diceRoll = rand() % 6 + 1;
    	printf("Player %d, your dice roll is %d.\n", i + 1, diceRoll);
  	}
}

/*
 * Checks how many rows have minimum tokens
 * 
 * Input: board - a 6x9 array of squares that represents the board
 * 		  minNumOfTokens - number of tokens in lowest stack 
 * Output: number of rows with minimum tokens
 */
int totalMinTokens(square board[NUM_ROWS][NUM_COLUMNS], int minNumOfTokens) {
  	int count = 0;
  	for (int j = 0; j < NUM_ROWS; j++) {
    	if (board[j][0].numTokens == minNumOfTokens) {
      		count++;
    	}
  	}
  	return count;
}

bool checkWin(player players[], int numPlayers) {
  	for (int i = 0; i < numPlayers; i++) {
    	if (players[i].numTokensLastCol >= 3) {
      		return true;
    	}
  	}
  	return false;
}

void push(token **startPointer, enum colour col) {
  	token *temp = malloc(sizeof(token));
  	temp->col = col;
  	temp->nextPtr = *startPointer;
  	*startPointer = temp;
}

void pop(token **startPointer) {
  	if (*startPointer == NULL) {
    	return;
  	}
  	token *temp = *startPointer;
  	*startPointer = (*startPointer)->nextPtr;
  	free(temp);
}
