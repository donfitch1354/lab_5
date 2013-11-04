/*
 * lab4.c
 *
 *  Created on: Oct 27, 2013
 *      Author: C14Ethan.Snyder
 */
#include <msp430.h>
#include "LCD.h"


char LCDCON = 0;

/////////////////////////////////////////////////////
//Function Name: initSPI()
//Author: C1C Ethan Snyder, USAF
//Function: initializes the SPI
//Inputs:none
//Returns: none
//Functions Used: none
////////////////////////////////////////////////////
void initSPI(){


			UCB0CTL1 |= UCSWRST;

			UCB0CTL0  |= UCCKPH|UCMSB|UCMST|UCSYNC;    // don't forget UCSYNC!

			UCB0CTL1 |= UCSSEL1;                        // select a clock to use!

			//UCB0STAT |= UCLISTEN;                       // enables internal loopback

			P1DIR|= BIT3;

			P1SEL |= BIT5;                            // make UCB0CLK available on P1.5
			P1SEL2 |= BIT5;

			P1SEL |= BIT7;                             // make UCB0SSIMO available on P1.7
			P1SEL2 |= BIT7;

			P1SEL |= BIT6;                              // make UCB0SSOMI available on P1.6
			P1SEL2|= BIT6;

			UCB0CTL1 &= ~UCSWRST;                        // enable subsystem
}


void delay1(){
			__delay_cycles(45); //45 millisecond delay


}

void delay2(){
		   __delay_cycles(1900); // 1.65 mS delay

}

/////////////////////////////////////////////////////
//Function Name: LCDinit()
//Author: C1C Ethan Snyder, USAF
//Function: initializes the LCD on the geek box
//Inputs:none
//Returns: none
//Functions Used: delay1();
////////////////////////////////////////////////////

void LCDinit()
{
    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x02);

    writeCommandByte(0x28);

    writeCommandByte(0x0C);

    writeCommandByte(0x01);

    writeCommandByte(0x06);

    writeCommandByte(0x01);

    writeCommandByte(0x02);

    SPI_send(0);
    delay1();
}

/////////////////////////////////////////////////////
//Function Name: LCDclear()
//Author: C1C Ethan Snyder, USAF
//Function: clears lcd
//Inputs:none
//Returns: none
//Functions Used: none
////////////////////////////////////////////////////
void LCDclear()
{
    writeCommandByte(1);
}

/////////////////////////////////////////////////////
//Function Name: wirteCommandNibble()
//Author: C1C Ethan Snyder, USAF
//Function: creates command nibble for each byte sent
//Inputs:LCDCON
//Returns: none
//Functions Used: delay2(), LCD_write_4();
////////////////////////////////////////////////////
void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    delay2();
}
/////////////////////////////////////////////////////
//Function Name: writeCommandByte()
//Author: C1C Ethan Snyder, USAF
//Function: writes command byte
//Inputs:byte for command
//Returns: none
//Functions Used: delay2(), LCD_write_8()
////////////////////////////////////////////////////
void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    delay2();
}

/////////////////////////////////////////////////////
//Function Name: writeDataByte()
//Author: C1C Ethan Snyder, USAF
//Function: writes data byte
//Inputs:byte for data
//Returns: none
//Functions Used: delay2(), LCD_write_8()
////////////////////////////////////////////////////
void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    delay2();
}
/////////////////////////////////////////////////////
//Function Name: LCD_write_8()
//Author: C1C Ethan Snyder, USAF
//Function: sends byte to LCD
//Inputs:byte to send
//Returns: none
//Functions Used: delay2(), LCD_write_4()
////////////////////////////////////////////////////
void LCD_write_8(char byteToSend)
{
    unsigned char sendByte = byteToSend;
    sendByte &= 0xF0;

    sendByte = sendByte >> 4;               // rotate to the right 4 times

    LCD_write_4(sendByte);

    sendByte = byteToSend;

    sendByte &= 0x0F;

    LCD_write_4(sendByte);
}
/////////////////////////////////////////////////////
//Function Name: SPI_send()
//Author: C1C Ethan Snyder, USAF
//Function: times when to send
//Inputs:byte for command
//Returns: none
//Functions Used: delay2(), set_SS_lo()
////////////////////////////////////////////////////
void SPI_send(char byteToSend)
{
    volatile char readByte;

    set_SS_lo();

    UCB0TXBUF = byteToSend;

    while(!(UCB0RXIFG & IFG2))
    {
        // wait until you've received a byte
    }

    readByte = UCB0RXBUF;

    set_SS_hi();
}
/////////////////////////////////////////////////////
//Function Name: cursorToLineTwo()
//Author: C1C Ethan Snyder, USAF
//Function: moves lcd cursor to line 2
//Inputs:none
//Returns: none
//Functions Used: delay1(), writeCommandByte()
////////////////////////////////////////////////////
void cursorToLineTwo(){
	writeCommandByte(0xc0);
}
/////////////////////////////////////////////////////
//Function Name: cursorToLineOne()
//Author: C1C Ethan Snyder, USAF
//Function: moves cursor to line one
//Inputs:none
//Returns: none
//Functions Used: delay1(), writeCommandByte()
////////////////////////////////////////////////////
void cursorToLineOne(){
	writeCommandByte(0x80);
	}

/////////////////////////////////////////////////////
//Function Name: LCD_write_4()
//Author: C1C Ethan Snyder, USAF
//Function: sends a byte in to parts
//Inputs:byte to send
//Returns: none
//Functions Used: delay1(), SPI_send()
////////////////////////////////////////////////////
void LCD_write_4(char byteToSend){
					  //LCDDATA = byteToSend;                                            // load data to send
					  byteToSend &=  0x0f; //                                              ; ensure upper half of byte is clear
	                  byteToSend |=   LCDCON; //                                             ; set LCD control nibble
	                  byteToSend &= 0x7f;                                              // ; set E low
	                  SPI_send(byteToSend);
	                  delay1();
	                  byteToSend |=  0x80; //                                               ; set E high
	                  SPI_send(byteToSend);
	                  delay1();
	                  byteToSend &= 0x7f; //                                               ; set E low
	                  SPI_send(byteToSend);
	                  delay1();
}

/////////////////////////////////////////////////////
//Function Name: set_SS_hi() and set_SS_lo()
//Author: C1C Ethan Snyder, USAF
//Functions: these two set SS high or low
//Inputs:none
//Returns: none
//Functions Used: none
////////////////////////////////////////////////////
void set_SS_hi(){
	P1OUT |= BIT3;
	}

void set_SS_lo(){

	P1OUT &= ~BIT3;

}
void super_Delay(){
	__delay_cycles(100000);


}
