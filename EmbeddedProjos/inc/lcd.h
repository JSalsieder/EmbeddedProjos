/*
 * lcd.h
 *
 *  Created on: Dec 18, 2016
 *      Author: salsiederja
 */

#ifndef LCD_H_
#define LCD_H_
#include "defines.h"





// methods

/*
 * initialize the lcd with 2 rows, 16 columns
 * and set the cursor to 0,0
 */
void lcd_begin();

/*
 * move the cursor to 0,0
 */
void lcd_home();

/*
 * remove all characters from the display and
 * return the cursor to 0,0
 */
void lcd_clear();

/*
 * moves the cursor to the row, column
 */
void lcd_cursorAt(int row, int col);

/*
 * display the cursor
 */
void lcd_cursor();

/*
 * do not show the cursor
 */
void lcd_noCursor();

/*
 * show a blinking cursor
 */
void lcd_blink();

/*
 * do not show the blinking cursor
 */
void lcd_noBlink();

/*
 * enable the display
 */
void lcd_display();

/*
 * disable the display
 */
void lcd_noDisplay();

/*
 * print a string by reference to the string's location
 */
void lcd_print(char *string);

/*
 * write a single char by writing the char at the lcd's ROM in address CCG_address
 */
void lcd_write(char ascii);

/*
 * write characters from Left to Right
 */
void lcd_LTR();

/*
 * write characters from Right to Left
 */
void lcd_RTL();

/*
 * returns 1 if the busy flag is set else 0
 */
int lcd_isBusy();


#endif /* LCD_H_ */
