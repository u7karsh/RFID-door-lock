#include <EEPROM.h>

void setup()
{
  
  //utkarsh card
    EEPROM.write(0, 0);
    EEPROM.write(1, 1);
    EEPROM.write(2, 2);
    EEPROM.write(3, 3);
    EEPROM.write(4, 4);
    EEPROM.write(5, 5);
    EEPROM.write(6, 6);
    EEPROM.write(7, 7);
    EEPROM.write(8, 8);
    EEPROM.write(9, 9);
    EEPROM.write(10, 10);
    EEPROM.write(11, 11);
    
    
   //ashish card
    EEPROM.write(12, 12);
    EEPROM.write(13, 13);
    EEPROM.write(14, 14);
    EEPROM.write(15, 15);
    EEPROM.write(16, 16);
    EEPROM.write(17, 17);
    EEPROM.write(18, 18);
    EEPROM.write(19, 19);
    EEPROM.write(20, 20);
    EEPROM.write(21, 21);
    EEPROM.write(22, 22);
    EEPROM.write(23, 23);
    
    /*
    
    EEPROM.write(48, 0); // counter utkarsh
    EEPROM.write(49, 0); // counter ashish
    */
}

void loop()
{
}

