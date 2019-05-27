# Igel Ärgern 
#### COMP10050 Software Engineering Project 1, Assignment 2
> C implementation of the German board game Igel Ärgern, whose name loosely translates to "Hedgehogs in a Hurry".

## About The Game
The standard game is played by 2-6 players on a board with 6 rows and 9 columns. Each player has four tokens (representing hedgehogs) that he or she must move from the left column to the right column. Tokens sharing a square are stacked on top of each other. Only the token on the top of a stack may move.

On their turn, a player:
1. rolls the dice,
2. optionally moves one of their tokens up or down one row (we call this a "sideways" move, because the token is moved sideways relative to the direction of travel toward the finish line), and
3. chooses one token (either their own or another player's) in the row indicated by the dice roll and moves it one space to the right (i.e., "forward").

A token that falls into an obstacle square is stuck there until every other token has caught up (i.e. no token is placed in a column on the left of the obstacle in any row). 

The winner of the game is the player who can move three of their tokens to the last column of the board.
Detailed Rules: [boardgamegeek.com](https://boardgamegeek.com/boardgame/95/igel-argern)

## Getting Started
__Windows Users__  
```Download and run igelArgern.exe ```
## Authors
* [Jason Tee](https://github.com/AmplifiedHuman)
* [Rajit Banerjee](https://github.com/rajitbanerjee)

#### Grade Received
A+
