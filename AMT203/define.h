#ifndef DEFINE_h
#define DEFINE_h

#include "Arduino.h"

#define PIN_CSB1 8
#define PIN_CSB2 9
//AMT203のCSBピンは，68,69,70番は使用できない．
//他にも使用できないピンがある可能性有，読めない場合はピンを変えてみること．

#define SW_1 1
#define SW_2 2

// 制御周期
#define INT_TIME			( 0.01 )//( 0.001 )