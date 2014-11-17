#include <SoftwareSerial.h>
#include <EEPROM.h>

#define rxPin 3
#define txPin 2
#define motor1 8
#define motor2 9
#define close_feedback 13
#define wireless 16
float t_debounce = 10;
float t_bit_rate = 110;

String utkarsh = "";
String ashish = "";

int action = 0;
int flag = 0;

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()  
{
	Serial.begin(9600);
	pinMode(motor1,OUTPUT);
	pinMode(motor2,OUTPUT);
	pinMode(close_feedback, INPUT);
	pinMode(wireless, INPUT);
	read_codes();
	mySerial.begin(9600);
}

void loop()                    
{
	//okay.. let us form the string
	String inByte="";
	while(mySerial.available()) 
	{
		inByte = String(inByte + mySerial.read());
		flag = 1;
	}
	
	check_wireless();
	
	if(flag == 1)
	{
		delay(100);
		if(inByte.equals(utkarsh))
		{
			action = 1;
		}
		else if(inByte.equals(ashish))
		{
			action = 1;
		}
		else
		{
			action = 0;
		}
		flag = 0;
	}
	if(action == 1)
	{
		digitalWrite(motor2,HIGH);
		digitalWrite(motor1,LOW);
		delay(200);
		digitalWrite(motor1,LOW);
		digitalWrite(motor2,LOW);
		int ret = lock_after_open_timeout();
		action = 0;
	}  
	else if(action == 2)
	{
		int ret = lock_instantaneous();
		action = 0;
	}
	else if(action == 3)
	{
		digitalWrite(motor2,HIGH);
		digitalWrite(motor1,LOW);
		delay(200);
		digitalWrite(motor1,LOW);
		digitalWrite(motor2,LOW);
		action = 0;
	}
}

int lock_after_open_timeout()
{
	int stat = 0;
	int timeout = 0;
	while(1)
	{ 
		while(digitalRead(close_feedback) == HIGH && stat ==0)
		{
			if(timeout >= 3000)
			{
				digitalWrite(motor2,LOW);
				digitalWrite(motor1,HIGH);
				delay(200);
				digitalWrite(motor1,LOW);
				digitalWrite(motor2,LOW);  
				return 1;
			}
			delay(10);
			timeout++;
		}
		stat = 1;
		int cnt = 0;
		while(digitalRead(close_feedback) == HIGH)
		{
			if(cnt >= 50)
			{
				digitalWrite(motor2,LOW);
				digitalWrite(motor1,HIGH);
				delay(200);
				digitalWrite(motor1,LOW);
				digitalWrite(motor2,LOW);  
				return 1;
			}
			cnt++;
			delay(10);
		}
	}
	return 0;
}

int lock_instantaneous()
{
	while(1)
	{ 
		int cnt = 0;
		while(digitalRead(close_feedback) == HIGH)
		{
			if(cnt >= 50)
			{
				digitalWrite(motor2,LOW);
				digitalWrite(motor1,HIGH);
				delay(200);
				digitalWrite(motor1,LOW);
				digitalWrite(motor2,LOW);  
				return 1;
			}
			cnt++;
			delay(10);
		}
	}
	return 0;
}

void read_codes()
{
	int i;
	for(i=0;i<=11;i++)
	{
		utkarsh = String(utkarsh + (String)EEPROM.read(i));
	}
	for(i=12;i<=23;i++)
	{
		ashish = String(ashish + (String)EEPROM.read(i));
	}
}	

void check_wireless()
{
	if(digitalRead(wireless) == HIGH)
	{
		delay(20);
                if(digitalRead(wireless) == HIGH)
                {
                  action = 1;
                }
		
	}
	delay(500);
	if(digitalRead(wireless) == HIGH)
	  action = 0;
}																		
