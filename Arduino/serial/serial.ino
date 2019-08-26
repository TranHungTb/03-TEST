#include <SoftwareSerial.h>


SoftwareSerial mySerial(2,3); //SIM800L Tx & Rx is connected to Arduino #2 & #3
//char inByte[2]={};

const String myphone = "0929034450";  
int RELAY =  13; 
int mic,old,Byt;                                           // Bat module Sim 900A

String s = ""; 
char inByte;

void updateSerial();


 void setup() {
  Serial.begin(9600);                           // Cau hinh UART de giao tiep module Sim 900A
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
    
  digitalWrite(RELAY, LOW);               // Khai bao chan  de dieu khien dong cat RELAY
  pinMode(RELAY, OUTPUT);
  pinMode(A0, INPUT);
                                    // Bat Module Sim 900A

}


void loop() {
updateSerial();  
}
 
 
 void updateSerial()
{
  delay(50);
  while (Serial.available()) 
  { 
    delay(50);
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available())
  {
    String command = mySerial.readString();
    Serial.println("Command Sent: " + command);

    if (command == ("\r\nOK\r\n")) {
      Serial.println(" da ok roi nha. khong can:" );
    }
    else
    {
      Serial.println(" da dfsdfsdfcan:" );
    }


//    delay(50);
//    inByte = mySerial.read();
//    Serial.write(inByte);
//    Byt = inByte,DEC;
//     if (Byt == 75 && old== 79) {
//      delay(50);
//      Serial.println("inByte:");
//    Serial.println(inByte,DEC);  
//    delay(50);
//    Serial.println("old:");
//    Serial.println(old,DEC );  
//    delay(50);
//      Serial.println(" da ok roi nha. khong can:" );
//    }
//    else
//    {
//      delay(50);         
//      Serial.println( inByte,DEC );
//      old = Byt;
//     Serial.println("khong duoc"); 
//    }
    
  }
  }
