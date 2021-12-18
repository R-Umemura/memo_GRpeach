#define PIN_SELECT 2
#define SERIAL_SELECT (Serial4)

bool sendpos(byte id, unsigned int pos)
{
    byte buf[9] = {
        0xff, 0xff, // header
        id,         // id
        0x05,          // inst
        0x03,          // size
        0x1E,         // address
        (byte)(pos & 0xff), (byte)(pos >> 8),
        0x00
    };

    for (int i = 2; i < 8; i++) buf[8] += buf[i]; // calc sum
    buf[8] = ~buf[8];
    
    digitalWrite(PIN_SELECT, 1);
    //for (int i = 0; i < 9; i++) SERIAL_SELECT.write(buf[i]);   // send inst packet
    SERIAL_SELECT.write(buf, 9);
    SERIAL_SELECT.flush();
    delay(1);
    digitalWrite(PIN_SELECT, 0);
    while (SERIAL_SELECT.available ()){ // 受信処理
      Serial.println(SERIAL_SELECT.read ());
    }
    
    return false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SERIAL_SELECT.begin(115200);
  SERIAL_SELECT.setTimeout(50);
  
  pinMode(PIN_SELECT, OUTPUT);
  
  delay(500);
  
  Serial.println("send LED on");
    byte buf1[9] = {
        0xff, 0xff, // header
        0x01,         // id
        0x04,      // length
        0x03,      // inst
        0x19,      // addr
        0x01,      // data
        0x00
    };
    for (int i = 2; i < 7; i++) buf1[7] += buf1[i]; // calc sum
    buf1[7] = ~buf1[7];
    while (SERIAL_SELECT.available ()) SERIAL_SELECT.read (); // clear buffer
    
    digitalWrite(PIN_SELECT, 1);
    //for (int i = 0; i < 8; i++) SERIAL_SELECT.write(buf1[i]);   // send inst packet
    SERIAL_SELECT.write(buf1, 8);
    SERIAL_SELECT.flush();
    delay(1);
    digitalWrite(PIN_SELECT, 0);
    while (SERIAL_SELECT.available ()){ // 受信処理
      Serial.println(SERIAL_SELECT.read ());
    }
    
    Serial.println("torque enable send");
    byte buf2[9] = {
        0xff, 0xff, // header
        0x01,         // id
        0x04,      // len
        0x03,      // inst
        0x18,
        0x01,
        0x00
    };
    for (int i = 2; i < 7; i++) buf2[7] += buf2[i]; // calc sum
    buf2[7] = ~buf2[7];
    
    while (SERIAL_SELECT.available ()) SERIAL_SELECT.read (); // clear buffer
    
    digitalWrite(PIN_SELECT, 1);
    //for (int i = 0; i < 8; i++) SERIAL_SELECT.write(buf2[i]);   // send inst packet
    SERIAL_SELECT.write(buf2, 8);
    SERIAL_SELECT.flush();
    delay(1);
    digitalWrite(PIN_SELECT, 0);
    while (SERIAL_SELECT.available ()){ // 受信処理
      Serial.println(SERIAL_SELECT.read ());
    }

}

void loop() {
  // put your main code here, to run repeatedly: 
  //回転
  int u = 2;
  //Serial.println("send to 1 -1");
  sendpos (u, 0);    // Set Goal Position to  0
  delay(100);      // Delay 1 sec
  //Serial.println("send to 1 -2");
  sendpos (u, 1000); // Set Goal Position to 1023
  delay(100);      // Delay 1 sec
}



