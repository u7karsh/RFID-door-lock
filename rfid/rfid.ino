#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#define rxPin 3
#define txPin 2
#define light_pin 7 
#define motor1 8
#define motor2 9
LiquidCrystal lcd(12, 11, 3, 4, 5, 6);
String utkarsh = "";
String ashish = "";
String aux1 = "";
String aux2 = "";
String user = "";
String temp="";
int action = 0;
int flag = 0;
int count;
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
void setup()  
{
  lcd.print("Initializing...");
  Serial.begin(57600);
  Serial.println("Scan RFID Tag!");
  lcd.begin(16, 2);
  lcd.print("----Room 411----");
  pinMode(light_pin,OUTPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  read_codes();
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
   if(inByte.equals(utkarsh)){
    user = "Welcome Utkarsh!";
    Serial.println("Welcome Utkarsh");
    action = 1;
    temp = (String)EEPROM.read(48);
    count = temp.toInt();
    count++;
    EEPROM.write(48, count);
    
   }
  else if(inByte.equals(ashish)){
    user = "Welcome Ashish! ";
    Serial.println("Welcome Ashish");
    action = 1;
    temp = (String)EEPROM.read(49);
    count = temp.toInt();
    count++;
    EEPROM.write(49, count);
  }
  else if(inByte.equals(aux1)){
    lcd.setCursor(0, 1);
    digitalWrite(light_pin,HIGH);
    temp = (String)EEPROM.read(48);
    temp = String("Utkarsh:" + temp);
    lcd.print(temp);
    delay(2000);
    temp = (String)EEPROM.read(49);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    temp = String("Ashish:" + temp);
    lcd.print(temp);
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    digitalWrite(light_pin,LOW);
  }
  else{
    user = "Access Denied!  ";
    action = 0;
  }
  flag = 0;
    }
  lcd.setCursor(0, 1);
  if(action == 1){
    lcd.print(user);
    digitalWrite(light_pin,HIGH);
    digitalWrite(motor2,HIGH);
    digitalWrite(motor1,LOW);
    delay(200);
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,LOW);
    delay(10000);
    digitalWrite(motor1,HIGH);
    digitalWrite(motor2,LOW); 
    delay(200);   
    action = 0;
  }    
   digitalWrite(motor1,LOW);
   digitalWrite(motor2,LOW);
   digitalWrite(light_pin,LOW);
   lcd.print("                ");
}


void read_codes(){
  int i;
  for(i=0;i<=11;i++){
   utkarsh = String(utkarsh + (String)EEPROM.read(i));
  }
  for(i=12;i<=23;i++){
   ashish = String(ashish + (String)EEPROM.read(i));
  }
  for(i=24;i<=35;i++){
   aux1 = String(aux1 + (String)EEPROM.read(i));
  }
  for(i=36;i<=47;i++){
   aux2 = String(aux2 + (String)EEPROM.read(i));
  }
}
