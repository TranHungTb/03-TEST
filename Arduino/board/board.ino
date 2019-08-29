////i2c Master Code(UNO)
//#include <Wire.h>
//void setup()
//{
//  Serial.begin(9600);
//  Wire.begin(); // Khởi tạo thư viện i2c
//}
//
//void loop()
//{
//  while (Serial.available()) // đợi cho đến khi serial có tín hiệu
//  {
//    char c = Serial.read(); // gán biến c đọc dữ liệu trong serial
//
//    if (c == 'H') // nếu c = "H"
//    {
//      Wire.beginTransmission(6); // Bắt đầu truyền dữ liệu về địa chỉ số 6
//      Wire.write('H'); // Truyền ký tự H
//      Wire.endTransmission(); // kết thúc truyền dữ liệu
//    }
//    else if (c == 'L') // Nếu c = "L"
//    {
//      Wire.beginTransmission(6); // Bắt đầu truyền dữ liệu về địa chỉ sô 6
//      Wire.write('L'); // Truyền ký tự L
//      Wire.endTransmission();// Kết thúc truyền dữ liệu
//    }
//  }
//}


//i2c Slave Code(UNO)
#include <Wire.h>
void setup()
{
  Wire.begin(6); // Khởi tạo thư viện i2c địa chỉ 6
  Wire.onReceive(receiveEvent); // khởi tạo chế độ nhận tín hiệu từ boad chủ
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}
 
void loop()
{
}
 
void receiveEvent() // hàm sự kiện nhận tín hiệu từ boad chủ
{
  while(Wire.available()) // chờ cho đến khi có tín hiệu
  {
    char c = Wire.read(); // biến c để lưu dữ liệu nhận được
    
    if(c == 'H') // nếu boad chủ gửi về tín hiệu là H
    {
      digitalWrite(13,HIGH); // chân 13 ở mức High
    }
    else if(c == 'L') // nếu tín hiệu boad chủ gửi về là L
    {
      digitalWrite(13,LOW);// chân 13 ở mức Low
    }
  }
}
