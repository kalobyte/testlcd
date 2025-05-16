#ifndef gui_h
#define gui_h

#include <Arduino.h>
#include <LCD.h>

#define LCD_RS     7
#define LCD_ENABLE 6
#define LCD_D4     2
#define LCD_D5     3
#define LCD_D6     4
#define LCD_D7     5

LCD lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*
setup
lcd.begin(LCD_ROWS, LCD_COLUMNS);
lcd.create(0, rightArrow); загрузка своих символов в банк 0

loop
lcd.cls(); // очистить экран
lcd.print("hello world");
lcd.printf("hello world %f", data);
lcd.character(2, 1, 0); // показать свои символы  из озу
lcd.display(CURSOR_ON);
lcd.display(BLINK_ON); // мигание курсора
lcd.display(BLINK_OFF);
lcd.display(CURSOR_OFF);
lcd.locate(1, 1); // установка курсора столбец, строка
lcd.clp(1, 1, 3); // очистить 3 знакоместа с позиции 1,1
*/

/*
   printf ("Characters: %c %c \n", 'a', 65);
   printf ("Decimals: %d %ld\n", 1977, 650000L);
   printf ("Preceding with blanks: %10d \n", 1977);
   printf ("Preceding with zeros: %010d \n", 1977);
   printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
   printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
   printf ("Width trick: %*d \n", 5, 10);
   printf ("%s \n", "A string");

   Characters: a A
Decimals: 1977 650000
Preceding with blanks:       1977
Preceding with zeros: 0000001977
Some different radices: 100 64 144 0x64 0144
floats: 3.14 +3e+000 3.141600E+000
Width trick:    10
A string
*/

void printGUI(void); // прототип функции, чтобы GTimerCb8 видела как callback

#endif