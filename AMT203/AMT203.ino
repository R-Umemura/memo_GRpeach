// GR-PEACHボードを使ったプログラムです
// このプログラムは，AMT203を読み取るまたは原点をリセットするものです．
// uenosuke(上野先生)が作成したライブラリの使用を前提としています．
// 作成日 2021/05/22
// 最終更新日 2021/10/27
// 作成者 Rumemura(梅村留奈)

//メモ
//AMT203値を初期化＆読み取れるプログラムです．
//初期化のときだいたい4096と出力されますがそれで大丈夫です．
//２つ同時に読めるようになっています．
//AMT203のCSBピンやスイッチのピン番号はdefineの方から変えてください

#include <Arduino.h>
#include <MsTimer2.h>
#include <SPI.h>
#include <math.h>
#include "define.h"
#include "AMT203VPeach.h"

AMT203V amt203_1(&SPI, PIN_CSB1);
AMT203V amt203_2(&SPI, PIN_CSB2);

bool flag_10ms = false; // loop関数で10msごとにシリアルプリントできるようにするフラグ
bool flag_100ms = false;

// LEDをチカチカさせるための関数
void LEDblink(byte pin, int times, int interval)
{
  analogWrite(pin, 0);
  for (int i = 0; i < times; i++)
  {
    delay(interval);
    analogWrite(pin, 255);
    delay(interval);
    analogWrite(pin, 0);
  }
}

// setupで有効にされるタイマ割り込み処理が書いてある場所
void timer_warikomi()
{
  // RGB LED を良い感じに光らせるための処理
  static int count = 0;
  static int count_flag = 0;
  count += 2; // ここで光る周期を変えられる(はず)
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

  // フラグ立てるための処理
  flag_10ms = true;
}

void setup()
{
  Serial.begin(115200);

  // AMT203Vの初期化
  SPI.begin();                          // ここでSPIをbeginしてあげないとちゃんと動かなかった
  SPI.setClockDivider(SPI_CLOCK_DIV16); //SPI通信のクロックを1MHzに設定 beginの後に置かないと，処理が止まる
  Serial.println(amt203_1.init());
  Serial.println(amt203_2.init());
  //ここのinitで1が出力されなかった場合はうまく読み取れてない．

  LEDblink(PIN_LED_GREEN, 2, 100); // 初期が終わった証拠にブリンク
  Serial.println("AMT203V init done!");
  Serial.flush();

  MsTimer2::set(10, timer_warikomi); // 10ms period
  MsTimer2::start();
}

void loop()
{
  // 10msに1回ピン情報を出力する
  if (flag_10ms)
  {

    int Enc_read_1;
    int Enc_read_2; /*,preEnc_read*/
    ;
    int SW_read_1 = digitalRead(SW_1);
    int SW_read_2 = digitalRead(SW_2);

    Enc_read_1 = amt203_1.getEncount();
    Enc_read_2 = amt203_2.getEncount();


    //AMT203の原点をリセットする>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (SW_read_1 == 1)
    {
      amt203_1.setZeroPos();
    }
    else if (SW_read_2 == 1)
    {
      amt203_2.setZeroPos();
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //読み取った値をtera termで表示する
    Serial.print("ENC1_");
    Serial.print(Enc_read_1);
    Serial.print("___ENC2_");
    Serial.println(Enc_read_2);

    flag_10ms = false;
  }
}
