#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2



const String myphone = "0972154901";     // Thay so cua ban vao day
const int RELAY =  13;                              // Chan so 12 arduino uno dung lam chan dieu khien dong/cat Relay de On/Off den
 
String RxBuff = "";                                    // Khai bao bo dem nhan du lieu
String ab = "";                                                               // Tat ca du lieu nhan ve tu module sim deu duoc luu trong day 
                                                                
 struct person
{
    String names, phoneNumber, address;
};
int Index_Lamp_On = -1;                           // vi tri cua chuoi "LAMP_ON"
int Index_Lamp_Off = -1;                           // vi tri cua chuoi "LAMP_OFF"
 
void Gsm_Init();                                    // Cau hinh Module Sim800C
void Gsm_MakeCall(String phone);                   // Ham goi dien
void Gsm_MakeSMS(String phone,String content);     // Ham nhan tin
void updateSerial(); 

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
  Gsm_MakeCall(myphone);                          // Test cuoc goi 
  // Gsm_MakeSMS(myphone,"I'm a test");       // Test tin nhan
 


}

void loop() {
  updateSerial();
  serialEvent();
  
  delay(1000);                                                                    // tre 1s 
  Index_Lamp_On = ab.indexOf("On");              // Tim vi tri cua chuoi "LAMP_ON" trong bo dem nhan RxBuff
 
  if(Index_Lamp_On >= 0)                                                   // Neu tim thay "LAMP_ON" trong RxBuff
  {
    Index_Lamp_On = -1;                                                     // 
    Serial.println("tìm thấy" + ab);
    Serial.println("aaaaa");
    ab = "";                                                                   // Xoa bo dem
    digitalWrite(RELAY, HIGH);                                             // Dong Relay de bat den // Bat bong den
  }
  else
  {                                                  // Neu khong tim thay "LAMP_ON" thi tiep tuc tim "LAMP_OFF"
    Index_Lamp_Off = ab.indexOf("Off");          // Tim vi tri cua chuoi "LAMP_OFF" trong bo dem nhan RxBuff  
    if(Index_Lamp_Off >= 0)                                                // Neu tim thay "LAMP_OFF" trong RxBuff
    {
      
      Index_Lamp_Off = -1;                                                   // 
      ab = "";                                                                // Xoa bo dem
      digitalWrite(RELAY, LOW);                                           // Cat Relay de tat den
    }
  }
}




 
void serialEvent() {                                          // Chuong trinh ngat nhan du lieu
  while (mySerial.available()) {                               // Doi den khi co du lieu nhan ve
    // get the new byte:
    char inChar = (char)mySerial.read();                  // Doc mot byte du lieu vua nhan ve
    ab += inChar;                          // Ghi byte do vao bo dem nhan RxBuff (ta se xu ly RxBuff trong vong loop()) 
    Serial.println("Lưu" + ab);
    if(ab.length()>= 128)                              // Neu bo dem qua dai thi xoa bo dem di
    {
      ab = "";
    }
  }
  
}
 

 
void Gsm_Init()
{
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  delay(2000);
  mySerial.println("ATE1");                            // Tat che do phan hoi (Echo mode)
  updateSerial();
  delay(2000);
  mySerial.println("AT+IPR=9600");              // Dat toc do truyen nhan du lieu 9600 bps
  updateSerial();
  delay(2000);
 
  mySerial.println("AT+CMGF=1");                // Chon che do TEXT Mode
  updateSerial();
  delay(2000);
  mySerial.println("AT+CLIP=1");                  // Hien thi thong tin nguoi goi den
  updateSerial();
  delay(2000);
  mySerial.println("AT+CNMI=1,2,0,0,0");              // Hien thi truc tiep noi dung tin nhan mới
  updateSerial();
  delay(2000);
}
 
void Gsm_MakeCall(String phone)           
{
  mySerial.println("ATD" + phone + ";");         // Goi dien 
  updateSerial();
  delay(10000);                                        // Sau 10s
  mySerial.println("ATH");                              // Ngat cuoc goi
  updateSerial();
  delay(2000);
}
 
void Gsm_MakeSMS(String phone,String content)
{
  mySerial.println("AT+CMGS=\"" + phone + "\"");     // Lenh gui tin nhan
  updateSerial();
  delay(3000);                                                     // Cho ky tu '>' phan hoi ve 
  mySerial.print(content);                                          // Gui noi dung
  updateSerial();
  delay(1000); 
  mySerial.print((char)26);                                         // Gui Ctrl+Z hay 26 de ket thuc noi dung tin nhan va gui tin di
  updateSerial();
  delay(5000);                                                      // delay 5s
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
