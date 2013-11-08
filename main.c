#include <msp430.h>
#include "lab_5.h"
#include "LCD.h"
void init_timer();
void init_buttons();

int main(void){
	WDTCTL = (WDTPW|WDTHOLD);
unsigned char player = initPlayer();

init_timer();

init_buttons();

__enable_interrupt();




while(1)        {
	/*                 *
	 *
	 *  while (game is on)                 *
	 *   {                 *                 check if button is pushed (you don't want to block here, so don't poll!)                 *
	 *   if button is pushed:                 *
	 *    clear current player marker                 *
	 *    update player position based on direction                 *
	 *    print new player                 *
	 *    clear two second timer                 *
	 *    wait for button release (you can poll here)                 * }                 *
	 *    * print game over or you won, depending on game result                 *                 *
	 *    wait for button press to begin new game (you can poll here)                 *
	 *    wait for release before starting again                 */
	}        return 0;}
// // YOUR TIMER A ISR GOES HERE//
void init_timer(){
		 TACTL &= ~(MC1|MC0);  // stop timer

		 TACTL |= TASSEL1;    // clear TAR

		 TACTL |= TASSEL1;    // configure for SMCLK

		 TACTL |= ID1|ID0;    // divide clock by 8

		 TACTL &= ~TAIFG;

		 TACTL |= MC1;        // set timer mode to continuous

		 TACTL |= TAIE;       // enable interrupt

void init_buttons(){
	   	 P1DIR &= ~(BIT1|BIT2|BIT3|BIT4);  // set buttons 1-4 to inputs for reading later

	   	 P1IE |= BIT1|BIT2|BIT3|BIT4;      // turn on the interrupts for the buttons (will just trigger 1 interrupt)

	   	 P1IES |= BIT1|BIT2|BIT3|BIT4;     // falling edge configuration

	   	 P1REN |= BIT1|BIT2|BIT3|BIT4;     // set buttons to pull up/pull down resistors

	   	 P1OUT |= BIT1|BIT2|BIT3|BIT4;     // since resistors are enabled as pull up or pull down, set them as pull up.

	   	 P1IFG &=~(BIT1|BIT2|BIT3|BIT4);   // clear flags for buttons 1-4

}
}
