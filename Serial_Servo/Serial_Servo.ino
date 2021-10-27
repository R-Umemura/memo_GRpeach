#define PIN_SELECT 5

bool sendpos(byte id, unsigned int pos)
{
  byte buf[9] = {
      0xff, 0xff, // header
      id,         // id
      0x05,       // inst
      0x03,       // size
      0x1E,       // address
      (byte)(pos & 0xff), (byte)(pos >> 8),
      0x00};

  for (int i = 2; i < 8; i++)
    buf[8] += buf[i]; // calc sum
  buf[8] = ~buf[8];

  digitalWrite(PIN_SELECT, 1);
  //for (int i = 0; i < 9; i++) Serial4.write(buf[i]);   // send inst packet
  Serial4.write(buf, 9);
  Serial4.flush();
  delay(1);
  digitalWrite(PIN_SELECT, 0);
  while (Serial4.available())
  { // 受信処理
    Serial.println(Serial4.read());
  }

  return false;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial4.begin(115200);
  Serial4.setTimeout(50);

  pinMode(PIN_SELECT, OUTPUT);

  delay(500);

  Serial.println("send LED on");
  byte buf1[9] = {
      0xff, 0xff, // header
      0x01,       // id
      0x04,       // length
      0x03,       // inst
      0x19,       // addr
      0x01,       // data
      0x00};
  for (int i = 2; i < 7; i++)
    buf1[7] += buf1[i]; // calc sum
  buf1[7] = ~buf1[7];
  while (Serial4.available())
    Serial4.read(); // clear buffer

  digitalWrite(PIN_SELECT, 1);
  //for (int i = 0; i < 8; i++) Serial4.write(buf1[i]);   // send inst packet
  Serial4.write(buf1, 8);
  Serial4.flush();
  delay(1);
  digitalWrite(PIN_SELECT, 0);
  while (Serial4.available())
  { // 受信処理
    Serial.println(Serial4.read());
  }

  Serial.println("torque enable send");
  byte buf2[9] = {
      0xff, 0xff, // header
      0x01,       // id
      0x04,       // len
      0x03,       // inst
      0x18,
      0x01,
      0x00};
  for (int i = 2; i < 7; i++)
    buf2[7] += buf2[i]; // calc sum
  buf2[7] = ~buf2[7];

  while (Serial4.available())
    Serial4.read(); // clear buffer

  digitalWrite(PIN_SELECT, 1);
  //for (int i = 0; i < 8; i++) Serial4.write(buf2[i]);   // send inst packet
  Serial4.write(buf2, 8);
  Serial4.flush();
  delay(1);
  digitalWrite(PIN_SELECT, 0);
  while (Serial4.available())
  { // 受信処理
    Serial.println(Serial4.read());
  }
  Serial.println("torque enable send end");
}

void loop()
{
  int a = 0;
  int b = 1;
  int c = 2;
  int d = 3;
  int e = 4;
  sendpos(a, 0); // Set Goal Position to  0
  //delay(10);
  sendpos(b, 0); // Set Goal Position to  0
  //delay(10);
  sendpos(c, 0); // Set Goal Position to  0
  //delay(10);
  sendpos(d, 1000); // Set Goal Position to  0
  //delay(10);
  sendpos(e, 1000); // Set Goal Position to  0
  //delay(1000);
  delay(1000);
  //delay(1000);

  sendpos(a, 1000); // Set Goal Position to  0
  //delay(10);
  sendpos(b, 1000); // Set Goal Position to  0
  //delay(10);
  sendpos(c, 1000); // Set Goal Position to  0
  //delay(10);
  sendpos(d, 0); // Set Goal Position to  0
  //delay(10);
  sendpos(e, 0);
  //delay(1000);
  //delay(1000);
  //delay(1000);
}
