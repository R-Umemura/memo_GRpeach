#include <Arduino.h>
//#include <SoftwareSerial.h>

#define SERIAL_SELECT (Serial0)
#define SERIAL_B 9600

#define Re 12
#define De 11

#define Transmit HIGH
#define Receive LOW

#define Pin13LED 13

uint8_t byteIn[2] = {};
int byteOut;

void setup() /****** SETUP RUNS ONCE ******/
{
  Serial.begin(SERIAL_B);
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/
  Serial.println("Serial ready for transmitting");

  pinMode(Pin13LED, OUTPUT);
  pinMode(Re, OUTPUT);
  pinMode(De, OUTPUT);
  //pinMode(RxTx, OUTPUT);
  //RS485Receive();

  //digitalWrite(RxTx, Receive);   //Initialize transciever to receive data

  SERIAL_SELECT.begin(SERIAL_B); // set the data rate

} //--(end setup )---

void loop() /****** LOOP RUNS CONSTANTLY ******/
{
  //digitalWrite(Pin13LED, HIGH);       //On when not transmitting
  //if (Serial.available())
  //{

  //byteOut = 0x54; //Locally store the transmitted string

  RS485Transmit(); // Transmit
  char adachi = 0x54;
  SERIAL_SELECT.write(adachi); // Send byte to encoder
  SERIAL_SELECT.flush();
  delay(1);
  //delayMicroseconds(100);
  RS485Receive();
  //delayMicroseconds(100);
  delay(1);

  //digitalWrite(Pin13LED, LOW);      // Off momentarily
  //delay(10);
  // Receive
  //delay(100);
  //}

  if (SERIAL_SELECT.available()) //Look for data from encoder
  {
    Serial.print("received");
    //Serial.print("Received---");
    //digitalWrite(Pin13LED, LOW);        // Off momentarily
    byteIn[0] = SERIAL_SELECT.read();
    byteIn[1] = SERIAL_SELECT.read(); // Read received byte

    //RS485Receive();
    // Show on Serial Monitor
    delay(1);
    //delayMicroseconds(100);
  }
  else
  {
    //Serial.print(SERIAL_SELECT.available());
    delayMicroseconds(100);
  }

  Serial.print("Sent");
  Serial.print("\t"); //Serial indicator
  Serial.print(byteIn[0]);
  Serial.print("\t");
  Serial.print(byteIn[1]);
  Serial.println("\t");
  delay(10);
}

void RS485Transmit()
{
  digitalWrite(Re, LOW);
  digitalWrite(De, HIGH);
}
void RS485Receive()
{
  digitalWrite(Re, HIGH);
  digitalWrite(De, LOW);
}

/*
#include <Arduino.h>
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Serial0.begin(115200);
  pinMode(5, OUTPUT);
}

void loop() {
   byte buf = 0x54;
   int data1, data2;
   digitalWrite(5, HIGH);
   Serial0.write(buf);
  
   Serial0.flush();
    
    digitalWrite(5, LOW);
    delay(1);
    if(Serial0.available()){
    data1 = Serial0.read();
    data2 = Serial0.read();
    Serial.println("OK");
    Serial.println(data1);
    Serial.println(data2);
    }
    else{
    Serial.println("NO");
    }
    delay(100);
}*/
