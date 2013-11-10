#include "lab_5.h"
#include "LCD.h"
#include <msp430.h>

/////////////////////////////////////////////////////
//Function Name: initPlayer()
//Author: C1C Ethan Snyder, USAF
//Function: initializes any variable that is set equal to the function to 0x80 (first place on the geek box);
//Inputs:none
//Returns: unsigned char
//Functions Used: none;
////////////////////////////////////////////////////

unsigned char initPlayer(){
	return 0x80;
}

/////////////////////////////////////////////////////
//Function Name: checkBounds()
//Author: C1C Ethan Snyder, USAF
//Function: checks current player location to see if it is still in bounds on the LCD screen
//Inputs:char
//Returns: char
//Functions Used: none
////////////////////////////////////////////////////
char checkBounds(char player){

	if((player<=0xC7 && player>=0xC0)||(player<=0x87 && player>=0x80)){
		return 1;
	}






	else {
		return 0;
	}



}
/////////////////////////////////////////////////////
//Function Name: printPlayer()
//Author: C1C Ethan Snyder, USAF
//Function: prints player (based off of location) to LCD screen
//Inputs:char player
//Returns: none
//Functions Used: none
////////////////////////////////////////////////////
void printPlayer(unsigned char player){
	writeCommandByte(player);
	writeDataByte('*');
}

/////////////////////////////////////////////////////
//Function Name: clearPlayer()
//Author: C1C Ethan Snyder, USAF
//Function: removes player from screen, i never used this but left it here in case I ever needed it
//Inputs:char player
//Returns: none
//Functions Used:none
////////////////////////////////////////////////////
void clearPlayer(unsigned char player){
	writeCommandByte(player);
	writeDataByte(' ');
}

/////////////////////////////////////////////////////
//Function Name: movePlayer()
//Author: C1C Ethan Snyder, USAF
//Function: increments char player based on button pushed
//Inputs:char player, unsigned char direction
//Returns: modified char player
//Functions Used:none
////////////////////////////////////////////////////

unsigned char movePlayer(unsigned char player, unsigned char direction){
	 {
	               if(direction==1){
	            	   player -= 64;
	       	               }

	               if (direction ==2){
	            	   player+=64;
	               }
	               if (direction == 3){
	            	   player -=1;
	               }
	               if (direction ==4){
	            	   player +=1;
	               }
	}        return player;
}


/////////////////////////////////////////////////////
//Function Name: didPlayerWin()
//Author: C1C Ethan Snyder, USAF
//Function: checks to see if player won
//Inputs:player
//Returns: char
//Functions Used:none
////////////////////////////////////////////////////
char didPlayerWin(unsigned char player)
	{
	return (player == 0xC7);
	}
/////////////////////////////////////////////////////
//Function Name: init_timer()
//Author: C1C Ethan Snyder, USAF
//Function: initializes timer
//Inputs:none
//Returns: none
//Functions Used: none
////////////////////////////////////////////////////
void init_timer(){
		 TACTL &= ~(MC1|MC0);  // stop timer

		 TACTL |= TACLR;    // clear TAR

		 TACTL |= TASSEL1;    // configure for SMCLK

		 TACTL |= ID1|ID0;    // divide clock by 8

		 TACTL &= ~TAIFG;

		 TACTL |= MC1;        // set timer mode to continuous

		 TACTL |= TAIE;       // enable interrupt
}
/////////////////////////////////////////////////////
//Function Name: init_buttons()
//Author: C1C Ethan Snyder, USAF
//Function: initializes the pins on the MSP340 so they can read in button pushes
//Inputs:none
//Returns: none
//Functions Used: none
////////////////////////////////////////////////////
void init_buttons(){
	   	 P1DIR &= ~(BIT0|BIT1|BIT2|BIT4);  // set buttons 1-4 to inputs for reading later

	   	 P1IE |= BIT0|BIT1|BIT2|BIT4;      // turn on the interrupts for the buttons (will just trigger 1 interrupt)

	   	 P1IES |= BIT0|BIT1|BIT2|BIT4;     // falling edge configuration

	   	 P1REN |= BIT0|BIT1|BIT2|BIT4;     // set buttons to pull up/pull down resistors

	   	 P1OUT |= BIT0|BIT1|BIT2|BIT4;     // since resistors are enabled as pull up or pull down, set them as pull up.

	   	 P1IFG &=~(BIT0|BIT1|BIT2|BIT4);   // clear flags for buttons 1-4

}

