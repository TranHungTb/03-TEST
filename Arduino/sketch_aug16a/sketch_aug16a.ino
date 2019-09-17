#include <SoftwareSerial.h>
#include <Servo.h>      // Thư viện điều khiển servo
 
// Khai báo đối tượng myservo dùng để điều khiển servo
Servo myservo;   
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2



const String myphone = "0929034450";     // Thay so cua ban vao day
const int RELAY =  13;                              // Chan so 12 arduino uno dung lam chan dieu khien dong/cat Relay de On/Off den
int n;
int servoPin = A0;

String RxBuff = "";                                    // Khai bao bo dem nhan du lieu
String returned = "";                                // Tat ca du lieu nhan ve tu module sim deu duoc luu trong day
boolean newline = false;
String Sdt="";
int Index= -1;                           // vi tri cua chuoi returned
int Index_Lamp_On = -1;                           // vi tri cua chuoi "LAMP_ON"
int Index_Lamp_Off = -1;                           // vi tri cua chuoi "LAMP_OFF"

void baochay();
void serialEvent();
void runUtilOk(String cmd, String okCondition, int delays);
void updateSerial();
void Gsm_Init();                                    // Cau hinh Module Sim800C
void Gsm_MakeCall(String phone);                   // Ham goi dien
void Gsm_MakeSMS(String phone, String content);    // Ham nhan tin
//void ConnectServer(String ip, String port);
//void disconnected();
//void Makesendserver(String content);



void setup()
{

  Serial.begin(9600);

  mySerial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(0);
  Serial.println("Initializing...");
  delay(1000);
  digitalWrite(RELAY, LOW);               // Khai bao chan  de dieu khien dong cat RELAY
  pinMode(RELAY, OUTPUT);

  delay(5000);                                              // Đợi module sim kiểm tra kết nối mạng GSM


  Gsm_Init();                                                 // Cau hinh module Sim800C
//  Gsm_MakeCall(myphone);                          // Test cuoc goi
  // Gsm_MakeSMS(myphone,"I'm a test");       // Test tin nhan
//  ConnectServer("138.197.46.187", "1347/level");
//    mySerial.println("at+cipstart=\"tcp\",\"138.197.46.187\",\"1347/level\"");
  //  delay(2000);

runUtilOk2("AT+CUSD=1,\"*101#\"", "TKC", 4000); 

//serialEvent();
//
//Serial.println("Thành: " + returned);
//delay(100);
//serialEvent();
//
//Serial.println("Thành2: " + returned);
  //  Makesendserver("times");

}
void displayMyserialData() {
  while(mySerial.available()) {
    Serial.print("\n>>>" + mySerial.readString());
  }
}
void loop() {
  
  
}

void serialEvent() {                                          // Chuong trinh ngat nhan du lieu sự kiện trả về
  while (mySerial.available()) {                               // Doi den khi co du lieu nhan ve
    returned = mySerial.readString();
  }
//  returned +="|";
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
void runUtilOk2(String cmd, String okCondition, int delays) //s sánh phản hồi trả về từ sim
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
    Gsm_MakeSMS(myphone,returned);
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
    Serial.println(">");
  }
  Serial.println("|");
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
  runUtilOk("ATD" + phone + ";", "OK", 3000);
  delay(7000);
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
