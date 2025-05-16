#ifndef settings_h
#define settings_h

#pragma region CONSTRAIN DEFINES
  #define P1_INITIAL 25
  #define P1_MIN 1
  #define P1_MAX 50

  #define T_INITIAL 100
  #define T_MIN 1
  #define T_MAX 200

  #define P2_INITIAL 50
  #define P2_MIN 1
  #define P2_MAX 50

  #define S_INITIAL 1000
  #define S_MIN 200
  #define S_MAX 2000

  #define BACKLIGHT_MIN 0
  #define BACKLIGHT_MAX 5
#pragma endregion

#pragma region GATE VOLTAGE DEFINES
  #define PIN_VGATE A1
  #define GATE_ADC_MIN 573 // ~ <10.1V (2.80v raw)
  #define GATE_ADC_MAX 853 // ~ >15.01v (4.17v raw)
  #define GATE_VOLTAGE_DIVIDER_RATIO 3.6 // 18v/5v = 3.6
  //used in main.cpp uint16_t VGateRaw; 
#pragma endregion

//BATTERY VOLTAGE DEFINES
  #define PIN_VBAT A0 //used in main.cpp uint16_t VBatRaw;

#endif