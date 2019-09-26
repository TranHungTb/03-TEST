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
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define Phai 0
#define Len 90
#define Trai 180
#define Xuong 270

const int left = 2;// nút số 1
const int up = 3;// nút số 2
const int right = 4;// nút số 3
const int down = 5;// nút số 4
const int POWER = 6;// nút Power
int led = 13;
int x0  ;
int y0  ;
int w0 ;
int h0  ;
int x = 0 ;
int y = 0;

bool collide( int xa,int ya, int wa, int ha, int x0, int y0, int w0, int h0) {
  if (((xa < x0) && (wa + xa > x0)) ||
      ((x0 <= xa) && (w0 + x0 > xa))) {  // kiểm tra trục x
    if (((ya < y0) && (ha + ya > y0)) ||
        ((y0 <= ya) && (h0 + y0 > ya))) {  // kiểm tra trục y
      return true;
    }
  }
  return false;
}

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
//void action( int x, int y, int width, int high, const char* bitmap_name, unsigned  int time_delay,unsigned  int huong){
//    bool mirror=false;
//    if(huong==Trai){
//        mirror=true;// nếu đi sang trái thì xoay nhân vật về bên trái
//    }
//    display.Plus_Bitmap( x,y,width,high,bitmap_name,0,mirror,BLACK); 
//    display.display();
//    delay(time_delay);
//    display.display();
//    display.clearDisplay();
//}
// 
//void walk(int x, int y, unsigned int time_delay,unsigned int huong){
//    int denta=1;//  sang phải thì x tăng
//    if(huong==Trai){
//        denta=-1;// sang trái thì x giảm, denta phải âm
//    }
//    action(x,y,25,28,Player2, time_delay,huong);
//    action(x+3*denta,y,25,28,Player2, time_delay,huong);
//    action(x+6*denta,y,25,28,Player2, time_delay,huong);
//    action(x+9*denta,y,25,28,Player2, time_delay,huong);
//}


void loop()
{ 
  
  display.clearDisplay();
  
  display.drawBitmap( x0 ,y0 , Boss, 9, 9, 1);          
  display.display();
  
  display.drawBitmap( x,y, Player2, 10, 10, 1);          
  display.display();//Finally display the created image


  if (digitalRead(left) == 0)// khi nút RED được nhấn
  {
   x--;
   if(x<1){x=0;}
   delay(50);
  }
  
  if (digitalRead(right) == 0)
  {
  x++; 
  if(x>117){x=118;}
  delay(50);
}

 if (digitalRead(up) == 0)// khi nút RED được nhấn
  {
   y--;
   if(y<1){y=0;}
   delay(50);
  }
  
  if (digitalRead(down) == 0)
  {
  y++; 
  if(y>54){y=54;}
  delay(50);
}

 bool check = collide(x, y, 10, 10, 30, 30, 9, 9);

}
