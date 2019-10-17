
#include <SoftwareSerial.h>
#include <Sodaq_wdt.h>
#include <Servo.h>      // Thư viện điều khiển servo

// Khai báo đối tượng myservo dùng để điều khiển servo
Servo myservo;   
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2



const String myphone = "0972154901";     // Thay so cua ban vao day

int servoPin = A0;
int Index= -1;  
int addr = 0;//địa chỉ EEPROM mà ta sẽ lưu đầu tiên

short int i;
short int level = 170;

String cap ="";              
String tk = "";           //thông tin tài khoản
String returned = "";       // Tat ca du lieu nhan ve tu module sim deu duoc luu trong day
String sdt="";             // sđt nhắn đến  
                         

void baochay();             // hàm thực hiện quay bảng
void serialEvent();         // bắt sự kiện
void runUtilOk(String cmd, String okCondition, int delays);   // kiểm tra lệnh at
void updateSerial();          //bắt sự kiển cổng này ghi vào cổng còn lại
void Gsm_Init();                                    // Cau hinh Module Sim800C
void Gsm_MakeCall(String phone);                   // Ham goi dien
void Gsm_MakeSMS(String phone, String content);    // Ham nhan tin
void Check_Account();



void setup()
{

  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(servoPin);
  
  Serial.println("Initializing...");
  pinMode(4,OUTPUT);
  digitalWrite(4,1);
                                               // Đợi module sim kiểm tra kết nối mạng GSM
  myservo.write(level);
  delay(2000); 
  digitalWrite(4,0);
  Gsm_Init();   

Serial.println("Starti...");
}

void loop() {

  serialEvent();  
  delay(20);    

  if (returned.indexOf("Cap") >= 0||returned.indexOf("cap") >= 0||returned.indexOf("6300610070") >= 0||returned.indexOf("4300610070") >= 0 )                                                  // Neu tim thay "LAMP_ON" trong RxBuff
  {
    
                                                     
    Serial.println("Nhận tin báo cháy:" + returned);
    sdt = returned.substring(9, 21);
    Serial.print("Số điện thoại cảnh báo cháy:");
    Serial.println(sdt);
    baochay(); 
 }
 else{
  if(returned.length()>20){
    runUtilOk("AT+CMGDA=\"DEL ALL\"","OK",1000);  // Xóa toàn bộ tin nhắn 
     // kiểm tra tin nhắn
  delay(2000); 
 }
 }
}
 



/**
 * Input: string gia tri lay tu myserial
 * Output: cap do chay
 */
void getLevel(String dataIncludeLevel) {
  if (dataIncludeLevel.indexOf("00630061007000200035") >= 0||dataIncludeLevel.indexOf("00430061007000200035") >= 0||dataIncludeLevel.indexOf("cap 5") >= 0||dataIncludeLevel.indexOf("Cap 5") >= 0)  {
    cap = "Cap 5 ";
    level = 23;  // cấp 5
  }
  else{
  if (dataIncludeLevel.indexOf("00630061007000200034") >= 0||dataIncludeLevel.indexOf("00430061007000200034") >= 0||dataIncludeLevel.indexOf("cap 4") >= 0||dataIncludeLevel.indexOf("Cap 4") >= 0)  {
    cap = "Cap 4 ";
    level = 57;  // cấp 4
  }
  else{
  if (dataIncludeLevel.indexOf("00630061007000200033") >= 0||dataIncludeLevel.indexOf("00430061007000200033") >= 0||dataIncludeLevel.indexOf("cap 3") >= 0||dataIncludeLevel.indexOf("Cap 3") >= 0)  {
    cap = "Cap 3 ";
    level = 72+26;  // cấp 3
  }
  else{
  if (dataIncludeLevel.indexOf("00630061007000200032") >= 0||dataIncludeLevel.indexOf("00430061007000200032") >= 0||dataIncludeLevel.indexOf("cap 2") >= 0||dataIncludeLevel.indexOf("Cap 2") >= 0)  {
    cap = "Cap 2 ";
    level = 127;  // cấp 2
  }
  else{
  if (dataIncludeLevel.indexOf("00630061007000200031") >= 0||dataIncludeLevel.indexOf("00430061007000200031") >= 0||dataIncludeLevel.indexOf("cap 1") >= 0||dataIncludeLevel.indexOf("Cap 1") >= 0)  {
    cap = "Cap 1 ";
    level = 170;  // cấp 1
  }
  else{
  level = -1;
}}}}}}


void baochay()
{
  getLevel(returned);
//   int lever = getLevel(returned);
//  cap = returned.substring(50, 100);
  if (level == -1) {
    Serial.println("Không tìm thấy cấp độ báo cháy." + returned); 
    returned = "";   
  } 
  else {
    digitalWrite(4,1);
    Serial.println("Thực hiện lệnh:" + cap + "Ok");  
    myservo.write(level);
//    Check_Account(); // kieerm tra tk
//    Gsm_MakeSMS(sdt, "Lenh bao chay:" + cap + "Ok.\r\n" + tk );  
    delay(1000); // để động cơ đổi vị trí 
    returned = "";   
    digitalWrite(4,0);
  }
  
}  
 


void serialEvent() {                                          // Chuong trinh ngat nhan du lieu sự kiện trả về
  while (mySerial.available()) {  
     // Doi den khi co du lieu nhan ve
    returned = mySerial.readString();
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

void runUtilOk(String cmd, String okCondition, int delays) //s sánh phản hồi trả về từ sim
{
  mySerial.println(cmd);
  delay(delays);
  serialEvent();   
  Index = returned.indexOf(okCondition);
  if (Index >= 0)                   // Neu tim thay "LAMP_ON" trong RxBuff
  {
    Index = -1;          
    i = 0;                              
    Serial.println("Thành công: " + returned);  
    returned = "";     
    
  }
    else
    {
    Index = -1; 
    i++;
    Serial.println("Thất bại, gửi lại: " + returned);
    returned = "";
    if(i > 5){
      sodaq_wdt_enable(WDT_PERIOD_2X);
    }
    else{
     runUtilOk(cmd, okCondition, delays); 
    }
    
    
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


void Check_Account(){
  mySerial.println("AT+CUSD=1,\"*101#\"");
  delay(5000);
  serialEvent();  
  delay(20);
  if(returned.length()<50){
    Check_Account();
  }
  Serial.println("Kiểm tra tài khoản: " + returned); 
  tk = returned.substring(36, 130); 
  Serial.println("Số tài khoản: " + tk);
  mySerial.println("ATH");
}
