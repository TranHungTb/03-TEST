/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : ledtt
Version : 
Date    : 10/7/2019
Author  : 
Company : 
Comments: 


Chip type               : ATtiny13A
AVR Core Clock frequency: 9.600000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 16
*******************************************************/

#include <tiny13a.h>
#include <delay.h>
// Declare your global variables here

//Tr?ng thái c?a LED, hay chính là byte mà ta s? g?i qua shiftOut
#DEFINE clockPin  PINB.0;         //sh 12
#DEFINE dataPin   PINB.1;               // ds 11
#DEFINE latchPin  PINB.2;         //st 8

char data;
char dataArray[8]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Function: Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit5=P Bit4=P Bit3=1 Bit2=0 Bit1=0 Bit0=0 
PORTB=(1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-5: Off
GIMSK=(0<<INT0) | (0<<PCIE);
MCUCR=(0<<ISC01) | (0<<ISC00);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB=(0<<ACME);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR0=(0<<AIN0D) | (0<<AIN1D);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);


while (1)
      {  
      
      //Sáng tu?n t?
//  ledStatus = 0;
//  //m?c d?nh là không có dèn nào sáng h?t (0 = 0b00000000)  
//  for (i = 0; i < 8; i++) {
//    ledStatus = (ledStatus << 1) | 1;
//    //Ð?y toàn b? các bit qua trái 1 bit và c?ng bit có giá tr? là 1 ? bit 0  
//    
//    /**
//      B?t bu?c ph?i có d? shiftOut
//    **/
//    
//    PORTB.2 = 0;
//    //các dèn LED s? không sáng khi b?n digital LOW
// 
//    //ShiftOut ra IC
//    shiftOut(PORTB.1, PORTB.0, MSBFIRST, ledStatus);  
//
//    PORTB.2 = 1;//các dèn LED s? sáng v?i tr?ng thái v?a du?c c?p nh?p
//   
//    /**
//      K?t thúc b?t bu?c ph?i có
//    **/
//    
//    delay_ms(500); // D?ng chuong trình kho?ng 500 mili giây d? th?y các hi?u ?ng c?a dèn LED
//  }
  

  //T?t tu?n t?
//  for (int i = 0;i<8;i++) {
//    ledStatus <<= 1; //Ð?y t?t c? các bit qua bên trái 1 bit
//    PORTB.2 = 0;
//    shiftOut(PORTB.1, PORTB.0, MSBFIRST, ledStatus);  
//    PORTB.2 = 1;
//    delay(500);
//  }


      // Place your code here
//      while (1)
//    {  
//      
//      if(PINB.4==0){  
//      i++;
//      if(i>=3){i=0;}
//      }   
//      
//
//      if(i==1){  
//       while(0<i1<9){
//      i++;
//      PORTB=a[7]; 
//      PORTB=a[2]; 
//      delay_ms(500);
//      } 
//       while(i1<17&&i1>8){
//      i++; 
//      PORTB=a[0];
//      PORTB=a[5]; 
//       
//      delay_ms(500); }
//      
//      
//      }
//       if(i==3){
//      PORTB=a[6];  
//      delay_ms(2);
//      PORTB=a[2];
//      }
//    
//      }
//.} 
}





//void shiftOut(char myDataPin, char myClockPin, char myDataOut) {
//  // This shifts 8 bits out MSB first,
//  //on the rising edge of the clock,
//  //clock idles low
//
//  //internal function setup
//  int i=0;
//  int pinState;
//  pinMode(myClockPin, OUTPUT);
//  pinMode(myDataPin, OUTPUT);
//
//  //clear everything out just in case to
//  //prepare shift register for bit shifting
//  digitalWrite(myDataPin, 0);
//  digitalWrite(myClockPin, 0);
//
//  //for each bit in the byte myDataOut?
//  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
//  //This means that %00000001 or "1" will go through such
//  //that it will be pin Q0 that lights.
//  for (i=7; i>=0; i--)  {
//    digitalWrite(myClockPin, 0);
//
//    //if the value passed to myDataOut and a bitmask result
//    // true then... so if we are at i=6 and our value is
//    // %11010100 it would the code compares it to %01000000
//    // and proceeds to set pinState to 1.
//    if ( myDataOut & (1<<i) ) {
//      pinState= 1;
//    }
//    else { 
//      pinState= 0;
//    }
//
//    //Sets the pin to HIGH or LOW depending on pinState
//    digitalWrite(myDataPin, pinState);
//    //register shifts bits on upstroke of clock pin  
//    digitalWrite(myClockPin, 1);
//    //zero the data pin after shift to prevent bleed through
//    digitalWrite(myDataPin, 0);
//  }
//
//  //stop shifting
//  digitalWrite(myClockPin, 0);
//}
//


