#include <Arduino.h>
#include <MsTimer2.h>
#include <SPI.h>
#include <math.h>
#include "define.h"

void setup() {
  pinMode(SW_1);
  pinMode(SW_2);
}

void loop() {

  analogRead(ANALOG_SELECT1);
  
}
