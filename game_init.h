
//number of rows of the board
#define NUM_ROWS 6
//number of columns of the board
#define NUM_COLUMNS 9


//types of squares
enum stype {NORMAL, OBSTACLE};
//colors of tokens
enum colour {RED, BLUE, GREEN, YELLOW, PINK, ORANGE};

//defines a token.
//Note each token can be associated with a color
typedef struct token {
	enum colour col;
} token;

//Defines a square of the board.
typedef struct square {
	//A square can be a NORMAL or an OBSTACLE square
  	enum stype type;
  	//the stack of tokens that can be placed on the board square
  	token *stack;
} square;



/*
 * You need to fill this data structure
 * with the information about the player
 * such as a name and a color.
 */
typedef struct player {
	char name [80];
	enum colour col;
} player;


/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
void initialise_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 *
 */
int initialise_players(player players[]);
