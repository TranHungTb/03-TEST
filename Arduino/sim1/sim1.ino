#include <SoftwareSerial.h>


SoftwareSerial GSMSerial(15,14);    // RX, TX

void setup()
{

     GSMSerial.begin(9600);
     Serial.begin(9600);
     Serial.println("START");
}

void loop()
{
     if(Serial.available())
       GSMSerial.print((char)Serial.read());
     else  if(GSMSerial.available())
       Serial.print((char)GSMSerial.read());
}
