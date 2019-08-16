//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(11, 10); //RX, TX
//
//void setup()
//{
//   mySerial.begin(9600);   
//   Serial.begin(9600);   
//   delay(100);
//}
//
//void loop()
//{
// 
//   if (Serial.available()>0){
//     mySerial.write(Serial.read());
//   }
//   if (mySerial.available()>0){
//     Serial.write(mySerial.read());
//   }
//}




//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(10, 11); // RX, TX
//
//void setup()  
//{
//  // Open serial communications and wait for port to open:
//  Serial.begin(9600);
//  mySerial.begin(9600);
//
//}
//
//void loop() // run over and over
//{
//  if (mySerial.available())
//    Serial.write(mySerial.read());
//
//  if (Serial.available())
//  {
//    while(Serial.available())
//    {
//      mySerial.write(Serial.read());
//    }
//    mySerial.println();
//  }
//}





//
//#include  <SoftwareSerial.h>
//#define GSMSerial Serial // the hardware serial will now be known as GSMSerial, to avoid confusion
//SoftwareSerial SMSerial(2,3); //Using Software Serial as second UART -
//char incoming_char=0; //Will hold the incoming character from the software Serial Port.
//void setup()
//{
////Initialize serial ports for communication.
//SMSerial.begin(9600);
//GSMSerial.begin(9600);
//SMSerial.println("Starting SM5100B Communication...");
//}
//void loop()
//{
//if(GSMSerial.available()>0) //If a character comes in from the cellular module...
//{
//SMSerial.write(GSMSerial.read()); //write it out to the serial monitor so we can see it
//}
//if(SMSerial.available() >0) //If you type something into the serial monitor
//{
//incoming_char=SMSerial.read(); //Get the character coming from the terminal
//GSMSerial.print(incoming_char); //Send the character to the cellular module.
//}}




/*
  Software serial multple serial test

 Receives from the two software serial ports,
 sends to the hardware serial port.

 In order to listen on a software port, you call port.listen().
 When using two software serial ports, you have to switch ports
 by listen()ing on each one in turn. Pick a logical time to switch
 ports, like the end of an expected transmission, or when the
 buffer is empty. This example switches ports when there is nothing
 more to read from a port

 The circuit:
 Two devices which communicate serially are needed.
 * First serial device's TX attached to digital pin 10(RX), RX to pin 11(TX)
 * Second serial device's TX attached to digital pin 8(RX), RX to pin 9(TX)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created 18 Apr. 2011
 modified 19 March 2016
 by Tom Igoe
 based on Mikal Hart's twoPortRXExample

 This example code is in the public domain.

 */

#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial portOne(10, 11);

// software serial #2: RX = digital pin 8, TX = digital pin 9
// on the Mega, use other pins instead, since 8 and 9 don't work on the Mega
SoftwareSerial portTwo(8, 9);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // Start each software serial port
  portOne.begin(9600);
  portTwo.begin(9600);
}

void loop() {
  
  Serial.println("Data from port two:");
  portOne.println("Data from port 11111:");
   portTwo.println("Data from 22222222 :");
  Serial.println();
}
