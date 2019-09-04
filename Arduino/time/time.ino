#include <SoftwareSerial.h>
//#include <Wire.h>
//#include <GOFi2cOLED.h>
//
//GOFi2cOLED GOFoled;

SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2



const String myphone = "0929034450";     // Thay so cua ban vao day
const int RELAY =  13;                              // Chan so 12 arduino uno dung lam chan dieu khien dong/cat Relay de On/Off den

String RxBuff = "";                                    // Khai bao bo dem nhan du lieu
String returned = "";                                // Tat ca du lieu nhan ve tu module sim deu duoc luu trong day
boolean newline = false;
String Sdt="";
int Index= -1;                           // vi tri cua chuoi returned
int Index_Lamp_On = -1;                           // vi tri cua chuoi "LAMP_ON"
int Index_Lamp_Off = -1;                           // vi tri cua chuoi "LAMP_OFF"

void serialEvent();
void runUtilOk(String cmd, String okCondition, int delays);
void updateSerial();
void Gsm_Init();                                    // Cau hinh Module Sim800C
void Gsm_MakeCall(String phone);                   // Ham goi dien
void Gsm_MakeSMS(String phone, String content);    // Ham nhan tin
void ConnectServer(String ip, String port);
void disconnected();
void Makesendserver(String content);


void setup()
{

  Serial.begin(9600);

  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
  digitalWrite(RELAY, LOW);               // Khai bao chan  de dieu khien dong cat RELAY
  pinMode(RELAY, OUTPUT);

  delay(5000);                                              // Đợi module sim kiểm tra kết nối mạng GSM


  Gsm_Init();                                                 // Cau hinh module Sim800C
//  Gsm_MakeCall(myphone);                          // Test cuoc goi
  // Gsm_MakeSMS(myphone,"I'm a test");       // Test tin nhan
//  ConnectServer("138.197.46.187", "1346");
  //  mySerial.println("at+cipstart=\"tcp\",\"138.197.46.187\",\"1349\"");
  //  delay(2000);


  //  Makesendserver("times");

}

void loop() {
  serialEvent();                                                                    // tre 1s
  Index_Lamp_On = returned.indexOf("time");              // Tim vi tri cua chuoi "LAMP_ON" trong bo dem nhan RxBuff

  if (Index_Lamp_On >= 0)                                                  // Neu tim thay "LAMP_ON" trong RxBuff
  {
    digitalWrite(RELAY, LOW);
    Index_Lamp_On = -1;                                                     //
    Serial.println("Nhận tin lấy giờ:" + returned);
    Sdt = returned.substring(9, 21);
    Serial.print("Số điện thoại yêu cầu:");
    Serial.println(Sdt);
    Serial.println("Gửi tin lấy giờ lên server");
    times:
    returned = "";
    ConnectServer("138.197.46.187","1349");   
    Makesendserver("times");
    serialEvent();   
    Index = returned.indexOf("GMT");
    if (Index >= 0)                   // Neu tim thay "LAMP_ON" trong RxBuff
   {
      Index = -1; 
      digitalWrite(RELAY, LOW);                                           
      Serial.println("Đã lấy được giờ: " + returned);  
      Serial.print("Trả giờ cho tài khoản yêu cầu:");
      Serial.println(Sdt);
      Gsm_MakeSMS(Sdt,returned); 
      returned = "";                                   // Xoa bo dem
      disconnected();
      
   }
    else
    {
      Index = -1; 
      digitalWrite(RELAY, HIGH); 
      Serial.println("Thất bại, gửi lại: " + returned);
      returned = "";
      goto times;
    }
    returned = "";                                                                   // Xoa bo dem
                                                 // Dong Relay de bat den // Bat bong den
  }
  
}





void serialEvent() {                                          // Chuong trinh ngat nhan du lieu sự kiện trả về
  while (mySerial.available()) {                               // Doi den khi co du lieu nhan ve
    // get the new byte:
    char inChar = (char)mySerial.read();                  // Doc mot byte du lieu vua nhan ve
    returned += inChar;                          // Ghi byte do vao bo dem nhan RxBuff (ta se xu ly RxBuff trong vong loop())
    
    if (returned.length() >= 128)                            // Neu bo dem qua dai thi xoa bo dem di
    {
    returned = "";
    }
  }
  
}


void runUtilOk(String cmd, String okCondition, int delays) //s sánh phản hồi trả về từ sim
{
  
  mySerial.println(cmd);
  delay(delays);
  serialEvent();   
  Index = returned.indexOf(okCondition);
  if (Index >= 0)                   // Neu tim thay "LAMP_ON" trong RxBuff
  {
    Index = -1; 
    digitalWrite(RELAY, LOW);                                           
    Serial.println("Thành công: " + returned);  
    returned = "";                                   // Xoa bo dem
  }
    else
    {
    Index = -1; 
    digitalWrite(RELAY, HIGH); 
    Serial.println("Thất bại, gửi lại: " + returned);
    returned = "";
    runUtilOk(cmd, okCondition, delays);
    }
}



void updateSerial()      
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port

  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port

  }
}

void Gsm_Init()          // cài đặt modul
{
           //Once the handshake test is successful, it will back to OK
  runUtilOk("AT", "OK", 2000);
  runUtilOk("ATE1", "OK", 2000);            // Tat che do phan hoi (Echo mode)
  runUtilOk("AT+CMGF=1", "OK", 2000);      // Chon che do TEXT Mode
  runUtilOk("AT+CLIP=1", "OK", 2000);           // Hien thi thong tin nguoi goi den
  runUtilOk("AT+CNMI=1,2,0,0,0", "OK", 2000);    // Hien thi truc tiep noi dung tin nhan mới


}

void Gsm_MakeCall(String phone)    //gọi điện
{
  runUtilOk("ATD" + phone + ";", "OK", 10000);
  runUtilOk("ATH", "OK", 2000);
}

void Gsm_MakeSMS(String phone, String content)  //gửi sms
{
  runUtilOk("AT+CMGS=\"" + phone + "\"", "OK", 3000);   //Gửi tin nhắn                                                   // Cho ky tu '>' phan hoi ve
  mySerial.print(content);                                          // Gui noi dung
  updateSerial();
  delay(500);
  mySerial.print((char)26);                                         // Gui Ctrl+Z hay 26 de ket thuc noi dung tin nhan va gui tin di
  updateSerial();
  delay(2000);                                                      // delay 5s
}


void ConnectServer(String ip, String port)    //kết nối tới server
{
  mySerial.println("AT+CGATT?");  //kiểm tra trạng thái GPRS
  delay(2000);
  serialEvent();   
  Index = returned.indexOf("1");
  if (Index >= 0)                  
  {
    Index = -1; 
    digitalWrite(RELAY, LOW);                                           
    Serial.println("Đã bật GPRS:" + returned);  
    returned = "";                                   
  }
    else
    {
    Index = -1; 
    digitalWrite(RELAY, HIGH); 
    Serial.println("Chưa bật GPRS:" + returned);
    runUtilOk("AT+CGATT=1", "1", 2000);
    returned = "";
    }
  
  mySerial.println("AT+CIPMUX?");     // Cài Sim800A ở chế độ Single Connection.
  delay(2000);
  updateSerial();
  mySerial.println("AT+CIPMode?");   //Bắt đầu tác vụ và đặt APN, TÊN NGƯỜI DÙNG, PASSWORD
  delay(2000);
  updateSerial();
//  runUtilOk("AT+CSTT=\"CMNET\"","OK",2000);  //;Bắt đầu tác vụ và đặt APN, TÊN NGƯỜI DÙNG, PASSWORD
  runUtilOk("AT+CIICR","OK",2000);   //Kết nối không dây với GPRS
  mySerial.println("AT+CIFSR");   //Nhận địa chỉ IP cục bộ
  delay(2000);
  updateSerial();
  //  chaylai();
  ip:
  mySerial.println("AT+CIPSTART=\"TCP\",\"" + ip + "\",\"" + port + "\"");   //Kết nối với Server theo TCP, Sim800A đóng vai trò TCP Client
  delay(2000);;
  serialEvent();   
  Index = returned.indexOf("OK");
  if (Index >= 0)                   // Neu tim thay
  {
    Index = -1; 
    digitalWrite(RELAY, LOW);                                           
    Serial.println("Thành công: " + returned);  
    returned = "";                        // Xoa bo dem
    delay(3000);
    serialEvent();   
    Index = returned.indexOf("CONNECT OK");
    if (Index >= 0)                   // Neu tim thay 
    {
      Index = -1; 
      digitalWrite(RELAY, LOW);                                           
      Serial.println("Connect Ok: " + returned);  
      returned = "";         
    }
    else
    {
      Index = -1; 
      digitalWrite(RELAY, HIGH); 
      Serial.println("Thất bại, gửi lại: " + returned);
      returned = "";
      goto ip;
    }
  }
  else
    {
    Index = -1; 
    digitalWrite(RELAY, HIGH); 
    Serial.println("Thất bại, gửi lại: " + returned);
    returned = "";
    goto ip;
    }
//  runUtilOk("AT+CIPSTART=\"TCP\",\"" + ip + "\",\"" + port + "\"", "server", 5000); 
}

void disconnected()
{
  runUtilOk("AT+CGATT=0", "OK", 2000);
  runUtilOk("AT+CIPCLOSE", "OK", 2000);
  runUtilOk("AT+CIPSHUT", "OK", 2000);
}

void Makesendserver(String content)
{

  runUtilOk("AT+CIPSEND", "OK", 3000);
  mySerial.println(content);
  delay(2000);
  updateSerial();
  mySerial.println((char)26);
  delay(2000);
  updateSerial();
}
