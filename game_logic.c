#include "game_logic.h"
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
 * Input: board - a 6x9 array of squares that represents the board
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
  	printf("     1   2   3   4   5   6   7   8   9\n\n");
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
	int minTokens = 0; //number of tokens in lowest stack 
  	int selectedSquare; //row number in first column, square selected by player
  	bool isValidInput = false; //boolean to check for valid input
  	int flag = 0; //indicate if scanf has received valid input

  	for (int i = 0; i < 4; i++) {
    	for (int j = 0; j < numPlayers; j++) {

			//reset valid input flag to false
      		isValidInput = false;

			//loop as long as selected square is invalid
      		while (!isValidInput) {
     			printf("\nPlayer %d, %s please select a square (1-6): ", j + 1, players[j].name);
        		fflush(stdout);
        		flag = scanf("%d", &selectedSquare);
        		selectedSquare--; //change row number to row index

				//conditions where input is invalid
        		if (flag != 1 || selectedSquare < 0 || selectedSquare > 5) {
          			printf("Input must be in range (1 - 6).");
        		} 
					    //checks if there is a lowest stack with a different colour
				else if (minWithDiffColour(board, minTokens, players[j].col) &&
						//checks if player color matches square colour
						board[selectedSquare][0].stack->col == players[j].col &&
						//checks if stack is not null
        				board[selectedSquare][0].stack != NULL) { 
          			printf("Token can't be placed on top of your own token!");
        		} 
				else if (board[selectedSquare][0].numTokens != minTokens) {
          			printf("Token must be placed on the lowest stack.");
        		} 
				else {
          			isValidInput = true; //if none  of these cases happen, input is valid
        		}

        		while (getchar() != '\n'); //removes invalid input from buffer
        		puts("");
     		}
			
			//when input is validated, place token on selected square
      		push(&board[selectedSquare][0].stack, players[j].col);
      		board[selectedSquare][0].numTokens++;

      		//find the minimum number of tokens at each iteration/round
      		if (((numPlayers * i) + j + 1) % NUM_ROWS == 0) {
        		minTokens++;
      		}
      		print_board(board);
    	}
  	}
}

/*
 * Returns true if there is a square with minimum number of tokens whose colour is 
 * not the same as the player's colour.
 * 
 * Input: board - a 6x9 array of squares that represents the board
 * 		  minTokens - number of tokens in lowest stack 
 *        col - player's chosen colour
 */
bool minWithDiffColour(square board[NUM_ROWS][NUM_COLUMNS], int minTokens, enum colour col) {
	for (int i = 0; i < NUM_ROWS; i++) {
			if (board[i][0].stack != NULL && board[i][0].numTokens == minTokens 
					&& board[i][0].stack->col != col)
				return true;
	}
	return false;
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
	
  	int diceRoll;
	int op;

  	int sideChoice [NUM_ROWS][NUM_COLUMNS] = {0};
	int forwardChoice;
	int columnChoice[NUM_COLUMNS] = {0};

	int sideRow;
	int sideCol;
	char upDown;

	while (!checkWin(players, numPlayers)) {
		for (int i  = 0; i < numPlayers; i++) {
    		print_board(board);

			//roll dice: part A of game play 
    		diceRoll = rand() % 6 + 1;

			for (int j = 0; j < NUM_COLUMNS; j++)
				columnChoice[j] = 0;
			
			for (int j = 0; j < NUM_ROWS; j++)
				for (int k = 0; k <NUM_COLUMNS; k++)
					sideChoice[j][k] = 0;

    		printf("Player %d, %s, your dice roll is %d.\n", i + 1, players[i].name, diceRoll);

			//part B of gameplay: optional sideways move
			do {
				printf("1. Move a token sideways\n");
				printf("2. Pass sideways move.\n");
				printf("Enter choice: ");
				scanf("%d", &op);	
				printf("\n");
			} while (op != 1 && op != 2);

			if (op == 2) {
				printf("Sideways move passed!\n");
			}
			else {
				printf("Move a token sideways!");
				printf("\nPossible squares: ");
				for (int j = 0; j < NUM_ROWS; j++) {
					for(int k = 0; k < NUM_COLUMNS; k++) {
						if (board[j][k].stack != NULL &&
							board[j][k].stack->col == players[i].col && 
							(board[j][k].type == NORMAL || !blocked(board, j))) {
							printf("\n(%d, %d)", j + 1, k + 1);
							sideChoice[j][k] = 1;
						}
					}
				}
				do {
					printf("\nChoose row: ");
					scanf("%d", &sideRow);
					printf("Choose column: ");
					scanf("%d", &sideCol);
					printf("\n");
				} while (sideChoice[sideRow-1][sideCol-1] == 0);

				if (sideRow != 1 && sideRow != NUM_ROWS) {
					do {
						printf("Enter U to move up, D to move down: ");
						scanf(" %c", &upDown);
					} while(upDown != 'U' && upDown != 'D' && upDown != 'u' && upDown != 'd');
				}
				else if (sideRow == 1)
					upDown = 'd';
				else if (sideRow == NUM_ROWS)
					upDown = 'u';
				

				if (upDown == 'D' || upDown == 'd') {
					push(&board[sideRow][sideCol-1].stack, players[i].col);
					board[sideRow][sideCol-1].numTokens++;

					pop(&board[sideRow-1][sideCol-1].stack);
					board[sideRow-1][sideCol-1].numTokens--;

					print_board(board);
					printf("Token moved down to square (%d, %d)!\n", sideRow + 1, sideCol);
				}
				else {
					push(&board[sideRow-2][sideCol-1].stack, players[i].col);
					board[sideRow-2][sideCol-1].numTokens++;

					pop(&board[sideRow-1][sideCol-1].stack);
					board[sideRow-1][sideCol-1].numTokens--;

					print_board(board);
					printf("Token moved up to square (%d, %d)!\n", sideRow - 1, sideCol);
				}
			}

			//part C of game play: move forward in diceRoll row

			if (emptyRow(board, diceRoll-1)) {
				printf("There are no movable tokens in row %d!\n", diceRoll);
			}
			else {
				//choose a token in row (diceRoll) to move forward
				printf("\nMove a token forward in row %d", diceRoll);
				printf("\nColumns from which a token can move forward: ");
				for (int j = 0; j < NUM_COLUMNS; j++) {
					if (board[diceRoll-1][j].stack != NULL && 
						(board[diceRoll-1][j].type == NORMAL || !blocked(board, diceRoll-1))) {
						printf("%d ", j + 1);
						columnChoice[j] = 1;
					}
				}
				do {
					printf("\nChoose which token to move forward in row %d: ", diceRoll);
					scanf("%d", &forwardChoice);
				} while (columnChoice[forwardChoice-1] == 0);

				push(&board[diceRoll-1][forwardChoice].stack, board[diceRoll-1][forwardChoice-1].stack->col);
      			board[diceRoll-1][forwardChoice].numTokens++;
				
				pop(&board[diceRoll-1][forwardChoice-1].stack);
				board[diceRoll-1][forwardChoice-1].numTokens--;

				print_board(board);
				printf("\nToken moved forward in row %d!\n", diceRoll);
			}
  		}
	}
}

//returns true if a row is empty or all tokens in row are in a deep pit
bool emptyRow(square board[NUM_ROWS][NUM_COLUMNS], int row) {
	for (int j = 0; j < NUM_COLUMNS; j++) {
		if (board[row][j].stack != NULL && !blocked(board, row))
			return false;
	}
	return true;
}

//returns true if all tokens if tokens in a row are blocked
bool blocked(square board[NUM_ROWS][NUM_COLUMNS], int row) {
	//return false if there are any non-empty normal squares (except last column)
	for (int j = 0; j < NUM_COLUMNS - 1; j++) {
		if (board[row][j].type == NORMAL && board[row][j].stack != NULL)
			return false;
	}

	for (int j = 0; j < NUM_COLUMNS - 1; j++) {
		if (board[row][j].type == OBSTACLE && board[row][j].stack != NULL) {
			//checking squares in all rows and columns behind obstacle
			for (int k = 0; k < NUM_ROWS; k++) {
				for (int m = 0; m < j; m++) {
					//return true if there is non-empty square behind obstacle
					if (board[k][m].stack != NULL)
						return true;
				}
			}
		}
	}
	return false;
}

/* 
 * Return true if a player has at least 3 tokens in last column, i.e.
 * the game has been won
 * 
 * Input: players - the array of players
 *        numPlayers - the number of players
 */
bool checkWin(player players[], int numPlayers) {
	//iterate through all the players
  	for (int i = 0; i < numPlayers; i++) {
		//check if we have a winner
    	if (players[i].numTokensLastCol >= 3) {
			printf("\nCONGRATULATIONS!");
			printf("\nPlayer %d, %s has won the game!\n", i + 1, players[i].name);
      		return true;
    	}
  	}
  	return false;
}

/*
 * Place a token on the stack
 * 
 * Input: top - pointer to topmost token pointer on stack
 */
void push(token **top, enum colour col) {
	//allocate memory to temporary pointer
  	token *temp = malloc(sizeof(token));
	//assign player's token colour to temporary pointer
  	temp->col = col;
	//let the temporary pointer point to the top pointer
  	temp->nextPtr = *top;
	//make the new token the topmost in the stack
  	*top = temp;
}

/*
 * Remove a token from the stack
 * 
 * Input: top - pointer to topmost token pointer on stack
 */
void pop(token **top) {
	//if the stack is empty, then exit
  	if (*top == NULL) {
    	return;
  	}
	//make temporary pointer the top pointer
  	token *temp = *top;
	//let topmost pointer point to 2nd topmost pointer
  	*top = (*top)->nextPtr;
	//get rid of the temporary pointer
  	free(temp);
}
