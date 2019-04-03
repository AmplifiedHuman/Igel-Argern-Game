#include <stdio.h>
#include "game_logic.h"
/*
 * main function to initialise board, players, place tokens and play game
 */
int main(void) {
    //seeding the random number generator
    srand(time(NULL));
    
    //the board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];

    //an array containing the players (MAX 6 players)
    player players[6];

    //the number of players
    int numPlayers = 0;

    //creates the squares of the board
    initialise_board(board);

    //prints the board
    print_board(board);

    //creates the players
    numPlayers = initialise_players(players);

    /*asks each player to place their tokens
    on the first column of the board*/
    place_tokens(board, players, numPlayers);

    //manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);

    return 0;
}
