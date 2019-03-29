#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printLine();

/*
* Returns the first letter associated with the color of the token
*
* Input: t - pointer to a token
* Output: initial of the color of the token
*/
char print_token(token *t) {
  if ((*t).col== PINK) return 'P';
  if ((*t).col== RED) return 'R';
  if ((*t).col== BLUE) return 'B';
  if ((*t).col== GREEN) return 'G';
  if ((*t).col== ORANGE) return 'O';
  if ((*t).col== YELLOW) return 'Y';
  return '\0';
}

/*
* Prints the board
*
* Input: the board to be printed.
*/
void print_board(square board[NUM_ROWS][NUM_COLUMNS]) {
  printf("                THE BOARD\n");
  for (int i = 0; i < NUM_ROWS; i++) {
    //prints an horizontal line
    printLine();
    //prints the row number
    printf(" %d ", i);
    char c = '\0' ;
    //if the square (i,j) is occupied,
    //c is assigned the initial of the color of the token that occupies the square
    for (int j = 0; j < NUM_COLUMNS; j++) {
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
  printf("     0   1   2   3   4   5   6   7   8\n");
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
  bool isValidInput = false;
  int flag = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < numPlayers; j++) {
      isValidInput = false;
      while (!isValidInput) {
        printf("Player %d, %s please select a square (0-5):", j + 1, players[j].name);
        fflush(stdout);
        flag = scanf("%d", &selectedSquare);
        if (flag != 1 || selectedSquare < 0 || selectedSquare > 5) {
          printf("Input must be in range (0 - 5).\n");
        } else if ((board[selectedSquare][0].stack != NULL) && (board[selectedSquare][0].stack->col == players[j].col)) {
          printf("Token can't be placed on the square with the same colour.\n");
        } else if (board[selectedSquare][0].numTokens != minNumOfTokens) {
          printf("Token must be placed on the lowest stack.\n");
        } else {
          isValidInput = true;
        }

        while (getchar() != '\n'); //removes invalid input from buffer
        puts("");
      }

      board[selectedSquare][0].stack = (token *)malloc(sizeof(token));
      board[selectedSquare][0].stack->col = players[j].col;
      board[selectedSquare][0].numTokens++;
      //need some time to understand, write formula on paper, very smart
      //basically find the min number of tokens at each iteration/rpund
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
  //TO BE IMPLEMENTED
}
