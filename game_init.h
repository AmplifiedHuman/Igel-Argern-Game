//number of rows of the board
#define NUM_ROWS 6
//number of columns of the board
#define NUM_COLUMNS 9

//types of squares
enum stype { NORMAL, OBSTACLE };
//colours of tokens
enum colour { RED, BLUE, GREEN, YELLOW, PINK, ORANGE };

//defines a token
typedef struct token {
	//each token can be associated with a colour
	enum colour col;
} token;

//defines a square of the board
typedef struct square {
	//a square can be a NORMAL or an OBSTACLE square
  	enum stype type;
  	//the stack of tokens that can be placed on the board square
  	token *stack;
} square;

//defines a player 
typedef struct player {
	char name [70];
	//each player has tokens of a particular colour
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
