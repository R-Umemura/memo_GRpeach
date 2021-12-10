#include <Arduino.h>
#include <MsTimer2.h>

#define SELLECT_PIN 20
#define NODE_ADDRESS (0x54) //エンコーダのアドレス
#define TURN_ADDRESS (0x55) //エンコーダのアドレス
#define SELEAL_SELECT (Serial0)

int absEncData;
byte saveData[2];
byte  K0, K1;
bool flag_10ms = false;
bool flag_100ms = false;

void warikomi()
{
// RGB LED を良い感じに光らせるための処理
  static int count = 0;
  static int count_flag = 0;
  count += 5; // ここで光る周期を変えられる(はず)
  count_flag++;

  if (count < 255)
  {
    analogWrite(PIN_LED_RED, count);
    analogWrite(PIN_LED_BLUE, 255 - count);
  }
  else if (count < 255 * 2)
  {
    analogWrite(PIN_LED_GREEN, count - 255);
    analogWrite(PIN_LED_RED, 255 * 2 - count);
  }
  else if (count < 255 * 3)
  {
    analogWrite(PIN_LED_BLUE, count - 255 * 2);
    analogWrite(PIN_LED_GREEN, 255 * 3 - count);
  }
  else
  {
    count = 0;
  }

  bool flag_10ms = true;
  if (count_flag >= 10)
  {
    flag_100ms = true;
    count_flag = 0;
  }
}

void setup()
{
  Serial.begin(115200);
  SELEAL_SELECT.begin(115200);
  pinMode(SELLECT_PIN, OUTPUT);
  Serial.print("START");
  MsTimer2::set(10, warikomi);
  MsTimer2::start();
}

void loop()
{
  if (flag_100ms)
  {
    uint8_t def[2] = {};
    digitalWrite(SELLECT_PIN, HIGH);   //send
    SELEAL_SELECT.write(NODE_ADDRESS); //読み取りコマンド
    Serial.flush();
    delay(10);
    SELEAL_SELECT.write(TURN_ADDRESS);
    Serial.flush();
    delay(10);
    digitalWrite(SELLECT_PIN, LOW); //recive
    def[0] = SELEAL_SELECT.read();
    def[1] = SELEAL_SELECT.read();
    delay(10);
    
    if (SELEAL_SELECT.available())
    {
      /*
      K0 = bitRead(def[1], 1);
      K1 = bitRead(def[1], 2);
      delay(1));
      */
      
      saveData[2] = SELEAL_SELECT.read();
      saveData[0] = absEncData & 0b11111111;
      absEncData |= SELEAL_SELECT.read() << 8;
      saveData[1] = absEncData >> 8 & 0b00111111;
      absEncData = 0;
      absEncData = saveData[0];
      absEncData |= saveData[1] << 8;
      //Serial.println(absEncData);
      
      Serial.print(absEncData);
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
