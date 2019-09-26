#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
void setup()   {   
    Serial.begin(9600);
    mySerial.begin(9600);
    Serial.println();
    Serial.println("Initializing...");
}
void loop(){

    
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
    
  }

  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
    
  }
}
