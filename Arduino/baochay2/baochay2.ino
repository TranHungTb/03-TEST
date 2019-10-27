
#include <SoftwareSerial.h>
#include <Sodaq_wdt.h>      //thư viện để nhảy về dòng đầu tiên
#include <Servo.h>      // Thư viện điều khiển servo
#include <EEPROMex.h>         //Thư viện mở rộng eeprom
#include "Arduino.h"
// Khai báo đối tượng myservo dùng để điều khiển servo
Servo myservo;
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2



String myphone = "";     // Thay so cua ban vao day

int a;
int servoPin = A0;
int Index = -1;
int addressCharArray = 0;          //địa chỉ EEPROM mà ta sẽ lưu đầu tiên
const int maxAllowedWrites = 80;            //Số byte giới hạn
const int memBase          = 0;           //địa chỉ đọc đầu tiên eeprom
short int i;                  //biến đếm số lần lặp lại lỗi
short int level = 170;   // góc ban đầu servo


char input[10] = "";              // đầu vào hàm ghi eeprom
char output[10] = "";             //đầu ra hàm đọc eeprom


String cap = "";
String tk = "";           //thông tin tài khoản
String returned = "";       // Tat ca du lieu nhan ve tu module sim deu duoc luu trong day
String sdt = "";           // sđt nhắn đến


void baochay();             // hàm thực hiện quay bảng
void serialEvent();         // bắt sự kiện
void runUtilOk(String cmd, String okCondition, int delays);   // kiểm tra lệnh at
void updateSerial();          //bắt sự kiển cổng này ghi vào cổng còn lại
void Gsm_Init();                                    // Cau hinh Module Sim800C
void Gsm_MakeCall(String phone);                   // Ham goi dien
void Gsm_MakeSMS(String phone, String content);    // Ham nhan tin
void Check_Account();
void writeAndReadCharArray();
void doisdt();

void setup()
{

  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(servoPin);

  Serial.println("Initializing...");
  pinMode(4, OUTPUT);
  digitalWrite(4, 1);

  // Bát đầu đọc từ vị trí memBase( địa chỉ 0) của EEPROM. đặt MaxiumSize thành EEPROMSizeUno
  // Viết trước membase hoạc xa hơn eepromsizeuno sẽ chỉ báo lỗi khi eepromex_debug được đặt
  EEPROM.setMemPool(memBase, EEPROMSizeUno);

  //Đặt ghi tối đa được phép ghi vào max ALLowedWrites
  //Ghi nhiều hơn sẽ chỉ báo lỗi khi EEPROMEX_debug được đặt
  EEPROM.setMaxAllowedWrites(maxAllowedWrites);// số byte cho phép lưu
  delay(100);
  Serial.println("");

  // Luôn lấy địa chỉ trước và theo cùng một thứ tự
  addressCharArray = EEPROM.getAddress(sizeof(char) * 10);


  // In số điện thoại đã lưu sẵn tron eeprom
  EEPROM.readBlock<char>(addressCharArray, output, 10);
  myphone = output;
  delay(100);
  Serial.print("myphone: ");
  Serial.println(myphone);

  myservo.write(level);
  delay(2000);
  digitalWrite(4, 0);
  Gsm_Init();
  Serial.print("Start... ");
}

void loop() {

  serialEvent();
  delay(20);
  if (returned.indexOf("Doi so") >= 0 || returned.indexOf("doi so") >= 0 || returned.indexOf("44006f006900200073006f") >= 0 || returned.indexOf("64006f006900200073006f") >= 0 )
  {
    doisdt();
  }
  else {
    if (returned.indexOf("Cap") >= 0 || returned.indexOf("cap") >= 0 || returned.indexOf("6300610070") >= 0 || returned.indexOf("4300610070") >= 0 )                                            // Neu tim thay "LAMP_ON" trong RxBuff
    {
      baochay();
    }
    else {
      if (returned.length() > 20) {
        runUtilOk("AT+CMGDA=\"DEL ALL\"", "OK", 1000); // Xóa toàn bộ tin nhắn
        // kiểm tra tin nhắn
        returned = "";
        delay(2000);
      }
    }
  }
}


/**
   Input: string gia tri lay tu myserial
   Output: cap do chay
*/
void getLevel(String dataIncludeLevel) {
  if (dataIncludeLevel.indexOf("00630061007000200035") >= 0 || dataIncludeLevel.indexOf("00430061007000200035") >= 0 || dataIncludeLevel.indexOf("cap 5") >= 0 || dataIncludeLevel.indexOf("Cap 5") >= 0)  {
    cap = "Cap 5 ";
    level = 13;  // cấp 5
  }
  else {
    if (dataIncludeLevel.indexOf("00630061007000200034") >= 0 || dataIncludeLevel.indexOf("00430061007000200034") >= 0 || dataIncludeLevel.indexOf("cap 4") >= 0 || dataIncludeLevel.indexOf("Cap 4") >= 0)  {
      cap = "Cap 4 ";
      level = 47;  // cấp 4
    }
    else {
      if (dataIncludeLevel.indexOf("00630061007000200033") >= 0 || dataIncludeLevel.indexOf("00430061007000200033") >= 0 || dataIncludeLevel.indexOf("cap 3") >= 0 || dataIncludeLevel.indexOf("Cap 3") >= 0)  {
        cap = "Cap 3 ";
        level = 88;  // cấp 3
      }
      else {
        if (dataIncludeLevel.indexOf("00630061007000200032") >= 0 || dataIncludeLevel.indexOf("00430061007000200032") >= 0 || dataIncludeLevel.indexOf("cap 2") >= 0 || dataIncludeLevel.indexOf("Cap 2") >= 0)  {
          cap = "Cap 2 ";
          level = 127;  // cấp 2
        }
        else {
          if (dataIncludeLevel.indexOf("00630061007000200031") >= 0 || dataIncludeLevel.indexOf("00430061007000200031") >= 0 || dataIncludeLevel.indexOf("cap 1") >= 0 || dataIncludeLevel.indexOf("Cap 1") >= 0)  {
            cap = "Cap 1 ";
            level = 170;  // cấp 1
          }
          else {
            level = -1;
          }
        }
      }
    }
  }
}


void baochay()
{
  Serial.println("Nhận tin báo cháy:" + returned);
  sdt = returned.substring(9, 21);
  Serial.print("Số điện thoại cảnh báo cháy:");
  Serial.println(sdt);
  // kiểm tra sđt
  if (sdt.indexOf(myphone) >= 0) {
    Serial.print("Số điện thoại Có quyền:");
    getLevel(returned);
    //   int lever = getLevel(returned);
    //  cap = returned.substring(50, 100);
    if (level == -1) {
      Serial.println("Không tìm thấy cấp độ báo cháy." + returned);
      returned = "";
    }
    else {
      digitalWrite(4, 1);
      Serial.println("Thực hiện lệnh:" + cap + "Ok");
      myservo.write(level);
      Check_Account(); // kieerm tra tk
      Gsm_MakeSMS(sdt, "Lenh bao chay:" + cap + "Ok.\r\n" + tk );
      delay(1000); // để động cơ đổi vị trí
      returned = "";
      digitalWrite(4, 0);
    }
  }
  else {
    Serial.print("Số điện thoại không Có quyền Báo cháy.");
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
    if (i > 5) {
      sodaq_wdt_enable(WDT_PERIOD_2X);
    }
    else {
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
  runUtilOk("AT+CLIP=1", "OK", 2000);       // Hien thi thong tin nguoi goi den
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
  mySerial.println(content);                                          // Gui noi dung
  updateSerial();
  delay(500);
  mySerial.println((char)26);                                         // Gui Ctrl+Z hay 26 de ket thuc noi dung tin nhan va gui tin di
  updateSerial();
  delay(2000);                                                      // delay 5s
}


void Check_Account() {
  mySerial.println("AT+CUSD=1,\"*101#\"");
  delay(5000);
  serialEvent();
  delay(20);
  if (returned.length() < 50) {
    Check_Account();
  }
  Serial.println("Kiểm tra tài khoản: " + returned);
  tk = returned.substring(36, 130);
  Serial.println("Số tài khoản: " + tk);
  mySerial.println("ATH");
}


// Test reading and updating a string (char array) to EEPROM
void writeAndReadCharArray(char input[]) {

  delay(1000);

  EEPROM.writeBlock<char>(addressCharArray, input, 10);
  EEPROM.readBlock<char>(addressCharArray, output, 10);
  delay(10); // delay 5ms để trước khi lưu giá trị tiếp theo
  Serial.print("adress: ");
  Serial.println(addressCharArray);
  Serial.print("input: ");
  Serial.println(input);
  Serial.print("output: ");
  Serial.println(output);
  Serial.println("");
}

void doisdt() {

  Serial.println("Nhận tin đổi số: ");
  Serial.println(returned);
  sdt = returned.substring(57, 67);
  Serial.print("Số điện thoại được đổi: ");
  Serial.println(sdt);

  //    Gsm_MakeSMS(sdt,"Ban da duoc quyen canh bao chay rung voi sdt: ");
  mySerial.println("AT+CMGS=\"" + sdt + "\"");  //Gửi tin nhắn
  // Cho ky tu '>' phan hoi ve
  updateSerial();
  delay(5000);
  mySerial.print("Ban da duoc quyen canh bao chay rung voi sdt: " );
  mySerial.println(sdt);    // Gui noi dung
  updateSerial();
  delay(500);
  mySerial.println((char)26);
  delay(10000);
  //    updateSerial();
  serialEvent();
  Serial.println("nhan tin xong: " + returned);
  Index = returned.indexOf("OK");

  if (Index >= 0) {
    Index = -1;
    Serial.println("Số điện thoại cần đổi đến hoạt động: " + returned);
    returned = "";

    sdt.toCharArray(input, 11); // chuyển string sang array
    Serial.println( input);

    EEPROM.writeBlock<char>(addressCharArray, input, 10);
    delay(10);
    EEPROM.readBlock<char>(addressCharArray, output, 10);
    delay(10); // delay 5ms để trước khi lưu giá trị tiếp theo
    Serial.print("adress: ");
    Serial.println(addressCharArray);
    Serial.print("input: ");
    Serial.println(input);
    Serial.print("output: ");
    Serial.println(output);
    Gsm_MakeSMS(myphone, "Yeu cau doi so dien thoai thanh cong toi so: " + sdt );
    myphone = ""; //cho myphone = rỗng

    for (i = 0; i < 10; i++) {
      myphone = myphone + output[i];
    }

    //    myphone = output;
    Serial.println("myphone: ");
    Serial.println(myphone);
    Serial.println("");
    sdt = "";
  }
  else {
    Index = -1;
    Serial.println("Đổi số thất bại với số: " + sdt);
    sdt = "";
    returned = "";
  }
}



void StringToChar(String string, char input[]) {


  for (a = 0; a < string.length() ; a++) {
    // chữ số có ý nghĩa nhất của bài đọc nằm ở vị trí 15 trong báo cáoString:
    char mostSignificantDigit = string.charAt(a);
    input[a] = string.charAt(i);
    Serial.println( input[a]);
  }
  Serial.println( input);
}

// driver code


//Kiểm tra tài khoản
//void kttk()
