/* * lab_5.h
 *
 * * Author: Todd Branchflower *
 *  * This is shell code for the game to be implemented in Lab 4.  It provides basic functions that may prove useful in accomplishing the lab. */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ROW_MASK 0x40
unsigned char initPlayer();
void printPlayer(unsigned char player);//// Prints the player marker (*) at the player location passed in.//
void clearPlayer(unsigned char player);//// Clears the location passed in.
char player;
char gameWon=0;
char count=0;
unsigned char movePlayer(unsigned char player, unsigned char direction);//// Given a player's current position and a direction, returns an updated player position.//
char stringGameWon[]="Game Won!";
char stringGameLost[]="Game Over";
char didPlayerWin(unsigned char player);//// Returns true if the position passed in is the winning game position.//
char button_Was_Pushed=0;
void init_timer();
void init_buttons();
char game_Still_On =1;
char timed_Out =0;
char button_Pushed_Direction;
char timer_Interrupted =0;
char total_Timer_Interrupts =0;
char gameWon;
