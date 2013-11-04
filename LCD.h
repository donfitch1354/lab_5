//
// lcd.h
// Author: Ethan Snyder
// Date: 21 October 2013
// Description: Library to interact with the Geek Box LCD. Pulled from Capt Branchflowers code
#define RS_MASK 0x40



void initSPI(); // done
void LCDinit(); // done
void LCDclear(); // done
void cursorToLineTwo(); // kinda done
void cursorToLineOne(); // kinda done
void writeDataByte(char dataByte); // done
void writeCommandNibble(char commandNibble); // done
void writeCommandByte(char commandByte); // done
void delay1(); // done
void delay2(); // done
void LCD_write_8(char byteToSend); // done
void SPI_send(char byteToSend); // done
void LCD_write_4(char byteToSend); // done
void set_SS_hi();
void set_SS_lo();
void super_Delay();


