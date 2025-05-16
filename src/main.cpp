#include <Arduino.h>

#include "main.h"
#include "settings.h"
#include "pulse.h" 


#pragma region MENU VARS
struct menu
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
#pragma endregion

int8_t arrowPos = 1; // позиция стрелки меню (со знаком минус! signed int)
bool isItemEdit = false; // false - стрелка выбирает пункты меню, true - пункты редактируются

void setup()
{
  Inits();
  //Serial.begin(115200);
}

void loop()
{  
  // ### SYSTEM VARS ###
  uint16_t VGateRaw; // settings.h GATE VOLTAGE DEFINES
  uint16_t VBatRaw; // settings.h BATTERY VOLTAGE DEFINES
  
  // быстрое сравнение сырых значений, если напряжение затворов вышло за пределы нормы <10v и >15v
  VGateRaw = analogRead(PIN_VGATE); //первым измеряем напряжение затворов
  if (VGateRaw < GATE_ADC_MIN || VGateRaw > GATE_ADC_MAX) gateError(); // gateError() блокирует полностью всю работу
                                                                       
  allTicks();
  VBatRaw = analogRead(PIN_VBAT);
  params.VBat = VBatRaw * 50 / 1023; 
  params.VGate = VGateRaw * 50 / 1023 * 36;

  
  if(btnElectrodes.hold()) // дописать флаг выхода из редактирования
  {
    setPulseSequence(params.P1, params.T, params.P2);
    if (!isPulseRunning()) startPulseSequence();

    // дописать условие ручного-авто режима с педалью
  }

  if (encoder.click()) isItemEdit = !isItemEdit;// смена режима - выбор меню / изменение значений
// TODO переделать turn на tick и перенести click внутрь
  
  if (encoder.turn()) // при любом повороте и при допустимых напряжениях
  {
    lcd.cls(); // очищаем дисплей

    if (encoder.right() && isItemEdit == false)
    {
      arrowPos++;
      if (arrowPos >= 6) arrowPos = 5; // ограничиваем позицию курсора в ОБОИХ режимех
      //if (arrowPos == 1 && params.isAutoMode) arrowPos = 3; // в режиме авто пропустить пункты 1 и 2
    }
    
    if (encoder.left() && isItemEdit == false)
    {
      arrowPos--;
      if (arrowPos <= 0) arrowPos = 0; // ограничиваем позицию курсора в ОБОИХ режимех, signed int, иначе после 0 будет 255 до проверки на ноль
      //if (arrowPos == 2 && params.isAutoMode ) arrowPos = 0; // если в режиме авто, то  пропустить пункты 2 и 1
    }

    if (encoder.right() && isItemEdit == true)
    {
      switch (arrowPos)
      {
        case 0: params.P1++; params.P1 = constrain(params.P1, P1_MIN, P1_MAX);   break;
        case 1: params.T++; params.T= constrain(params.T, T_MIN, T_MAX);         break;
        case 2: params.P2++; params.P2 = constrain(params.P2, P2_MIN, P2_MAX);   break;
        case 3: params.S+=100; params.S = constrain(params.S, S_MIN, S_MAX); btnElectrodes.setHoldTimeout(params.S);  break;
        case 4: params.backlight++; params.backlight = constrain(params.backlight, BACKLIGHT_MIN, BACKLIGHT_MAX); setBacklight(); break;
        case 5: params.isAutoMode = !params.isAutoMode; break;
      }
      
    }

    if (encoder.left() && isItemEdit == true)
    {
      switch (arrowPos)
      {
        case 0: params.P1--; params.P1 = constrain(params.P1, P1_MIN, P1_MAX);  break;
        case 1: params.T--; params.T= constrain(params.T, T_MIN, T_MAX);       break;
        case 2: params.P2--; params.P2 = constrain(params.P2, P2_MIN, P2_MAX); break;
        case 3: params.S-=100; params.S = constrain(params.S, S_MIN, S_MAX); btnElectrodes.setHoldTimeout(params.S); break;
        case 4: params.backlight--; params.backlight = constrain(params.backlight, BACKLIGHT_MIN, BACKLIGHT_MAX); setBacklight();  break;
        case 5: params.isAutoMode = !params.isAutoMode; break;
      }
    }
  }
} // конец всей программы 
  

void allTicks(void)
{
    displayTimer.tick(); // main.h START Display Update Timer section
    encoder.tick();  
    btnElectrodes.tick();
    btnPedal.tick();
}

void setBacklight(void)
{
  //analogWrite(BACKLIGHT_PIN, params.backlight*51); // шим 255/5 уровней яркости = 51 коэфф
}

// дописать останов таймера1, вывод 9 сделать входом или сбросить
void gateError(void)
{
  displayTimer.stop(); // останавливаем таймер обновления экрана
  lcd.cls(); // очистка экрана
  lcd.locate(1, 2); lcd.print(F("DC 15V PROBLEM!"));
  lcd.locate(2, 6); lcd.print(F("DANGER!"));
  lcd.locate(3, 2); lcd.print(F("CONTROL VOLTAGE"));
  lcd.locate(4, 3); lcd.print(F("ERROR <10V >15V"));
  while (1)
  {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(1000);
    digitalWrite(PIN_BUZZER, LOW);
    delay(500);
  }
}

void beep()
{
  digitalWrite(PIN_BUZZER, HIGH);
  delay(50);
  digitalWrite(PIN_BUZZER, LOW);
}

void startBanner(void)
{
  lcd.locate(1, 3); lcd.print(F("BY AKA KASYAN")); // макрос F() загружает строковые константы из пзу без использования озу
  lcd.locate(2, 2); lcd.print(F("Spot Welder V1.0"));
  lcd.locate(3, 2); lcd.print(F(">>MyWeld V1.0<<"));
  lcd.locate(4, 1); lcd.print(F("Aka Kasyan YouTube"));
  delay(3000);
  beep();
  lcd.cls();
}

void Inits(void)
{
  stopPulseSequence(); // Init T1 Registers

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(9, OUTPUT); // 
  
  lcd.begin(4, 20);
  setBacklight(); // начальная яркость подсветки, режим пина настраивается сам внутри analogwrite()
  
  btnPedal.init(A4); // замыкание кнопки на землю, 
  
  btnElectrodes.init(A5, INPUT, HIGH); // замыкание электрода + на - с истоками, вход а5 подключен к истокам и подтянут к земле резистором 100ом
  btnElectrodes.setHoldTimeout(S_INITIAL); // установка задержки электродов
  
  //startBanner();
}

