#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(2, 3);

void setup()
{
  Serial.begin(9600);
  SoftSerial.begin(9600);
  
  SoftSerial.println("       **** Its a Software Serial **** ");
  SoftSerial.println(" Designed by www.TheEngineeringProjects.com");
  SoftSerial.println();
  
  Serial.println("       **** Its a Hardware Serial **** ");
  Serial.println(" Designed by www.TheEngineeringProjects.com");
  Serial.println();
}

void loop()
{
      
      if (Serial.available())
      {
           char data = Serial.read();
           SoftSerial.print(data);
      }
}
