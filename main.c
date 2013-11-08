#include <msp430.h>
#include "lab_5.h"
#include "LCD.h"



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
		 if (timer_Interrupted==1){
			 total_Timer_Interrupts++;
			 if(total_Timer_Interrupts==8){
				 timed_Out=1;
			 }
		 }
		 if (timed_Out){
			 LCDclear();
			 total_Timer_Interrupts=0;
			 count=9;
			 timed_Out=0;
			 player=initPlayer();
			 button_Was_Pushed=0;
			 while(count){
				 writeDataByte(stringGameLost[count]);
				 count--;
				 }
			 while (!button_Was_Pushed){
				 //burn power and wait for button push
			 }
			 printPlayer(player);
			 button_Was_Pushed=0;
		 }







	     if (button_Was_Pushed){
	    	 if(!checkBounds(player)){
	    		 player=initPlayer(); // you went out of bounds... go directly to jail and do not pass go (restarts game position as penalty for running out)
	    	 }
	    	 else{

	    	 LCDclear();
	    	 total_Timer_Interrupts=0;
	    	 button_Was_Pushed=0;

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
	    	 			writeDataByte(stringGameWon[count]);
	    	 			count--;
	    	    	    	 	 }
	    	 		while(!button_Was_Pushed){
	    	 			    	 				//burn power and wait for button push
	    	 			    	 			}


	    	 		printPlayer(player);
	    	 		button_Was_Pushed=0;

	     }
	    	 }

}

	}
}


__interrupt void TIMER0_A1_ISR(void)
{ 		 timer_Interrupted = 1;
		 TACTL &= ~TAIFG;

}
//documentation on this part: I got this (the idea and method) from C2C Payden McBee (he is in my squad and is the go to guy if I have problems)
__interrupt void Port_1_ISR(void)
{
		if(P1IFG & BIT1)
		{
			P1IFG &= ~BIT1; // clear the flag set when the button for right was pushed
			if(BIT1 & P1IES)
			{
				 button_Pushed_Direction=RIGHT;
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

				button_Pushed_Direction=LEFT;
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
				button_Pushed_Direction=DOWN;
			}
			else
			{
					delay2();
			}
		P1IES ^= BIT4;
		P1IFG &= ~BIT4;

		}

}
