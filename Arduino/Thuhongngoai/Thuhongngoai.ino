#include <IRremote.h> // thư viện hỗ trợ IR remote

const int receiverPin = A0; // chân digital 8 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu

const int RED = 13;// LED đỏ
const int YELLOW = 6;// LED vàng
const int GREEN = 5;// LED xanh
/* trạng thái của các LEDs*/
boolean stateRED = false;
boolean stateYELLOW = false;
boolean stateGREEN = false;
void setup()
{
  Serial.begin(9600);// serial 
  irrecv.enableIRIn(); // start the IR receiver
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  irrecv.enableIRIn();
}
// translate IR signals
void translateIR()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    Serial.println(results.value, HEX); // in ra Serial Monitor
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
  
  switch(results.value)
  {
    case 0x807FC03F: stateRED = !stateRED; 
                digitalWrite(RED, stateRED); 
                Serial.println("mã hex: bạt tat led");
                break;
    case 0x810: stateYELLOW = !stateYELLOW; 
                digitalWrite(YELLOW, stateYELLOW); 
                break;
    case 0x410: stateGREEN = !stateGREEN; 
                digitalWrite(GREEN, stateGREEN);  
                break;
    case 0xA90: stateRED = stateYELLOW = stateGREEN = false;
                digitalWrite(RED, 0);
                digitalWrite(YELLOW, 0);
                digitalWrite(GREEN, 0);
  }
}
void loop()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    translateIR();
    Serial.println(results.value, HEX);
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}
