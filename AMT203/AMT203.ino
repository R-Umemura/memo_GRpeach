// GR-PEACHボードを使ったプログラムです
// このプログラムは，AMT203を読み取るものです．
// uenosuke(上野先生)が作成したライブラリの使用を前提としています．
// 作成日 2021/05/22
// 作成者 Rumemura(梅村留奈)

//メモ
//AMT203値を初期化＆読み取れるプログラムです．
//今はコメントアウトしてありますが，109行目，110行目が初期化用のコマンドなので必要な方をコメントアウト外して入れてください．
//初期化のときだいたい4096と出力されますがそれで大丈夫です．
//方位角はど真ん中，仰角は一番下が初期位置です．
//よろしくお願いします．


#include <Arduino.h>
#include <MsTimer2.h>
#include <SPI.h>
#include <math.h>
#include "define.h"
#include "AMT203VPeach.h"

AMT203V amt_houikaku(&SPI, PIN_CSB);
AMT203V amt_gyoukaku(&SPI, PIN_CSB2);

// グローバル変数の設定
double gPosix = 0.0, gPosiy = 0.0, gPosiz = 0.0;
double refVx, refVy, refVz;
double angle_rad;
int encX = 0, encY = 0; // X,Y軸エンコーダのカウント値
int preEncX = 0, preEncY = 0; // X,Y軸エンコーダの"1サンプル前の"カウント値

unsigned int ButtonState = 0, LJoyX = 127, LJoyY = 127, RJoyX = 127, RJoyY = 127; // コントローラデータ格納用

int zone; // 赤か青か
bool flag_10ms = false; // loop関数で10msごとにシリアルプリントできるようにするフラグ
bool flag_100ms = false;

// 最大最小範囲に収まるようにする関数
double min_max(double value, double minmax)
{
  if(value > minmax) value = minmax;
  else if(value < -minmax) value = -minmax;
  return value;
}

// LEDをチカチカさせるための関数
void LEDblink(byte pin, int times, int interval){
  analogWrite(pin, 0);
  for(int i = 0; i < times; i++){
    delay(interval);
    analogWrite(pin, 255);
    delay(interval);
    analogWrite(pin, 0);
  }
}

// setupで有効にされるタイマ割り込み処理が書いてある場所
void timer_warikomi(){    
  // RGB LED を良い感じに光らせるための処理
  static int count = 0;
  static int count_flag = 0;
  count += 2; // ここで光る周期を変えられる(はず)
  count_flag++;

  if(count < 255){
    analogWrite(PIN_LED_RED, count);
    analogWrite(PIN_LED_BLUE, 255 - count);
  }else if(count < 255 * 2){
    analogWrite(PIN_LED_GREEN, count - 255);
    analogWrite(PIN_LED_RED, 255 * 2 - count);
  }else if(count < 255 * 3){
    analogWrite(PIN_LED_BLUE, count - 255 * 2);
    analogWrite(PIN_LED_GREEN, 255 * 3 - count);
  }else{
    count = 0;
  }

  // フラグ立てるための処理
  flag_10ms = true;
  /*
  if(count_flag >= 10){
    flag_100ms = true;
    count_flag = 0;
  }*/

}

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_SW, INPUT); // オンボードのスイッチ

  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_ENC, OUTPUT);
  
  pinMode(PIN_ENC_A, INPUT);
  pinMode(PIN_ENC_B, INPUT);
  
  // AMT203Vの初期化
  SPI.begin(); // ここでSPIをbeginしてあげないとちゃんと動かなかった
  SPI.setClockDivider(SPI_CLOCK_DIV16); //SPI通信のクロックを1MHzに設定 beginの後に置かないと，処理が止まる
  Serial.println(amt_houikaku.init());
  Serial.println(amt_gyoukaku.init());
    
  LEDblink(PIN_LED_GREEN, 2, 100); // 初期が終わった証拠にブリンク
  Serial.println("AMT203V init done!");
  Serial.flush();

  
  //amt_houikaku.setZeroPos();
  //amt_gyoukaku.setZeroPos();
  MsTimer2::set(10, timer_warikomi); // 10ms period
  MsTimer2::start();
  
  
}

void loop()
{
  //digitalWrite(84, HIGH);

  // 10msに1回ピン情報を出力する
  if(flag_10ms){
  
    int thetaDuEnc_houikaku;
    int thetaDuEnc_gyokaku; /*,preThetaDuEnc*/;
    thetaDuEnc_houikaku = amt_houikaku.getEncount(); 
    //delay(10);
    thetaDuEnc_gyokaku = amt_gyoukaku.getEncount();
    //delay(10);

    

    Serial.print("ENC1_");
    Serial.print(thetaDuEnc_houikaku);
    Serial.print("___ENC2_");
    Serial.println(thetaDuEnc_gyokaku);
    
    flag_10ms = false;
    
  }


 //delayMicroseconds(100);
}
