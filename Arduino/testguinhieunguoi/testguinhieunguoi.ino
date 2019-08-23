const String numberPhones[] = {"0929034450"}; //danh sách số điện thoại

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

int RELAY =  13;  
int mic,i;                                           // Bat module Sim 900A
void Gsm_Init();                                                       // Cau hinh Module Sim 900A
void Gsm_MakeCall(String phone);                            // Ham goi dien
void Gsm_MakeSMS(String phone,String content);     // Ham nhan tin


 void setup() {
  Serial.begin(9600);                           // Cau hinh UART de giao tiep module Sim 900A
 Serial.println (NUMITEMS (numberPhones));
  
  digitalWrite(RELAY, LOW);               // Khai bao chan  de dieu khien dong cat RELAY
  pinMode(RELAY, OUTPUT);
  pinMode(A0, INPUT);
                                    // Bat Module Sim 900A
  delay(10000);
  Gsm_Init();                         // Cau hinh module Sim 900A
  Gsm_MakeCall(numberPhones[0]);                          // Test cuoc goi 
 // Gsm_MakeSMS(numberPhones[0],"Test su hoat dong",mic);       // Test tin nhan
}


void loop() {

   delay(1000);                  //tre 1s 
  mic = analogRead(A0);                          
  Serial.print("mic: "); 
  Serial.println(mic);             
  if(mic >= 700)                                            
  {                                                  
    digitalWrite(RELAY, HIGH);                          // Bat bong den
     delay(1000); 
      for(i=0;i<NUMITEMS(numberPhones);i++){
      delay(1000);   
      Gsm_MakeSMS(numberPhones[i],"Noi nho di. Do on: ",mic); 
    
  }
  }
  else
  {                           
                                        
      digitalWrite(RELAY, LOW);               // Cat Relay de tat den
    }
 
}
 
//void serialEvent() {                                          // Chuong trinh ngat nhan du lieu
//  while (Serial.available()) {                               // Doi den khi co du lieu nhan ve
//    // get the new byte:
//    char inChar = (char)Serial.read();                  // Doc mot byte du lieu vua nhan ve
//    RxBuff += inChar;                           // Ghi byte do vao bo dem nhan RxBuff (ta se xu ly RxBuff trong vong loop()) 
//    if(RxBuff.length()>= 128)                              // Neu bo dem qua dai thi xoa bo dem di
//    {
//      RxBuff = "";
//    }
//  }
//}
 

void Gsm_Init()
{
  Serial.println("ATE0");                            // Tat che do phan hoi (Echo mode)
  delay(2000);
  Serial.println("AT+IPR=9600");              // Dat toc do truyen nhan du lieu 9600 bps
  delay(2000);
  Serial.println("AT+CMGF=1");                // Chon che do TEXT Mode để viết tin nhắn kiểu text
  delay(2000);
  Serial.println("AT+CLIP=1");                  // Hien thi thong tin nguoi goi den
  delay(2000);
  Serial.println("AT+CNMI=2,2");              // Hien thi truc tiep noi dung tin nhan
  delay(2000);
}
 
void Gsm_MakeCall(String phone)           
{
  Serial.println("ATD" + phone + ";");         // Goi dien 
  delay(10000);                                        // Sau 10s
  Serial.println("ATH");                              // Ngat cuoc goi
  delay(2000);
}
 
void Gsm_MakeSMS(String phone,String content,int mic)
{
  Serial.println("AT+CMGS=\"" + phone + "\"");     // Lenh gui tin nhan
  delay(2000);                                                     // Cho ky tu '>' phan hoi ve 
  Serial.print(content);                                          // Gui noi dung 
  Serial.print(mic);
  delay(2000);
  Serial.println((char)26);                                         // Gui Ctrl+Z hay 26 de ket thuc noi dung tin nhan va gui tin di
  
  delay(2000);                                                      // delay 5s
}
 
