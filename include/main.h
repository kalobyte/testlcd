#ifndef main_h
#define main_h
#include <Arduino.h>

#pragma region ENCODER
    // https://github.com/GyverLibs/EncButton/tree/main
    #define CLK 13
    #define DT 12
    #define SW 8

    #define EB_NO_FOR           // отключить поддержку pressFor/holdFor/stepFor и счётчик степов (экономит 2 байта оперативки)
    #define EB_NO_CALLBACK      // отключить обработчик событий attach (экономит 2 байта оперативки)
    #define EB_NO_COUNTER       // отключить счётчик энкодера (экономит 4 байта оперативки)
    #define EB_NO_BUFFER        // отключить буферизацию энкодера (экономит 1 байт оперативки)
    #define EB_DEB_TIME 50     // таймаут гашения дребезга кнопки (кнопка)
    #define EB_CLICK_TIME 500  // таймаут ожидания кликов (кнопка)
    //#define EB_HOLD_TIME 600   // таймаут удержания (кнопка)
    #define EB_STEP_TIME 200   // таймаут импульсного удержания (кнопка)
    #define EB_FAST_TIME 30    // таймаут быстрого поворота (энкодер)
    #define EB_TOUT_TIME 1000  // таймаут действия (кнопка и энкодер)
    #include <EncButton.h> //!!подключение после дефайнов!!
    EncButtonT<DT, CLK, SW> encoder;
#pragma endregion
#include <LCD.h>
#define LCD_RS     7
#define LCD_ENABLE 6
#define LCD_D4     2
#define LCD_D5     3
#define LCD_D6     4
#define LCD_D7     5
LCD lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void allTicks(void);
void setBacklight(void);
void startBanner(void);
void gateError(void);
void Inits(void);
void printGUI(void);


#pragma region Display Update Timer
    #include <GTimer.h>
    GTimerCb8<millis> displayTimer(254, printGUI, GTMode::Interval, false);
 #pragma endregion

// из библиотеки EncButton.h
Button btnPedal; //педаль с подтяжкой к питанию (активный при замыкании на землю)
Button btnElectrodes; // подключить к истокам + резистор на землю 100ом (активный при замыкании на +5в)

#define BACKLIGHT_PIN 11 //вывод подсветки
#define PIN_BUZZER 10 

/*
    // установить таймаут ожидания кликов, умолч. 500 (макс. 4000 мс)
    void setClickTimeout(const uint16_t tout) 

        // установить таймаут импульсного удержания, умолч. 200 (макс. 4000 мс)
    void setStepTimeout(const uint16_t tout) 

        // установить таймаут удержания, умолч. 600 (макс. 4000 мс)
    void setHoldTimeout(const uint16_t tout) 

        // установить время таймаута, умолч. 1000 (макс. 4000 мс)
    void setTimeout(const uint16_t tout) 

        // кнопка была удержана (больше таймаута) [событие]
    bool hold() 
*/
#endif