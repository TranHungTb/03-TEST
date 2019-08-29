#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2,3); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
//  delay(1000);
//
//  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
//  updateSerial();
//  mySerial.println("ATE1");
//  updateSerial();
//  mySerial.println("AT+CSQ"); //Kiểm tra chất lượng tín hiệu, phạm vi giá trị là 0-31, 31 là tốt nhất
//  updateSerial();
//  mySerial.println("AT+CCID"); //Đọc thông tin SIM để xác nhận xem SIM đã được cắm chưa
//  updateSerial();
//  mySerial.println("AT+CREG?"); //Kiểm tra xem nó đã đăng ký trong mạng chưa
//  updateSerial();
}

void loop()
{
  updateSerial();
//  Serial.println(Serial.read());
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port

  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port

  }
}
