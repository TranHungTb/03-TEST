//


static const unsigned char PROGMEM  Boss[] =
{ 
0XFC,0X00,0XFC,0X00,0XFC,0X00,0X1F,0X80,0X1F,0X80,0X1F,0X80,0XFC,0X00,0XFC,0X00,
0XFC,0X00
};
static const unsigned char PROGMEM  Player[] =
{ 
  0XFC,0X00,0XFC,0X00,0XFC,0X00,0XFF,0X80,0XFF,0X80,0XFF,0X80,0XFC,0X00,0XFC,0X00,
0XFC,0X00
};
static const unsigned char PROGMEM  Player2[] =
{ 
0XFE,0X00,0XAA,0X00,0XFE,0X40,0X93,0XC0,0XFB,0XC0,0XFB,0XC0,0X92,0X40,0XFE,0X00,
0XAA,0X00,0XFE,0X00
};

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>         //download here: https://www.electronoobs.com/eng_arduino_Adafruit_GFX.php
#include <Adafruit_SSD1306.h>     //downlaod here: https://www.electronoobs.com/eng_arduino_Adafruit_SSD1306.php
//#define OLED_RESET 5
Adafruit_SSD1306 display(128, 64);
//Adafruit_SSD1306 display(OLED_RESET);
//#define NUMFLAKES 10
//#define XPOS 0
//#define YPOS 1
//#define DELTAY 2

const int left = 2;// nút số 1
const int up = 3;// nút số 2
const int right = 4;// nút số 3
const int down = 5;// nút số 4
const int POWER = 6;// nút Power
int led = 13;
uint8_t x = 0;
uint8_t y = 0;
void setup()
{

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32 or 64 from eBay)
  delay(100);
  display.clearDisplay();
  display.display();
  delay(100);

  
  Serial.begin(9600);
  /* điện trở nội kéo lên cho tất cả nút bấm*/
  pinMode(left, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(POWER, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
}

void loop()
{ 
  
  display.clearDisplay();
  
  display.drawBitmap( x,y, Player2, 10, 10, 1);          
  display.display();//Finally display the created image

  if (digitalRead(left) == 0)// khi nút RED được nhấn
  {
   x--;
   if(x<1){x=128;}
   delay(50);
    Serial.println("ra ánh sáng.");
    digitalWrite(led,1);
  }
  if (digitalRead(right) == 0)
  {
  x++; 
  if(x>128){x=0;}
  digitalWrite(led,0);
  delay(50);
}

 if (digitalRead(up) == 0)// khi nút RED được nhấn
  {
   y--;
   if(y<1){y=64;}
   delay(50);
    Serial.println("ra ánh sáng.");
    digitalWrite(led,1);
  }
  if (digitalRead(down) == 0)
  {
  y++; 
  if(y>64){y=0;}
  digitalWrite(led,0);
  delay(50);
}

}
