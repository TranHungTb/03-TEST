#include <SoftwareSerial.h>
#include <Servo.h>      // Thư viện điều khiển servo
 
// Khai báo đối tượng myservo dùng để điều khiển servo
Servo myservo;   
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2



const String myphone = "0972154901";     // Thay so cua ban vao day
const int RELAY =  13;                              // Chan so 12 arduino uno dung lam chan dieu khien dong/cat Relay de On/Off den
int n;
int servoPin = 5;

String RxBuff = "";                                    // Khai bao bo dem nhan du lieu
String returned = "";                                // Tat ca du lieu nhan ve tu module sim deu duoc luu trong day
boolean newline = false;
String Sdt="";
int Index= -1;                           // vi tri cua chuoi returned
int Index_Lamp_On = -1;                           // vi tri cua chuoi "LAMP_ON"
int Index_Lamp_Off = -1;                           // vi tri cua chuoi "LAMP_OFF"

void ktweb();
void get_http();
int getLevel(String dataIncludeLevel);
void baochay();
void serialEvent();
void updateSerial();  
void runUtilOk(String cmd, String okCondition, int delays);
void Check_Account();
void Gsm_Init();                                    // Cau hinh Module Sim800C
void Gsm_MakeCall(String phone);                   // Ham goi dien
void Gsm_MakeSMS(String phone, String content);    // Ham nhan tin
void ConnectServer(String ip, String port);
void disconnected();
void Makesendserver(String content);
void Check_Account();
void set_http();


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
  Gsm_MakeCall(myphone);                          // Test cuoc goi
  // Gsm_MakeSMS(myphone,"I'm a test");       // Test tin nhan
//  ConnectServer("138.197.46.187", "1347/level");
//    mySerial.println("at+cipstart=\"tcp\",\"138.197.46.187\",\"1347/level\"");



  //  Makesendserver("times");
Serial.println("Starti...");
}
void displayMyserialData() {
  while(mySerial.available()) {
    Serial.print("\n>>>" + mySerial.readString());
  }
}
void loop() {

  serialEvent();                                                                    // tre 1s
  Index_Lamp_On = returned.indexOf("cap");              // Tim vi tri cua chuoi "LAMP_ON" trong bo dem nhan RxBuff

  if (Index_Lamp_On >= 0)                                                  // Neu tim thay "LAMP_ON" trong RxBuff
  {
    digitalWrite(RELAY, LOW);
    Index_Lamp_On = -1;                                                     
    Serial.println("Nhận tin báo cháy:" + returned);
    Sdt = returned.substring(9, 21);
    Serial.print("Số điện thoại cảnh báo cháy:");
    Serial.println(Sdt);
    baochay(); 
//    Serial.println("kiểm tra số điện thoại.");
//    if(Sdt=="+84972154901")
//    {
//     Serial.println("Số điện thoại có quyền thực hiện thay đổi báo cháy.");
//     baochay(); 
//    }
//    else
//    {
//     Serial.println("Số điện thoại không có quyền thay đổi báo cháy.");
//    }
 }
}

void ktweb()(
//    mySerial.println("AT+HTTPPARA=\"URL\",\"http://138.197.46.187:1347/level/\"");// setting the httppara, 
//   //the second parameter is the website from where you want to access data   
//   delay(1000);
//   mySerial.println();
//      while (mySerial.available())
//  {
//    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
//  }
////   serialEvent();
////   mySerial.println();
//   mySerial.println("AT+HTTPACTION=0");//submit the GET request 
//   delay(6000);//the delay is important if the return datas are very large, the time required longer.
////  serialEvent();
//     while (mySerial.available())
//  {
//    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
//  }
//   mySerial.println("AT+HTTPREAD=0,150");// read the data from the website you access
//   delay(4000); 
////     while (mySerial.available())
////  {
////    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
////  }
//     serialEvent();
//   if(returned != ret){
//   if (returned.indexOf("cap") >= 0)                                                  // Neu tim thay "LAMP_ON" trong RxBuff
//  {
//    ret = returned;                                                  
//    Serial.println("Nhận tin báo cháy từ web:" + returned);
//    baochay();
//    }
//  }      
}
      
void get_http()
{
    mySerial.println("AT+HTTPPARA=\"URL\",\"http://138.197.46.187:1347/level\"");// setting the httppara, 
   //the second parameter is the website from where you want to access data 
   delay(1000);
   serialEvent();
   
   mySerial.println();
   mySerial.println("AT+HTTPACTION=0");//submit the GET request 
   delay(8000);//the delay is important if the return datas are very large, the time required longer.
   serialEvent();;
   mySerial.println("AT+HTTPREAD=0,150");// read the data from the website you access
   delay(3000);
        
}
/**
 * Input: string gia tri lay tu myserial
 * Output: cap do chay
 */
int getLevel(String dataIncludeLevel) {
  if (dataIncludeLevel.indexOf("00630061007000200035") >= 0||dataIncludeLevel.indexOf("cap 5") >= 0) {
    return 0; // cấp 5
  }
  if (dataIncludeLevel.indexOf("00630061007000200034") >= 0||dataIncludeLevel.indexOf("cap 4") >= 0) {
    return 36;  // cấp 4
  }
  if (dataIncludeLevel.indexOf("00630061007000200033") >= 0||dataIncludeLevel.indexOf("cap 3") >= 0) {
    return 77;  // cấp 3
  }
  if (dataIncludeLevel.indexOf("00630061007000200032") >= 0||dataIncludeLevel.indexOf("cap 2") >= 0) {
    return 118;  // cấp 2
  }
  if (dataIncludeLevel.indexOf("00630061007000200031") >= 0||dataIncludeLevel.indexOf("cap 1") >= 0) {
    return 158;  // cấp 1
  }
  return -1;
}

void baochay()
{
  int level = getLevel(returned);

  if (level == -1) {
    Serial.println("Không tìm thấy cấp độ báo cháy." + returned); 
    returned = "";   
  } 
  else {
    Serial.println("Báo cháy cấp " + level);  
    myservo.write(level);

    
    runUtilOk("AT+CMGDA=\"DEL ALL\"","OK",1000);  // Xóa toàn bộ tin nhắn 
    returned = ""; 
  }
}  
 


void serialEvent() {                                          // Chuong trinh ngat nhan du lieu sự kiện trả về
  while (mySerial.available()) {                               // Doi den khi co du lieu nhan ve
    returned = mySerial.readString();
  }
//  returned +="|";
}

//void serialEvent() {                                          // Chuong trinh ngat nhan du lieu
//  while (mySerial.available()) {                               // Doi den khi co du lieu nhan ve
//    // get the new byte:
//    char inChar = (char)Serial.read();                  // Doc mot byte du lieu vua nhan ve
//    returned += inChar;                                       // Ghi byte do vao bo dem nhan RxBuff (ta se xu ly RxBuff trong vong loop()) 
//    if(returned.length()>= 200)                              // Neu bo dem qua dai thi xoa bo dem di
//    {
//      returned = "";
//    }
//  }
//}
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



void Check_Account(){
  
  mySerial.println("AT+CUSD=1,\"*101#\"");
//  mySerial.println("ATD*101#;");
  delay(5000);
  serialEvent(); 
  Serial.println("Báo cháy cấp11111: " + returned);  
  if(returned.length()<50){
   Check_Account();  
  }
  else{
   Serial.println("Báo cháy cấp: " + returned); 
  Sdt = returned.substring(36,170); 
  Serial.println("Starti..." + Sdt); 

  }
 
  
}


void Gsm_Init()          // cài đặt modul
{
           //Once the handshake test is successful, it will back to OK
  runUtilOk("AT", "OK", 2000);
  runUtilOk("ATE1", "OK", 2000);            // Bật che do phan hoi (Echo mode)
  runUtilOk("AT+CMGF=1", "OK", 2000);      // Chon che do TEXT Mode
  runUtilOk("AT+CLIP=1", "OK", 2000);           // Hien thi thong tin nguoi goi den
  runUtilOk("AT+CNMI=2,2", "OK", 2000);    // Hien thi truc tiep noi dung tin nhan mới


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
  
  mySerial.println("AT+CIPMUX?");     // Cài Sim800A ở chế độ Single Connection.0 Kết nối IP đơn1 kết nối nhiều IP
  delay(2000);
  updateSerial();
  mySerial.println("AT+CIPMode?");   //Bắt đầu tác vụ và đặt APN, TÊN NGƯỜI DÙNG, PASSWORD
  delay(2000);
  updateSerial();
//  runUtilOk("AT+CSTT=\"CMNET<CR><LF>\"","OK",2000);  //;Bắt đầu tác vụ và đặt APN, TÊN NGƯỜI DÙNG, PASSWORD
  mySerial.println("AT+CSTT?");   //Bắt đầu tác vụ và đặt APN, TÊN NGƯỜI DÙNG, PASSWORD
  delay(2000);
  updateSerial();
//  runUtilOk("AT+CIICR","OK",2000);   //Kết nối không dây với GPRS
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
  runUtilOk("AT+CIPSTART=\"TCP\",\"" + ip + "\",\"" + port + "\"", "server", 5000); 
}

//void disconnected()
//{
//  runUtilOk("AT+CGATT=0", "OK", 2000);
//  runUtilOk("AT+CIPCLOSE", "OK", 2000);
//  runUtilOk("AT+CIPSHUT", "OK", 2000);
//}
//
//void Makesendserver(String content)
//{
//
//  runUtilOk("AT+CIPSEND", "OK", 3000);
//  mySerial.println(content);
//  delay(2000);
//  updateSerial();
//  mySerial.println((char)26);
//  delay(2000);
//  updateSerial();
//}

void Check_Account(){
  mySerial.println("AT+CUSD=1,\"*101#\"");
  delay(5000);
  serialEvent();  
  delay(20);
  if(returned.length()<30){
    Check_Account();
  }
  Serial.println("Báo cháy cấp: " + returned); 
  Sdt = returned.substring(33, 170); 
  Serial.println("Starti..." + Sdt);
}

void set_http()
{
 
 delay(500); 
  mySerial.println("AT+HTTPTERM");// terminate HTTP service
  delay(500);
 updateSerial();
 mySerial.println("AT+CGATT=1");
 delay(200);
 updateSerial();
 
 mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR,connection type is GPRS
 delay(1000);
 updateSerial();
 
 mySerial.println("AT+SAPBR=3,1,\"APN\",\"\"");//setting the APN,2nd parameter empty works for all networks 
 delay(5000);
 updateSerial();
 
 mySerial.println();
 mySerial.println("AT+SAPBR=1,1");
 delay(10000);
 updateSerial();
 
 mySerial.println("AT+HTTPINIT"); //Khởi tạo yêu cầu HTTP
 delay(2000); 
 updateSerial();

}
