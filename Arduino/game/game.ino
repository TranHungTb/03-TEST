#include <Wire.h>
#include <GOFi2cOLED.h>
#include <avr/pgmspace.h>

GOFi2cOLED GOFoled;
#include "bmp1.h"//
void setup() {
 //default address is 0x3D.
  GOFoled.init(0x3C);
  // init done
  
  GOFoled.display(); // show splashscreen
  delay(2000);
  GOFoled.clearDisplay();

  GOFoled.setTextSize(1);
  GOFoled.setTextColor(WHITE);
}
void loop() {
 
     for(int x=0; x<100; x+=9){
        walk(x,35,200);
    }
}

void walk(int x, int y,unsigned int time_d){
    //p1
    GOFoled.drawBitmap( x,y,25,28,walk1,WHITE); 
    GOFoled.display();
    delay(time_d);
    GOFoled.clearDisplay();
    //p2
    GOFoled.drawBitmap( x+3,y,25,28,walk2,WHITE); 
    GOFoled.display();
    delay(time_d);
    GOFoled.clearDisplay();
    //p3
    GOFoled.drawBitmap( x+6,y,25,28,walk3,WHITE);
    GOFoled.display();
    delay(time_d); 
    GOFoled.clearDisplay();
    //p4
    GOFoled.drawBitmap( x+9,y,25,28,walk4,WHITE); 
    GOFoled.display();
    delay(time_d);
    GOFoled.clearDisplay();
    GOFoled.display();
}
