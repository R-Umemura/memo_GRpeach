#include <Arduino.h>
#include <MsTimer2.h>

#define SELLECT_PIN 55
#define NODE_ADDRESS (0x54) //エンコーダのアドレス
#define SELEAL_SELECT (Serial4)

int absEncData;
byte saveData[2];
byte  K0, K1;
bool flag_10ms = false;
bool flag_100ms = false;

void warikomi()
{
  static int count = 0;
  count++;
  bool flag_10ms = true;
  if (count >= 10)
  {
    flag_100ms = true;
    count = 0;
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  SELEAL_SELECT.begin(115200);
  pinMode(SELLECT_PIN, OUTPUT);
  Serial.print("START");
  MsTimer2::set(10, warikomi);
  MsTimer2::start();
}

void loop()
{
  // put your main code here, to run repeatedly:

  if (flag_10ms)
  {

    //while(!SELEAL_SELECT.available());
    /*absEncData = SELEAL_SELECT.read();
    saveData[0] = absEncData & 0b11111111;
    absEncData |= SELEAL_SELECT.read() << 8;
    saveData[1] = absEncData >> 8 & 0b00111111;
    absEncData = 0;
    absEncData = saveData[0];
    absEncData |= saveData[1] << 8;
    */

    flag_10ms = false;
  }

  if (flag_100ms)
  {
    uint8_t def[2] = {};
    digitalWrite(SELLECT_PIN, HIGH);   //send
    SELEAL_SELECT.write(NODE_ADDRESS); //読み取りコマンド
    Serial.flush();
    delay(10);
    digitalWrite(SELLECT_PIN, LOW); //recive
    def[0] = SELEAL_SELECT.read();
    def[1] = SELEAL_SELECT.read();
    delay(10);
    //Serial.println(absEncData );
    //Serial.print(SELEAL_SELECT.available());
    //Serial.print("---");
    if (SELEAL_SELECT.available())
    {
      /*
      K0 = bitRead(def[1], 1);
      K1 = bitRead(def[1], 2);
      delay(1));
      *?
      
      saveData[2] = SELEAL_SELECT.read();
      saveData[0] = absEncData & 0b11111111;
      absEncData |= SELEAL_SELECT.read() << 8;
      saveData[1] = absEncData >> 8 & 0b00111111;
      absEncData = 0;
      absEncData = saveData[0];
      absEncData |= saveData[1] << 8;
      //Serial.println(absEncData);
      */
      
      
      Serial.print("first : ");
      Serial.print(SELEAL_SELECT.read());
      Serial.print("\t");
      Serial.print("second : ");
      Serial.println(SELEAL_SELECT.read(),BIN);
      /*
      Serial.print("OK");
      Serial.print("\t");
      Serial.print(K0);
      Serial.print("\t");
      Serial.println(K1);
      */
    }

    flag_100ms = false;
  }
}
