//#include <Servo.h>
//
//#define SERVO_PIN 3
//
//Servo myservo1;
//int pos = 0;
//void setup() {
//  myservo1.attach(SERVO_PIN);
//  Serial.begin(9600);
//  Serial.println();
//
//
//}
//void loop() {
//  for ( pos = 0; pos <= 180; pos += 5) {
// 
//    myservo1.write(pos);
//    Serial.print("Pos= ");
//    Serial.print(pos);
//    Serial.println();
//    delay(100);
//   
//  }
//  for ( pos = 180; pos >= 0; pos -= 5) {
//    myservo1.write(pos);
//    Serial.print("Pos= ");
//    Serial.print(pos);
//    Serial.println();
//    delay(100);
//  }
//  delay(500);
//}


#include <Servo.h>      // Thư viện điều khiển servo
 
// Khai báo đối tượng myservo dùng để điều khiển servo
Servo myservo;          
 int pos = 0;
int bientro = A0;       // Khai báo chân analog đọc biến trở điều khiển servo
int servoPin = 3;       // Khai báo chân điều khiển servo
 
void setup ()
{
    // Cài đặt chức năng điều khiển servo cho chân servoPin
    myservo.attach(servoPin); 
    
    Serial.begin(9600); // Mở giao tiếp Serial ở baudrate 9600
}
 
void loop ()
{
   for ( pos = 0; pos <= 180; pos += 5) {
 
    myservo.write(pos);
    Serial.print("Pos= ");
    Serial.print(pos);
    Serial.println();
    delay(100);
   
  }
  for ( pos = 180; pos >= 0; pos -= 5) {
    myservo.write(pos);
    Serial.print("Pos= ");
    Serial.print(pos);
    Serial.println();
    delay(100);
  }
  delay(500);
}
