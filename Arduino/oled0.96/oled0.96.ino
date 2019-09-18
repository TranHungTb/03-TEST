/*  OLED i2c Arduino example with unique logos
 * Schematic: https://www.electronoobs.com/eng_arduino_tut52_sch1.php
 * Tutorial: https://www.electronoobs.com/eng_arduino_tut52.php
 */



static const unsigned char PROGMEM  LOGO[] =
{ 
0XFC,0X00,0XFC,0X00,0XFC,0X00,0X1F,0X80,0X1F,0X80,0X1F,0X80,0XFC,0X00,0XFC,0X00,
0XFC,0X00
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


//#include <DS3231.h>
//DS3231  rtc(SDA, SCL);          //use the i2c pins


void setup() {
   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32 or 64 from eBay)
  delay(100);
  display.clearDisplay();
  display.display();
  delay(100);
}

void loop() {

  display.clearDisplay();
//  display.display();
//  
//  display.setTextSize(1);    
//  display.setCursor(0,0);
//  display.setTextColor(WHITE);
//  display.println("ELECTRONOOBS"); 
//  display.setTextSize(2);    
//  display.setCursor(33,8);
//  display.setTextColor(WHITE,BLACK);
//  display.println("13:22"); 
//  display.setTextSize(1);  
//  display.setTextColor(WHITE);
//  display.println("ABCDEFGHIJKLMNOPQRSTU"); 
//  
//  display.display();//Finally display the created image
//
//  delay(4000);
//
//  
//  display.clearDisplay();
//  display.display(); 
//  display.setTextSize(1);    
//  display.setCursor(45,0);
//  display.setTextColor(WHITE);
//  display.println("MY LOGO"); 
  display.drawBitmap(0,0, LOGO, 9, 9, 1);          
  /*here we print the logo on position 0 on x and 8 on y. The size of the logo is 128 on x
  and 31 on y. the LOGO bytes are defined above and are made with the Image2LCD program*/
  display.display();//Finally display the created image
  delay(3000);
  display.clearDisplay();

}
