
#include "gui.h"
#include <LCD.h>

extern LCD lcd;
extern struct menu
{
  uint8_t P1; //value 1-50 millisec
  uint8_t T; // value millisec
  uint8_t P2; //value 1-50 millisec
  uint16_t S; // value 1-1000 millisec
  bool isAutoMode; // режим ручной/авто
  int8_t backlight; // яркость шаги 0-5, !знаковый signed!
  uint16_t VBat;
  uint16_t VGate;
} params;

extern uint8_t arrowPos; // позиция стрелки меню (со знаком минус! signed int)
extern bool isItemEdit;

void printGUI(LCD *lcd) // функция вызывается автоматические каждые 300мс
{ 
  // строки левой колонки
  lcd->locate(1,2);  lcd->printf("P1: %2d ms", params.P1);
  lcd->locate(2,2);  lcd->printf("T: %3d ms", params.T);
  lcd->locate(3,2);  lcd->printf("P2:%3d ms", params.P2);
  lcd->locate(4,2);  lcd->printf("S:%4d ms", params.S);

  // строки правой колонки
  lcd->locate(1,13);  lcd->printf("BL:    %d", params.backlight);
  lcd->locate(2,13);  lcd->print(F("Mode:"));  params.isAutoMode ? lcd->character(2,20,'A'):lcd->character(2,20,'M');
  lcd->locate(3,13);  lcd->printf("Bat %1d.%1d", params.VBat/10, params.VBat%10);
  lcd->locate(4,13);  lcd->printf("Drv %2d.%1d", params.VGate/100, (params.VGate+5) %100/10);
   
   
  // выводим стрелку
  switch (arrowPos)
  {
    case 0: lcd->locate(1, 1);  break;
    case 1: lcd->locate(2, 1);  break;
    case 2: lcd->locate(3, 1);  break;
    case 3: lcd->locate(4, 1);  break;
    case 4: lcd->locate(1, 12); break;
    case 5: lcd->locate(2, 12); break;
  }
  lcd->write(isItemEdit ? 62 : 126);
  // идея реализации позиции стрелки на любых координатах черезма массив структуры координат х,у + строку меню
  // где индекс массива будет равен количеству пунктов меню
}