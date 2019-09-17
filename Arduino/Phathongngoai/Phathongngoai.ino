#include <IRremote.h>
IRsend irsend;// gửi tín hiệu hồng hoại
const int CH1 = 5;// nút số 1
const int CH2 = 8;// nút số 2
const int CH3 = 9;// nút số 3
const int POWER = 10;// nút Power
void setup()
{
  Serial.begin(9600);
  /* điện trở nội kéo lên cho tất cả nút bấm*/
  pinMode(CH1, INPUT_PULLUP);
  pinMode(CH2, INPUT_PULLUP);
  pinMode(CH3, INPUT_PULLUP);
  pinMode(POWER, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(CH1) == 1)// khi nút RED được nhấn
  {
    
    Serial.println("ra ánh sáng.");
    irsend.sendSony(0x807FC03F, 32);// gửi tín hiệu HEX 0x10, 12 bits
  }
  else if (digitalRead(CH2) == 0)// khi nút YELLOW được nhấn
    irsend.sendSony(0x810, 12);// gửi tín hiệu HEX 0x810, 12 bits
  else if (digitalRead(CH3) == 0)// khi nút GREEN được nhấn
    irsend.sendSony(0x410, 12);// gửi tín hiệu HEX 0x410, 12 bits
  else if (digitalRead(POWER) == 0)// khi nút POWER được nhấn
    irsend.sendSony(0xA90, 12);// gửi tín hiệu HEX 0xA90, 12 bits
  delay(50);
}
