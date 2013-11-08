/* * lab_5.h
 *
 * * Author: Todd Branchflower *
 *  * This is shell code for the game to be implemented in Lab 4.  It provides basic functions that may prove useful in accomplishing the lab. */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ROW_MASK 0x40
unsigned char initPlayer();//// Prints the player marker (*) at the player location passed in.//
void printPlayer(unsigned char player);//// Clears the location passed in.//
void clearPlayer(unsigned char player);//// Given a player's current position and a direction, returns an updated player position.//
unsigned char movePlayer(unsigned char player, unsigned char direction);//// Returns true if the position passed in is the winning game position.//
char didPlayerWin(unsigned char player);
void init_timer();
void init_buttons();
char game_Still_On =1;
char button_Was_Pushed =0;
char button_Pushed_Direction;
char timer_Interrupted =0;
