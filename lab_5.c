#include "lab_5.h"
#include "LCD.h"
#include <msp430.h>

unsigned char initPlayer(){
	return 0x80;
}


char checkBounds(char player){
	if (player<=0xC7 && player >=0xC0){

		return 1;
	}
	if (player>=80 && player <= 87){
		return 1;
	}
	else return 0;



}






void printPlayer(unsigned char player){
	writeCommandByte(player);
	writeDataByte('*');
}


void clearPlayer(unsigned char player){
	writeCommandByte(player);
	writeDataByte(' ');
}


unsigned char movePlayer(unsigned char player, unsigned char direction){
	 {
	               if(direction==1){
	            	   player += 40;
	       	               }

	               if (direction ==2){
	            	   player-=40;
	               }
	               if (direction == 3){
	            	   player -=1;
	               }
	               if (direction ==4){
	            	   player +=1;
	               }
	}        return player;
}


char didPlayerWin(unsigned char player)
	{
	return player == 0xC7;}

void init_timer(){
		 TACTL &= ~(MC1|MC0);  // stop timer

		 TACTL |= TASSEL1;    // clear TAR

		 TACTL |= TASSEL1;    // configure for SMCLK

		 TACTL |= ID1|ID0;    // divide clock by 8

		 TACTL &= ~TAIFG;

		 TACTL |= MC1;        // set timer mode to continuous

		 TACTL |= TAIE;       // enable interrupt
}
void init_buttons(){
	   	 P1DIR &= ~(BIT1|BIT2|BIT4);  // set buttons 1-4 to inputs for reading later

	   	 P1IE |= BIT1|BIT2|BIT4;      // turn on the interrupts for the buttons (will just trigger 1 interrupt)

	   	 P1IES |= BIT1|BIT2|BIT4;     // falling edge configuration

	   	 P1REN |= BIT1|BIT2|BIT4;     // set buttons to pull up/pull down resistors

	   	 P1OUT |= BIT1|BIT2|BIT4;     // since resistors are enabled as pull up or pull down, set them as pull up.

	   	 P1IFG &=~(BIT1|BIT2|BIT4);   // clear flags for buttons 1-4

}

