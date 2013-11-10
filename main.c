#include <msp430.h>
#include "lab_5.h"
#include "LCD.h"
unsigned char player;
unsigned char gameWon=0;
unsigned char count;
unsigned char game_Still_On =1;
unsigned char timed_Out =0;
unsigned char button_Pushed_Direction;
unsigned char timer_Interrupted =0x00;
unsigned char total_Timer_Interrupts =0x00;
unsigned char gameWon;
unsigned char button_Was_Pushed=0x00;
unsigned char stringGameWon[]="You Won!";
unsigned char stringGameLost[]="You lost";




int main(void){
	WDTCTL = (WDTPW|WDTHOLD);

		player = initPlayer();

		init_timer();

		init_buttons();

        __enable_interrupt();

        initSPI();

        LCDinit();

        LCDclear();

        printPlayer(player);



while(1)        {
		if (timer_Interrupted){
						 timer_Interrupted=0;
			 			 total_Timer_Interrupts++;
			 			 if(total_Timer_Interrupts>=8){
			 				 timed_Out=1;
			 				 timer_Interrupted=0;
			 			 }
			 		 }

		 if (timed_Out){
			 LCDclear();
			 total_Timer_Interrupts=0;
			 count=0;
			 timed_Out=0;
			 player=initPlayer();
			 button_Was_Pushed=0;
			 cursorToLineOne();
			 while(count<8){
				 writeDataByte(stringGameLost[count]);
				 count++;
				 }
			 while (!button_Was_Pushed){
				 //burn power and wait for button push

			 }
			 LCDclear();
			 printPlayer(player);
			 button_Was_Pushed=0;
		 }







	     if (button_Was_Pushed){
	    	 LCDclear();
	    	 total_Timer_Interrupts=0;
	    	 button_Was_Pushed=0;

	    	 if(!checkBounds(player)){
	    		 if( button_Pushed_Direction==UP){
	    			 player+=64;
	    		 }
	    		 if( button_Pushed_Direction==DOWN){
	    			    			 player-=64;
	    			    		 }
	    		 if( button_Pushed_Direction==RIGHT){
	    			    			 player-=1;
	    			    		 }
	    		 if( button_Pushed_Direction==LEFT){
	    			    			 player+=1;
	    			    		 }











	    		 printPlayer(player);
	    	 }
	    	 else{


	    	 if (didPlayerWin(player)){
	    	 		 gameWon=1;
	    	 	 }
	    	 else{
	    	 		 player=movePlayer(player, button_Pushed_Direction);
	    	 		 printPlayer(player);

	    	 	 }
	    	 if (gameWon){
	    	 		 LCDclear();
	    	 		 count=9;
	    	 		 player=initPlayer();
	    	 		 button_Was_Pushed=0;
	    	 		 gameWon=0;
	    	 		 while(count){
	    	 			writeDataByte(stringGameWon[9-count]);
	    	 			count--;
	    	    	    	 	 }
	    	 		while(!button_Was_Pushed){
	    	 			    	 				//burn power and wait for button push
	    	 			    	 			}




	     }
	    	 }

}

	}
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
		 timer_Interrupted = 1;
		 TACTL &= ~TAIFG;

}
//documentation on this part: I got this (the idea and method) from C2C Payden McBee (he is in my squad and is the go to guy if I have problems)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void)
{
		if(P1IFG & BIT1)
		{
			P1IFG &= ~BIT1; // clear the flag set when the button for right was pushed
			if(BIT1 & P1IES)
			{
				 button_Pushed_Direction=UP;
				 button_Was_Pushed=1;

			}
			else
			{
				delay1(); //debounce
			}
			// part below is in case a button is pushed that isn't one of the four.
			P1IES ^= BIT1;
			P1IFG &= ~BIT1;
		}
		if(P1IFG & BIT2)
		{
			P1IFG &= ~BIT2; 			// clear flag

			if(BIT2 & P1IES)
			{

				button_Pushed_Direction=DOWN;
				button_Was_Pushed=1;
			}
			else
			{
				delay2(); //debounce
			}
			P1IES ^= BIT2;
			P1IFG &= ~BIT2;
		}
		if(P1IFG & BIT4)
		{
			P1IFG &= ~BIT4;
			if(BIT4& P1IES)
			{
				button_Was_Pushed=1;
				button_Pushed_Direction=RIGHT;
			}
			else
			{
					delay2();
			}
		P1IES ^= BIT4;
		P1IFG &= ~BIT4;

		}
		if(P1IFG & BIT0)
				{
					P1IFG &= ~BIT0; 			// clear flag

					if(BIT0 & P1IES)
					{

						button_Pushed_Direction=LEFT;
						button_Was_Pushed=1;
					}
					else
					{
						delay2(); //debounce
					}
					P1IES ^= BIT0;
					P1IFG &= ~BIT0;
				}

}
