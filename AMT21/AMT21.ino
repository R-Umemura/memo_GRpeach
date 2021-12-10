#include "Arduino.h"
#define SERIAL (Serial0)
#define PIN_SELECT 0

bool sendpos()
{
  byte buf[5] = {
      0xff, 0xff, // header
      0x01,
      0x02,
      0x00};

  for (int i = 2; i < 5; i++)
    buf[5] += buf[i]; // calc sum
  buf[5] = ~buf[5];

  digitalWrite(PIN_SELECT, 1);
  //for (int i = 0; i < 9; i++) SERIAL.write(buf[i]);   // send inst packet
  SERIAL.write(buf, 3);
  SERIAL.flush();
  delay(1);
  digitalWrite(PIN_SELECT, 0);
  while (SERIAL.available())
  { // 受信処理
    Serial.println(SERIAL.read());
  }

  return false;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  SERIAL.begin(115200);
  SERIAL.setTimeout(50);

  pinMode(PIN_SELECT, OUTPUT);

  delay(500);

  Serial.println("send LED on");
  byte buf1[5] = {
      0xff, 0xff, // header
      0x01,
      0x02,
      0x00};
  for (int i = 2; i < 4; i++)
    buf1[3] += buf1[i]; // calc sum
  buf1[3] = ~buf1[];
  while (SERIAL.available())
    SERIAL.read(); // clear buffer

  digitalWrite(PIN_SELECT, 1);
  //for (int i = 0; i < 8; i++) SERIAL.write(buf1[i]);   // send inst packet
  SERIAL.write(buf1, 8);
  SERIAL.flush();
  delay(1);
  digitalWrite(PIN_SELECT, 0);
  while (SERIAL.available())
  { // 受信処理
    Serial.println(SERIAL.read());
  }

  Serial.println("torque enable send");
  byte buf2[5] = {
      0xff, 0xff, // header
      0x01,
      0x02,
      0x00};
  for (int i = 2; i < 7; i++)
    buf2[7] += buf2[i]; // calc sum
  buf2[7] = ~buf2[7];

  while (SERIAL.available())
    SERIAL.read(); // clear buffer

  digitalWrite(PIN_SELECT, 1);
  //for (int i = 0; i < 8; i++) SERIAL.write(buf2[i]);   // send inst packet
  SERIAL.write(buf2, 8);
  SERIAL.flush();
  delay(1);
  digitalWrite(PIN_SELECT, 0);
  while (SERIAL.available())
  { // 受信処理
    Serial.println(SERIAL.read());
  }
  Serial.println("torque enable send end");
}

void loop()
{
  Serial.print();
  Serial.println("end");
}
