/* * lab_5.h
 *
 * * Author: C1C Ethan Snyder
 *  * This is shell code for the game to be implemented in Lab 4.  It includes the functions, constants, and universal variables used in lab 5 */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ROW_MASK 0x40
char player;
char gameWon=0;
char count=0;
char game_Still_On =1;
char timed_Out =0;
char button_Pushed_Direction;
char timer_Interrupted =0;
char total_Timer_Interrupts =0;
char gameWon;
char button_Was_Pushed=0;
char stringGameWon[]="Game Won!";
char stringGameLost[]="Game Over";
unsigned char movePlayer(unsigned char player, unsigned char direction);//// Given a player's current position and a direction, returns an updated player position.//
char didPlayerWin(unsigned char player);//// Returns true if the position passed in is the winning game position.//
void printPlayer(unsigned char player);//// Prints the player marker (*) at the player location passed in.//
void clearPlayer(unsigned char player);//// Clears the location passed in.
void init_timer();
void init_buttons();
unsigned char initPlayer();
char checkBounds(char player);
