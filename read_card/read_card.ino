#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 2

int flag = 0;

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
void setup()  
{
  Serial.begin(57600);
  mySerial.begin(9600);
}

void loop()                    
{

  String inByte="";
  while(mySerial.available()) {
      inByte = String(inByte + mySerial.read());
      flag = 1;
    }

    if(flag == 1){
      Serial.println(inByte);
      flag = 0;
    }
}
