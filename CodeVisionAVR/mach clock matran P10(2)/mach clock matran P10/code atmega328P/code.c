#include <mega328p.h>
#asm
   .equ __i2c_port=0x08 ;PORTC
   .equ __sda_bit=4
   .equ __scl_bit=5
#endasm
#include <i2c.h>
#include <delay.h>
#define OE PORTD.0
#define _A PORTD.1
#define _B PORTD.6

#define up PINC.0
#define down PINC.1
#define ok PINC.2

#define clk PORTD.3
#define xuat PORTD.4
#define DS PORTD.5
#define IR_pin PIND.2

#define MelodyPin PORTB.1

#define pitch_P        0
#define pitch_C5    196
#define pitch_Db5    200
#define pitch_D5    203
#define pitch_Eb5    206
#define pitch_E5    209
#define pitch_F5    211
#define pitch_Gb5    214
#define pitch_G5    216
#define pitch_Ab5    218
#define pitch_A5    220
#define pitch_Bb5    222
#define pitch_B5    224

#define pitch_C6    226
#define pitch_Db6    228
#define pitch_D6    229
#define pitch_Eb6    231
#define pitch_E6    232
#define pitch_F6    234
#define pitch_Gb6    235
#define pitch_G6    236
#define pitch_Ab6    237
#define pitch_A6     238
#define pitch_Bb6     239
#define pitch_B6     240

#define SENSOR_DATA_IN     PINC.3
#define SENSOR_DATA_OUT    PORTC.3
#define SENSOR_DDR_DATA    DDRC.3

unsigned int dem,dem1,chonchu;
unsigned char dosang;    // bien eeprom luu tri gia tri sang
unsigned int sang;  // sang co gia tri tu 0 den 1000
unsigned char gio,phut,giay,thu=1,ngay,thang,nam=17,t1,t2,t3,t4,t5,t6,t7,giaycu;
unsigned char ngay_al,thang_al,trangthaiauto;
unsigned int nhietdo=30;
unsigned char giobt,phutbt,trangthaibaothuc;
unsigned char bugio,am;
unsigned char IRI,lenhIR,lenhIRcu,chedohoclenh;
unsigned long giatri;
unsigned char nut; 
unsigned char hieuungchuyengiay; 
unsigned char cobaothoat;
unsigned char ngaysinhnhat,thangsinhnhat,cobaosinhnhat,trangthaisinhnhat;
unsigned int qtrN,halfN, eighthN,wholeN,sixteenN,
              thirtyTwoN, sixtyFourN,
             sixN, twelveN,twentyFourN;    
unsigned char bodem;
unsigned char ma[16][8]=
{
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF}, 
};
flash unsigned char so[14][16]=
{
          {0xFF,0xFF,0x83,0x01,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x01,0x83,0xFF,0xFF},    //0
          {0xFF,0xFF,0xE7,0xE7,0x87,0x87,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0x81,0x81,0xFF,0xFF},    //1
          {0xFF,0xFF,0x83,0x01,0x39,0xF9,0xF9,0xF9,0xF3,0xE7,0xCF,0x9F,0x01,0x01,0xFF,0xFF},    //2   
          {0xFF,0xFF,0x83,0x01,0x39,0xF9,0xF9,0xC1,0xC1,0xF9,0xF9,0xF9,0x01,0x83,0xFF,0xFF},    //3  
          {0xFF,0xFF,0x39,0x39,0x39,0x39,0x39,0x01,0x81,0xF9,0xF9,0xF9,0xF9,0xf9,0xFF,0xFF},    //4  
          {0xFF,0xFF,0x01,0x01,0x3F,0x3F,0x3F,0x03,0x01,0xF9,0xF9,0x79,0x01,0x83,0xFF,0xFF},    //5  
          {0xFF,0xFF,0x83,0x01,0x39,0x3F,0x3F,0x03,0x01,0x39,0x39,0x39,0x01,0x83,0xFF,0xFF},    //6  
          {0xFF,0xFF,0x83,0x01,0x39,0x39,0x39,0xF9,0xF9,0xF9,0xF9,0xF9,0xF9,0xF9,0xFF,0xFF},    //7  
          {0xFF,0xFF,0x83,0x01,0x39,0x39,0x39,0x83,0x01,0x39,0x39,0x39,0x01,0x83,0xFF,0xFF},    //8   
          {0xFF,0xFF,0x83,0x01,0x39,0x39,0x39,0x01,0x81,0xF9,0xF9,0xF9,0x01,0x83,0xFF,0xFF},    //9      
          {0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xff,0xFF,0xFF},     // hai cham 
          {0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff,0xFF,0xFF,0xFF},     //k hien gi  
          {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, // - 12
          {0xFF,0xFF,0xFF,0xFF,0xFF,0xe7,0xE7,0xC81,0x81,0xE7,0xe7,0xFF,0xFF,0xFF,0xFF,0xFF}, // + 13
                                                                                                                                                           
};  
                                                                                                                                                                    
flash unsigned char font[16][43]=
{                                                                   //0FFH,1FH,1FH,0FFH,0FFH,0FFH,0FFH,0FFH                                                             0BDH,7DH,0FDH,0FBH,0F7H,7H,0F7H,0F0H   
  {0xFF,0xFF,0xff,0xff,0xff,0xFC,0xFF,0xFF,0xFF,0xFF,0xff,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},                                                            
  {0xFF,0xFF,0xff,0xff,0xFF,0xFe,0x7F,0xFF,0xFF,0xFF,0xff,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x77,0xEE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},       
  {0xFF,0xFF,0xff,0xff,0xff,0xc7,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3c,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFe,0x07,0xFF,0x77,0xee,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xFF,0xFF,0xff,0xff,0xff,0x83,0xff,0xff,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xfF,0xFF,0xFe,0x07,0xFF,0x8F,0xf1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
                                                                                
  {0xC0,0x00,0x00,0x7F,0xFC,0x00,0xff,0xff,0xFF,0xFF,0xFC,0x00,0x00,0xFF,0xFC,0x00,0x0e,0x00,0x03,0xF0,0x03,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0xFF,0xfF,0xFF,0xFe,0x07,0xFF,0xe0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xC0,0x00,0x00,0x1F,0xF8,0x70,0x7f,0xff,0xFF,0xFF,0xc0,0x00,0x00,0xFF,0xFC,0x00,0x0e,0x00,0x03,0xE1,0xc1,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0xFF,0xff,0xFF,0xFe,0x07,0xFF,0xdF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xFC,0x0F,0xe0,0x0f,0xfF,0xFF,0xff,0xff,0xFF,0xFF,0x00,0x3F,0x01,0xFF,0xFF,0xC0,0x3f,0xC0,0x3F,0xFF,0xFF,0xFF,0xFF,0x80,0x3f,0xFF,0xFF,0xFF,0xff,0xFF,0xFe,0x07,0xFF,0xbF,0xFb,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xFC,0x0F,0xf0,0x07,0xF8,0x01,0xFc,0x01,0x80,0x7F,0x00,0xff,0x80,0xFF,0xFF,0xC0,0x7f,0xc0,0x7F,0xE0,0x07,0xFF,0xFF,0x80,0x7F,0xFF,0xFF,0x80,0x3f,0xF8,0x0e,0x07,0xFF,0xbF,0xdd,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  
  {0xFC,0x0F,0xF8,0x03,0xC0,0x00,0x3F,0x00,0x00,0x1F,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x7f,0x80,0x7F,0x00,0x00,0xFF,0xFF,0x80,0x7F,0xFF,0xFC,0x00,0x07,0xe0,0x00,0x07,0xFF,0xBF,0xbd,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},          
  {0xE0,0x03,0xF0,0x03,0x80,0x70,0x1F,0x00,0xF0,0x1c,0x01,0xE0,0x00,0x1F,0xFF,0x80,0x00,0x00,0x7E,0x03,0xC0,0x7F,0xFF,0x80,0x7F,0xFF,0xF0,0x1e,0x03,0xc0,0x38,0x07,0xFF,0xA0,0x7d,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xE0,0x03,0xF8,0x03,0x01,0xF8,0x0F,0x01,0xF0,0x1C,0x01,0xC0,0x00,0x1F,0xFF,0x80,0x00,0x00,0x7C,0x07,0xF0,0x3F,0xFF,0x80,0x7F,0xFF,0xE0,0x3e,0x01,0x80,0x7c,0x07,0xFF,0xBF,0xFd,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xFC,0x0F,0xF0,0x07,0x01,0xF8,0x0F,0x01,0xF0,0x1c,0x01,0xFC,0x03,0xFF,0xFF,0x80,0x7f,0x80,0x7C,0x07,0xF0,0x3F,0xFF,0x80,0x7F,0xC0,0x60,0x00,0x01,0x80,0x7c,0x07,0xFF,0xDF,0xFb,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  
  {0xFC,0x0F,0xF0,0x07,0x01,0xF8,0x1F,0x01,0xF0,0x3E,0x00,0xF8,0x03,0xFF,0xFF,0x80,0x7f,0x80,0x7C,0x07,0xF0,0x7F,0xFF,0x80,0x7F,0xC0,0xE0,0x7F,0xFF,0x80,0x7c,0x07,0xFF,0xEF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0xFC,0x0F,0xC0,0x1F,0x00,0xE0,0x1F,0x03,0xF0,0x3E,0x00,0x78,0x03,0xFF,0xFF,0x80,0x0f,0x80,0xFC,0x03,0x80,0x7F,0xFF,0x80,0xFF,0xC0,0xE0,0x3f,0x83,0x80,0x78,0x0F,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0x00,0x00,0x00,0x7F,0x80,0x00,0x70,0x00,0x80,0x07,0x80,0x00,0x03,0xFF,0xF0,0x00,0x0f,0x00,0x0E,0x00,0x01,0xFF,0xF0,0x00,0x00,0x00,0xF0,0x00,0x07,0xC0,0x00,0x01,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 
  {0x00,0x00,0x01,0xFF,0xF0,0x03,0xF0,0x00,0x80,0x07,0xF8,0x03,0x03,0xFF,0xF0,0x00,0x0f,0x00,0x0F,0xC0,0x0F,0xFF,0xF0,0x00,0x00,0x00,0xFE,0x00,0x3f,0xF8,0x08,0x01,0xFF,0x0F,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}     
 
}; 

flash unsigned char chu[50][16]=
{   
     {0xFF,0xFF,0xFF,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //a  0
     {0xFF,0xFF,0xFF,0xFF,0xC1,0xCC,0x9C,0x9C,0x81,0x9C,0x9C,0x3C,0x01,0xFF,0xFF,0xFF},   //b  1
     {0xFF,0xFF,0xFF,0xFF,0xC3,0x99,0x99,0x3F,0x3F,0x3F,0x39,0x39,0x83,0xFF,0xFF,0xFF},   //c  2
     {0xFF,0xFF,0xFF,0xFF,0xC1,0x8C,0x9C,0x9C,0x9C,0x9C,0x99,0x39,0x03,0xFF,0xFF,0xFF},   //d  3
     {0xFF,0xFF,0xFF,0xFF,0xC1,0xCF,0x9F,0x9F,0x83,0x9F,0x9F,0x3F,0x03,0xFF,0xFF,0xFF},   //e  4
     {0xFF,0xFF,0xFF,0xFF,0xC1,0xCF,0x9F,0x9F,0x83,0x9F,0x9F,0x3F,0x3F,0xFF,0xFF,0xFF},   //f  5
     {0xFF,0xFF,0xFF,0xFF,0xC3,0x99,0x99,0x3F,0x21,0x39,0x39,0x31,0x83,0xFF,0xFF,0xFF},   //g  6
     {0xFF,0xFF,0xFF,0xFF,0xCC,0xCC,0x99,0x99,0x81,0x99,0x99,0x33,0x33,0xFF,0xFF,0xFF},   //h  7
     {0xFF,0xFF,0xFF,0xFf,0xF3,0xFF,0xE7,0xE7,0xE7,0xE7,0xE7,0xCF,0xCF,0xFF,0xFF,0xFF},   //i  8
     {0xFF,0xFF,0xFF,0xFF,0xF9,0xF9,0xF3,0xF3,0xF3,0xF3,0xF3,0x27,0x8F,0xFF,0xFF,0xFF},   //j  9
     {0xFF,0xFF,0xFF,0xFF,0xCC,0xC9,0x93,0x87,0x87,0x93,0x93,0x39,0x39,0xFF,0xFF,0xFF},   //k  10 
     {0xFF,0xFF,0xFF,0xFF,0xCF,0xCF,0x9F,0x9F,0x9F,0x9F,0x9F,0x3F,0x03,0xFF,0xFF,0xFF},   //l  11
     {0xFF,0xFF,0xFF,0xFF,0xBE,0x9C,0x82,0xA2,0xB6,0xBE,0xBE,0x3C,0x3C,0xFF,0xFF,0xFF},   //m  12
     {0xFF,0xFF,0xFF,0xFF,0xDC,0xDC,0x89,0x89,0xA9,0xA1,0xA1,0x33,0x33,0xFF,0xFF,0xFF},   //n  13
     {0xFF,0xFF,0xFF,0xFF,0xC3,0x99,0x99,0xB9,0x39,0x39,0x3B,0x33,0x87,0xFF,0xFF,0xFF},   //o  14
     {0xFF,0xFF,0xFF,0xFF,0xC1,0xCC,0x9C,0x9C,0x9C,0x81,0x9F,0x3F,0x3F,0xFF,0xFF,0xFF},   //p  15
     {0xFF,0xFF,0xFF,0xFF,0xC3,0x99,0x99,0x39,0x39,0x39,0x2B,0x33,0x87,0xFF,0xFF,0xFF},   //q  16
     {0xFF,0xFF,0xFF,0xFF,0xC1,0xCC,0x9C,0x9C,0x83,0x93,0x93,0x39,0x39,0xFF,0xFF,0xFF},   //r  17
     {0xFF,0xFF,0xFF,0xFF,0xE3,0xC9,0xC9,0xCF,0xE7,0xF3,0x93,0x93,0xC7,0xFF,0xFF,0xFF},   //s  18
     {0xFF,0xFF,0xFF,0xFF,0x01,0xE7,0xCF,0xCF,0xCF,0xCF,0xCF,0x9F,0x9F,0xFF,0xFF,0xFF},   //t  19
     {0xFF,0xFF,0xFF,0xFF,0x9C,0x9C,0x39,0x39,0x39,0x39,0x39,0x33,0x87,0xFF,0xFF,0xFF},   //u  20
     {0xFF,0xFF,0xFF,0xFF,0x39,0x33,0x33,0x37,0x27,0x2F,0x0F,0x1F,0x1F,0xFF,0xFF,0xFF},   //v  21
     {0xFF,0xFF,0xFF,0xFF,0x6E,0x6C,0x4D,0x49,0x4B,0x23,0x27,0x27,0x6F,0xFF,0xFF,0xFF},   //w  22
     {0xFF,0xFF,0xFF,0xFF,0x3D,0x1B,0x93,0x93,0xC7,0xCF,0xCF,0x9F,0x9F,0xFF,0xFF,0xFF},   //x  23
     {0xFF,0xFF,0xFF,0xFF,0x3D,0x1B,0x93,0x93,0xC7,0xCF,0xCF,0x9F,0x9F,0xFF,0xFF,0xFF},   //y  24
     {0xFF,0xFF,0xFF,0xFF,0x81,0xF3,0xF3,0xE7,0xC7,0xCF,0x9F,0x9F,0x01,0xFF,0xFF,0xFF},   //z  25     
     {0xFc,0xF9,0xf3,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //a   26 
     {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF,0xFF},   //.   27  
     {0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xff,0xFF,0xFF},     // hai cham 28    
     {0xFF,0xff,0xFF,0xFF,0xFF,0xff,0xFF,0xFF,0xFF,0xff,0xFF,0xFF,0xFF,0xff,0xFF,0xFF},     // k hien gi 29 
     {0x07,0x07,0x07,0x67,0x67,0x67,0x61,0x66,0x66,0x61,0x67,0x67,0x67,0x07,0x07,0x07},   //30 nut keo  
     {0x07,0x07,0x07,0x07,0x07,0x07,0x01,0x06,0x06,0x01,0x07,0x07,0x07,0x07,0x07,0x07},   //31 nut keo 2  
     {0x9F,0xCF,0xE5,0xFC,0xC0,0x98,0x99,0xB9,0x39,0x39,0x39,0x33,0x87,0xFF,0xFF,0xFF},    //32 owf   
     {0xF9,0xf3,0xe7,0xFF,0x9C,0x9C,0x39,0x39,0x39,0x39,0x39,0x33,0x87,0xFF,0xFF,0xFF},   //us  33  
     {0xF3,0xE1,0xCC,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //aa  34    
     {0xe7,0xf3,0xf9,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //af  35
     {0xfc,0xf9,0xf3,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //as  36 
     {0xcc,0xe0,0xf1,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //aw  37
     {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, // - 38 
     {0xF3,0xC9,0x9C,0xFF,0xC3,0x99,0x99,0xB9,0x39,0x39,0x3B,0x33,0x87,0xFF,0xFF,0xFF},   //oo  39  
     {0xF3,0xE1,0xCC,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xe7,0xe7},   //aaj  40 
     {0xFF,0xE7,0xDB,0xDB,0xE7,0xff,0xFF,0xFF,0xFF,0xff,0xFF,0xFF,0xFF,0xff,0xFF,0xFF},   // ki hieu do 41  
     {0xFF,0xFF,0xff,0xFF,0xFF,0xFF,0xC3,0xFF,0xC3,0xff,0xFF,0xFF,0xFF,0xff,0xFF,0xFF},  // = 42   
     {0x9F,0xCF,0xE7,0xFE,0xC2,0x98,0x99,0xB9,0x39,0x39,0x3B,0x33,0x87,0xFF,0xFF,0xFF},  // owf 43 
     {0xF3,0xC9,0x9C,0xFF,0xC3,0x99,0x99,0xB9,0x39,0x39,0x3B,0x33,0x87,0xff,0xcf,0xcf},   //oj  44 
     {0xFF,0xFF,0xFF,0xFF,0xC1,0x8C,0x9C,0x0C,0x0C,0x9C,0x99,0x39,0x03,0xFF,0xFF,0xFF},   //dd  45 
     {0x9f,0xcf,0xe7,0xFF,0x9C,0x9C,0x39,0x39,0x39,0x39,0x39,0x33,0x87,0xFF,0xFF,0xFF},   //uf  46   
     {0xF3,0xE1,0xCC,0xFF,0xC1,0xCF,0x9F,0x9F,0x83,0x9F,0x9F,0x3F,0x03,0xFF,0xcf,0xcf},   //eej  47
     {0xF3,0xFd,0xFb,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xFF,0xFF},   //ar  48  
     {0xff,0xff,0xff,0xFF,0xE1,0xE1,0xC9,0xC9,0xC9,0x99,0x81,0x99,0x39,0xFF,0xe7,0xe7},   //aaj  49 
}; 
                                           
flash unsigned char thanhtruotIphone[16][16][4]=
{
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x09,0xFE,0x00,0x10,0x12,0x01,0x00,0x08,
0x24,0x00,0x80,0x04,0x28,0x00,0x40,0x04,0x28,0x00,0x40,0x04,0x28,0x00,0x40,0x04,
0x28,0x00,0x40,0x04,0x28,0x00,0x40,0x04,0x28,0x00,0x40,0x04,0x24,0x00,0x80,0x04,
0x12,0x01,0x00,0x08,0x09,0xFE,0x00,0x10,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0C,0x03,0xFF,0xF0,0x18,0x01,0xFF,0xF8,
0x30,0x00,0xFF,0xFC,0x30,0x00,0xFF,0xFC,0x30,0x00,0xFF,0xFC,0x30,0x00,0xFF,0xFC,
0x30,0x00,0xFF,0xFC,0x30,0x00,0xFF,0xFC,0x30,0x00,0xFF,0xFC,0x30,0x00,0xFF,0xFC,
0x18,0x01,0xFF,0xF8,0x0C,0x03,0xFF,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0E,0x01,0xFF,0xF0,0x1C,0x00,0xFF,0xF8,
0x38,0x00,0x7F,0xFC,0x38,0x00,0x7F,0xFC,0x38,0x00,0x7F,0xFC,0x38,0x00,0x7F,0xFC,
0x38,0x00,0x7F,0xFC,0x38,0x00,0x7F,0xFC,0x38,0x00,0x7F,0xFC,0x38,0x00,0x7F,0xFC,
0x1C,0x00,0xFF,0xF8,0x0E,0x01,0xFF,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0x00,0xFF,0xF0,0x1E,0x00,0x7F,0xF8,
0x3C,0x00,0x3F,0xFC,0x3C,0x00,0x3F,0xFC,0x3C,0x00,0x3F,0xFC,0x3C,0x00,0x3F,0xFC,
0x3C,0x00,0x3F,0xFC,0x3C,0x00,0x3F,0xFC,0x3C,0x00,0x3F,0xFC,0x3C,0x00,0x3F,0xFC,
0x1E,0x00,0x7F,0xF8,0x0F,0x00,0xFF,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xC0,0x3F,0xF0,0x1F,0x80,0x1F,0xF8,
0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,
0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,
0x1F,0x80,0x1F,0xF8,0x0F,0xC0,0x3F,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xC0,0x3F,0xF0,0x1F,0x80,0x1F,0xF8,
0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,
0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,0x3F,0x00,0x0F,0xFC,
0x1F,0x80,0x1F,0xF8,0x0F,0xC0,0x3F,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xE0,0x1F,0xF0,0x1F,0xC0,0x0F,0xF8,
0x3F,0x80,0x07,0xFC,0x3F,0x80,0x07,0xFC,0x3F,0x80,0x07,0xFC,0x3F,0x80,0x07,0xFC,
0x3F,0x80,0x07,0xFC,0x3F,0x80,0x07,0xFC,0x3F,0x80,0x07,0xFC,0x3F,0x80,0x07,0xFC,
0x1F,0xC0,0x0F,0xF8,0x0F,0xE0,0x1F,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xF0,0x0F,0xF0,0x1F,0xE0,0x07,0xF8,
0x3F,0xC0,0x03,0xFC,0x3F,0xC0,0x03,0xFC,0x3F,0xC0,0x03,0xFC,0x3F,0xC0,0x03,0xFC,
0x3F,0xC0,0x03,0xFC,0x3F,0xC0,0x03,0xFC,0x3F,0xC0,0x03,0xFC,0x3F,0xC0,0x03,0xFC,
0x1F,0xE0,0x07,0xF8,0x0F,0xF0,0x0F,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xF8,0x07,0xF0,0x1F,0xF0,0x03,0xF8,
0x3F,0xE0,0x01,0xFC,0x3F,0xE0,0x01,0xFC,0x3F,0xE0,0x01,0xFC,0x3F,0xE0,0x01,0xFC,
0x3F,0xE0,0x01,0xFC,0x3F,0xE0,0x01,0xFC,0x3F,0xE0,0x01,0xFC,0x3F,0xE0,0x01,0xFC,
0x1F,0xF0,0x03,0xF8,0x0F,0xF8,0x07,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFC,0x03,0xF0,0x1F,0xF8,0x01,0xF8,
0x3F,0xF0,0x00,0xFC,0x3F,0xF0,0x00,0xFC,0x3F,0xF0,0x00,0xFC,0x3F,0xF0,0x00,0xFC,
0x3F,0xF0,0x00,0xFC,0x3F,0xF0,0x00,0xFC,0x3F,0xF0,0x00,0xFC,0x3F,0xF0,0x00,0xFC,
0x1F,0xF8,0x01,0xF8,0x0F,0xFC,0x03,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFE,0x01,0xF0,0x1F,0xFC,0x00,0xF8,
0x3F,0xF8,0x00,0x7C,0x3F,0xF8,0x00,0x7C,0x3F,0xF8,0x00,0x7C,0x3F,0xF8,0x00,0x7C,
0x3F,0xF8,0x00,0x7C,0x3F,0xF8,0x00,0x7C,0x3F,0xF8,0x00,0x7C,0x3F,0xF8,0x00,0x7C,
0x1F,0xFC,0x00,0xF8,0x0F,0xFE,0x01,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFF,0x00,0xF0,0x1F,0xFE,0x00,0x78,
0x3F,0xFC,0x00,0x3C,0x3F,0xFC,0x00,0x3C,0x3F,0xFC,0x00,0x3C,0x3F,0xFC,0x00,0x3C,
0x3F,0xFC,0x00,0x3C,0x3F,0xFC,0x00,0x3C,0x3F,0xFC,0x00,0x3C,0x3F,0xFC,0x00,0x3C,
0x1F,0xFE,0x00,0x78,0x0F,0xFF,0x00,0xF0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFF,0x80,0x70,0x1F,0xFF,0x00,0x38,
0x3F,0xFE,0x00,0x1C,0x3F,0xFE,0x00,0x1C,0x3F,0xFE,0x00,0x1C,0x3F,0xFE,0x00,0x1C,
0x3F,0xFE,0x00,0x1C,0x3F,0xFE,0x00,0x1C,0x3F,0xFE,0x00,0x1C,0x3F,0xFE,0x00,0x1C,
0x1F,0xFF,0x00,0x38,0x0F,0xFF,0x80,0x70,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFF,0xC0,0x30,0x1F,0xFF,0x80,0x18,
0x3F,0xFF,0x00,0x0C,0x3F,0xFF,0x00,0x0C,0x3F,0xFF,0x00,0x0C,0x3F,0xFF,0x00,0x0C,
0x3F,0xFF,0x00,0x0C,0x3F,0xFF,0x00,0x0C,0x3F,0xFF,0x00,0x0C,0x3F,0xFF,0x00,0x0C,
0x1F,0xFF,0x80,0x18,0x0F,0xFF,0xC0,0x30,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFF,0xE0,0x10,0x1F,0xFF,0xC0,0x08,
0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,
0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,
0x1F,0xFF,0xC0,0x08,0x0F,0xFF,0xE0,0x10,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x0F,0xFF,0xE0,0x10,0x1F,0xFF,0xC0,0x08,
0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,
0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,0x3F,0xFF,0x80,0x04,
0x1F,0xFF,0xC0,0x08,0x0F,0xFF,0xE0,0x10,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
};
flash unsigned char lich[]={
0x1b,0x0c
,0x11,0x12,0x03,0x04,0x15,0x06,0x07,0x18,0x09,0x1a,0x1b,0x0c                     //14
,0x11,0x12,0x03,0x14,0x04,0x15,0x06,0x07,0x18,0x09,0x1a,0x0b,0x1c                //27
,0x11,0x12,0x03,0x14,0x05,0x16,0x07,0x08,0x19,0x0a,0x1b,0x0c                     //39
,0x11,0x12,0x03,0x14,0x15,0x06,0x17,0x08,0x09,0x1a,0x0b,0x1c                     //51
,0x01,0x12,0x02,0x13,0x14,0x05,0x16,0x07,0x18,0x09,0x1a,0x0b,0x1c                //64
,0x01,0x12,0x03,0x14,0x05,0x16,0x17,0x08,0x19,0x0a,0x1b,0x0c//2005               //76
,0x11,0x02,0x13,0x04,0x05,0x16,0x17,0x07,0x18,0x19,0x0a,0x1b,0x0c //2006         //89
,0x11,0x02,0x13,0x04,0x05,0x16,0x07,0x18,0x19,0x1a,0x0b,0x1c                     //101
,0x11,0x02,0x03,0x14,0x05,0x06,0x17,0x08,0x19,0x0a,0x1b,0x1c                     //113
,0x11,0x12,0x03,0x04,0x15,0x05,0x06,0x17,0x08,0x19,0x0a,0x1b,0x1c
,0x11,0x02,0x13,0x04,0x15,0x06,0x07,0x18,0x09,0x1A,0x0B,0x1C///2010              //138
,0x11,0x02,0x13,0x14,0x05,0x16,0x07,0x08,0x19,0x0A,0x1B,0x0C                     //150
,0x11,0x02,0x13,0x14,0x04,0x15,0x06,0x17,0x08,0x19,0x0a,0x1b,0x0c                //163
,0x11,0x02,0x13,0x04,0x15,0x16,0x07,0x18,0x09,0x1a,0x0b,0x1c                     //175
,0x01,0x12,0x03,0x14,0x05,0x16,0x07,0x18,0x19,0x09,0x1a,0x0b,0x1c                //188
,0x01,0x12,0x03,0x04,0x15,0x06,0x17,0x18,0x19,0x0a,0x1b,0x0c                     //200
,0x11,0x02,0x13,0x04,0x05,0x16,0x07,0x18,0x19,0x0a,0x1b,0x1c                     //212
,0x01,0x12,0x03,0x14,0x05,0x06,0x16,0x07,0x18,0x09,0x1a,0x1b,0x1c//2017          //225
,0x01,0x12,0x03,0x14,0x05,0x06,0x17,0x08,0x19,0x0a,0x1b,0x1c                     //237
,0x11,0x02,0x13,0x04,0x15,0x06,0x07,0x18,0x09,0x0a,0x1b,0x1c
,0x01,0x12,0x13,0x14,0x04,0x15,0x06,0x07,0x18,0x09,0x1a,0x0b,0x1c                //262
};
flash unsigned int count_year1[]={ 0,59,413,797,1151,1506,1890,2244,2628,2983,3337,3721,4075,4429,4813,5168,5552,5906,6261,6645,6999,7353,7737,8091,8446,8830,9184,9568,9922,10276,10660,11015,11369,11753,12108,12492,12846,13200,13584,13938,14292,14676,15031,15386,15770,16124,16508,16862,17216,17600,17954,18309,18693,19048,19431,19786,20140,20523,20878,21232,21616,21971,22325,22709,23063,23447,23801,24156,24540,24894,25249,25633,25987,26371,26725,27079,27463,27818,28172,28556,28911,29265,29649,30003,30387,30741,31096,31480,31834,32189,32572,32926,33310,33664,34019,34403,34758,35112,35496,35850,36204,36588};
flash unsigned int count_year[]={ 25 ,391 ,756 ,1121 ,1486 ,1852 ,2217 ,2582 ,2947 ,3313 ,3678 ,4043 ,4408 ,4774 ,5139 ,5504 ,5869 ,6235 ,6600 ,6965 ,7330 ,7696 ,8061 ,8426 ,8791 ,9157 ,9522 ,9887 ,10252 ,10618 ,10983 ,11348 ,11713 ,12079 ,12444 ,12809 ,13174 ,13540 ,13905 ,14270 ,14635 ,15001 ,15366 ,15731 ,16096 ,16462 ,16827 ,17192 ,17557 ,17923 ,18288 ,18653 ,19018 ,19384 ,19749 ,20114 ,20479 ,20845 ,21210 ,21575 ,21940 ,22306 ,22671 ,23036 ,23401 ,23767 ,24132 ,24497 ,24862 ,25228 ,25593 ,25958 ,26323 ,26689 ,27054 ,27419 ,27784 ,28150 ,28515 ,28880 ,29245 ,29611 ,29976 ,30341 ,30706 ,31072 ,31437 ,31802 ,32167 ,32533 ,32898 ,33263 ,33628 ,33994 ,34359 ,34724 ,35089 ,35455 ,35820 ,36185 ,36550 };
flash unsigned int sothang[]={ 0,2,14,27,39,51,64,76,89,101,113,126,138,150,163,175,188,200,212,225,237,249,262,274,286,299,311,324,336,348,361,373,385,398,410,423,435,447,460,472,484,497,509,521,534,546,559,571,583,596,608,620,633,645,658,670,682,695,707,719,732,744,756,769,781,794,806,818,831,843,855,868,880,893,905,917,930,942,954,967,979,991,1004,1016,1029,1041,1053,1066,1078,1090,1103,1115,1128,1140,1152,1165,1177,1189,1202,1214,1226,1239};
flash unsigned int count_month[] ={ 0,0,31,59,90,120,151,181,212,243,273,304,334};
flash unsigned int count_month1[]={ 0,0,31,60,91,121,152,182,213,244,274,305,335};

void hienthi();
void laythoigiantrongds1();
void laydosang();
void Delay10MC(unsigned char a)
{
  a=a*10;       // toc do phat  
  while(a--);
}    
interrupt [TIM0_OVF] void Ngat_Timer_0()
{
    MelodyPin = ~MelodyPin;
    TCNT0=bodem;
}
void MelodyTempo(int Tempo)
{
    qtrN = ((60000/Tempo));
    wholeN = qtrN*4;
    halfN = (qtrN*2);
    eighthN = (qtrN/2);
    sixteenN = (qtrN/4);
    thirtyTwoN = (qtrN/8);
    sixtyFourN = (qtrN/16);
    sixN = (wholeN/6);
    twelveN = (wholeN/12);
    twentyFourN = (wholeN/24);
}
void PlayNote(const unsigned char PitchL)
{
    bodem = PitchL; 
    TCNT0 = PitchL; 
    TCCR0B=0x04; //255
}

void EndNote(void){

    TCCR0B=0x00; // ngung dem
    MelodyPin = 1;
}

void delayms(unsigned int ms)
{
    for(;ms>0;ms--)
        Delay10MC(100);
}

void Melodyplay(const int Pitch, unsigned int interval)     // not nhac, dan cach
{
    if(Pitch!=0)
        PlayNote(Pitch);
    delayms(interval);
    EndNote();
}

void chucmungbuoisang()
{
     MelodyTempo(13);
     Melodyplay(pitch_Db5, qtrN);       
     Melodyplay(pitch_Eb5, qtrN);
     Melodyplay(pitch_F5, qtrN);
     Melodyplay(pitch_Db5, qtrN);

     Melodyplay(pitch_Db5, qtrN);       
     Melodyplay(pitch_Eb5, qtrN);
     Melodyplay(pitch_F5, qtrN);
     Melodyplay(pitch_Db5, halfN);

     Melodyplay(pitch_F5, qtrN);
     Melodyplay(pitch_Gb5, qtrN); 
     Melodyplay(pitch_Ab5, halfN);   

     Melodyplay(pitch_F5, qtrN);
     Melodyplay(pitch_Gb5, qtrN); 
     Melodyplay(pitch_Ab5, halfN); 
     
     Melodyplay(pitch_Ab5, qtrN);  
     Melodyplay(pitch_Bb5, qtrN); 
     Melodyplay(pitch_Ab5, qtrN); 
     Melodyplay(pitch_Gb5, qtrN); 
     Melodyplay(pitch_F5, qtrN);
     Melodyplay(pitch_Db5, halfN);  
     
     Melodyplay(pitch_Ab5, qtrN);  
     Melodyplay(pitch_Bb5, qtrN); 
     Melodyplay(pitch_Ab5, qtrN); 
     Melodyplay(pitch_Gb5, qtrN); 
     Melodyplay(pitch_F5, qtrN);
     Melodyplay(pitch_Db5, halfN);  

     Melodyplay(pitch_C6, qtrN); 
     Melodyplay(pitch_G5, qtrN);
     Melodyplay(pitch_C6, halfN);  

     Melodyplay(pitch_C6, qtrN); 
     Melodyplay(pitch_G5, qtrN);
     Melodyplay(pitch_C6, halfN);  
}

void chucmungsinhnhat()
{
       MelodyTempo(15);
   Melodyplay(pitch_Db5, qtrN);       
   Melodyplay(pitch_Db5, qtrN);
   Melodyplay(pitch_Eb5, qtrN);
   Melodyplay(pitch_Db5, qtrN);
   Melodyplay(pitch_Gb5, qtrN);
   Melodyplay(pitch_F5,  halfN);

   Melodyplay(pitch_Db5, qtrN);       
   Melodyplay(pitch_Db5, qtrN);
   Melodyplay(pitch_Eb5, qtrN);
   Melodyplay(pitch_Db5, qtrN);
   Melodyplay(pitch_Ab5, qtrN);
   Melodyplay(pitch_F5, halfN);

   Melodyplay(pitch_Db5, qtrN);       
   Melodyplay(pitch_Db5, qtrN);
   Melodyplay(pitch_Db6, qtrN);
   Melodyplay(pitch_Bb5, qtrN);
   Melodyplay(pitch_F5,  qtrN); 
   Melodyplay(pitch_F5, qtrN);       
   Melodyplay(pitch_Eb5, halfN);  
   
   Melodyplay(pitch_Bb5, eighthN );
   Melodyplay(pitch_Bb5, eighthN );
   Melodyplay(pitch_Bb5, eighthN); 
   Melodyplay(pitch_F5, qtrN);    
   Melodyplay(pitch_Gb5, qtrN);  
   Melodyplay(pitch_F5, qtrN);   
}    


//-------------------------Ket thuc phan Phat nhac---------------//

//----------------------------Chuong trinh doc nhiet do | Copy cua Led Dac Dam cho nhanh :P  ---------//
unsigned char reset_ds18b20(){
    unsigned char result=1;
    SENSOR_DATA_OUT=1;
    SENSOR_DATA_OUT=0;
    delay_us(480);
    SENSOR_DATA_OUT=1;
    SENSOR_DDR_DATA=0;
    delay_us(70);
    result=SENSOR_DATA_IN;
    delay_us(400);
    SENSOR_DDR_DATA=1;
    return result;
}

void write_bit_ds18b20(unsigned char b){
    SENSOR_DATA_OUT=0;
    delay_us(6);
    SENSOR_DATA_OUT=b;
    delay_us(54);
    SENSOR_DATA_OUT=1;
    delay_us(10);
}

unsigned char read_bit_ds18b20(){
    unsigned char result;
    SENSOR_DATA_OUT=0;
    delay_us(6);
    SENSOR_DATA_OUT=1;
    SENSOR_DDR_DATA=0;
    delay_us(9);
    result=SENSOR_DATA_IN;
    delay_us(55);
    SENSOR_DDR_DATA=1;
    return result;
}

void write_byte_ds18b20(unsigned char byte){
    unsigned char i;
    for(i=0;i<8;i++){
        write_bit_ds18b20(byte & 0x01);
        byte>>=1;
    }
}

unsigned char read_byte_ds18b20(){
    unsigned char i, result=0;
    for(i=0;i<8;i++){
        result>>=1;
        result|=(read_bit_ds18b20()<<7);
    }
    return result;
}

void int_ds18b20(){
    while(reset_ds18b20());
    write_byte_ds18b20(0xCC);
    write_byte_ds18b20(0x44);
}

void laynhietdo(){
    unsigned char a=0;
    unsigned char b=0;
    SENSOR_DDR_DATA=1;
    while(reset_ds18b20());
    write_byte_ds18b20(0xCC);
    write_byte_ds18b20(0xBE);
    a=read_byte_ds18b20();
    b=read_byte_ds18b20();
    nhietdo=((b*256+a)>>4);   
    int_ds18b20();
}


//----------------------------------END-----------------------------------------------

void delay(unsigned int t)        //delay_us
{
  for(;t>0;t--)
  {
   ;
  }
}                 
// ham ghi du lieu vao ds1307
void ghids(unsigned char add, unsigned char dat)
{
    i2c_start(); // bat dau ghi    
    i2c_write(0xd0); //0xd0 la dia chi cua ds1307
    i2c_write(add);    // gia tri can ghi
    i2c_write(((dat/10)<<4)|(dat%10));      // do du lieu trong ds la BCD nen ta can chuyen ca gia tri sang BCD ( day cau lenh chuyen du lieu sang BCD)
    i2c_stop();     // ket thuc qua trinh truyen du lieu
}
void ghidulieu(unsigned char add, unsigned char dat)
{
    i2c_start(); // bat dau ghi    
    i2c_write(0xd0); //0xd0 la dia chi cua ds1307
    i2c_write(add);    // gia tri can ghi
    i2c_write(dat);     
    i2c_stop();     // ket thuc qua trinh truyen du lieu
}
// Ham doc du lieu thoi gian trong ds
unsigned char docds(unsigned char add)
{
    unsigned char dat;
    
    i2c_start();   // bat dau doc
    
    i2c_write(0xd0);     // dau tien gui lenh ghi du lieu(ghi dia chi can lay du lieu trong DS1307)
    i2c_write(add); // Dia chi ma ta muon doc ( vi du, muon doc giay thi ta ghi dia chi 0x00)
    i2c_start();      // bat dau doc du lieu
    i2c_write(0xd1);      // gui ma lenh doc du lieu tu dia chi(add)
    dat = i2c_read(0);      // doc xong thi luu gia tri da doc dc vao dat
    i2c_stop();            // ket thuc qua trinh doc du lieu
    dat = (dat & 0x0f) + (dat>>4)*10;     // du lieu doc ra o dang BCD nen chuyen sang he 10                      
    return (dat);  // tra ve gia tri da doc duoc
}
unsigned char docdulieu(unsigned char add)
{
    unsigned char dat;
    
    i2c_start();   // bat dau doc
    
    i2c_write(0xd0);     // dau tien gui lenh ghi du lieu(ghi dia chi can lay du lieu trong DS1307)
    i2c_write(add); // Dia chi ma ta muon doc ( vi du, muon doc giay thi ta ghi dia chi 0x00)
    i2c_start();      // bat dau doc du lieu
    i2c_write(0xd1);      // gui ma lenh doc du lieu tu dia chi(add)
    dat = i2c_read(0);      // doc xong thi luu gia tri da doc dc vao dat
    i2c_stop();            // ket thuc qua trinh doc du lieu         
    return (dat);  // tra ve gia tri da doc duoc
}
void chuyen(unsigned char b)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        DS = b & (0x80>>i);        // Lay tung Bit cua byte b gui ra DS, lay bit MSB truoc

        // Tao xung dich du lieu
            clk = 0;
            clk = 1;
    }
}

// dich ma vao hc595
void hang(unsigned char sohang)
{
 switch(sohang)
 {
  case 1:{_A=0;_B=0;OE=1;break;} 
  case 2:{_A=1;_B=0;OE=1;break;}
  case 3:{_A=0;_B=1;OE=1;break;}
  case 4:{_A=1;_B=1;OE=1;break;} 
 }
}

// xuat toan bo bien trong mang ma[][] ra ngoai + quet led + bam xung chan OE de dieu chinh do sang
void hienthi()
{
 
   unsigned char a,b,x;  
    for(x=1;x<5;x++)
    {    
       for(a=0;a<8;a++)
       {
          for(b=16;b>0;b=b-4)
          {
           chuyen(ma[b-x][a]);  
          }
       }         
   xuat=0;
   xuat=1;  
   hang(5-x);                                                      
   delay(sang); 
   OE=0;     
   delay(1000-sang);
   }  
}
void xoamanhinh()
{                     
 unsigned char x,y;
 for(x=0;x<16;x++)
 {               
  for(y=0;y<8;y++)
  {
   ma[x][y]=0xff;
  }  
 } 
 hienthi();
}  
  
//void ghichu()
//{
//  unsigned char a,b,byte6,byte7;       
//  unsigned char d;   
//  d=giatri;
//   
//(((d>>4)&0x0F)<=9)?(byte6=(d>>4)&0x0F):(byte6='A'+((d>>4)&0x0F)-0x0A);
//((d&0x0F)<=9)?(byte7=d&0x0F):(byte7='A'+(d&0x0F)-0x0A);
//
//  for(a=1;a<17;a++)
//  {     
//   if(byte6 <=9){ma[a-1][6]=so[byte6][a-1];} else { ma[a-1][6]=chu[byte6-65][a-1]; }  
//   if(byte7 <=9){ma[a-1][7]=so[byte7][a-1];} else { ma[a-1][7]=chu[byte7-65][a-1]; }
//  }       
//} 
//

void ghithoigian()
{
 unsigned char a;
  for(a=1;a<17;a++)
  {     
    ma[a-1][0]=so[gio/10][a-1];       
    ma[a-1][1]=so[gio%10][a-1];   
    ma[a-1][2]=so[10][a-1];   
    ma[a-1][3]=so[phut/10][a-1];   
    ma[a-1][4]=so[phut%10][a-1];   
    ma[a-1][5]=so[10][a-1];   
    ma[a-1][6]=so[giay/10][a-1];   
    ma[a-1][7]=so[giay%10][a-1];         
  }  
}

void thanhtruotbat()
{
 unsigned char a,b,c; 
 EIMSK=0x00;  // cam ngat ngoai 0  <at328>
 
 for(b=0;b<15;b++)
 {   
     for(a=16;a>0;a--)                                
      { 
       ma[a-1][4]=~thanhtruotIphone[b][a-1][0];   
       ma[a-1][5]=~thanhtruotIphone[b][a-1][1];   
       ma[a-1][6]=~thanhtruotIphone[b][a-1][2];   
       ma[a-1][7]=~thanhtruotIphone[b][a-1][3]; 
      }  
      for(c=0;c<3;c++){hienthi();}     
  
  } 
  EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
 }  
 
void thanhtruottat()
{  
  unsigned char a,b,c;   
   EIMSK=0x00;  // cam ngat ngoai 0  <at328>
 for(b=16;b>0;b--)
 {   
     for(a=16;a>0;a--)                                
      { 
       ma[a-1][4]=~thanhtruotIphone[b-1][a-1][0];   
       ma[a-1][5]=~thanhtruotIphone[b-1][a-1][1];   
       ma[a-1][6]=~thanhtruotIphone[b-1][a-1][2];   
       ma[a-1][7]=~thanhtruotIphone[b-1][a-1][3]; 
      }  
      for(c=0;c<3;c++){hienthi();}     
  }    
  EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
}
//--------------lat giay------------
void lattrang()   
{
 unsigned char a,b,c;     
 sang=sang-2;
  if(giay!=0)
  {
      for(c=0;c<14;c++)
      {
         for(a=16;a>1;a--)
         {
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7]; 
         }   
             for(b=0;b<2;b++)
            {
             hienthi();
            }    
      }      
      for(c=0;c<14;c++)
      {
      ma[0][6]=so[giay/10][15-c]; 
      ma[0][7]=so[giay%10][15-c];   
            for(b=0;b<2;b++)
            {
             hienthi();
            }  
           for(a=16;a>1;a--)
             {
               ma[a-1][6]=ma[a-2][6];   
               ma[a-1][7]=ma[a-2][7]; 
             } 
      }   
              
       ma[0][6]=0xff; 
       ma[0][7]=0xff; 
       for(b=0;b<2;b++)
            {
             hienthi();
            } 
            for(a=16;a>1;a--)
             {
               ma[a-1][6]=ma[a-2][6];   
               ma[a-1][7]=ma[a-2][7]; 
             }  
       ma[0][6]=0xff; 
       ma[0][7]=0xff;
  }       
  else if(giay==0 && phut !=0)
  {
      for(c=0;c<14;c++)
      {
         for(a=16;a>1;a--)
         {   
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4]; 
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7]; 
         }   
             for(b=0;b<2;b++)
            {
             hienthi();
            }    
      }      
      for(c=0;c<14;c++)
      { 
      ma[0][3]=so[phut/10][15-c]; 
      ma[0][4]=so[phut%10][15-c];  
      ma[0][6]=so[giay/10][15-c]; 
      ma[0][7]=so[giay%10][15-c];   
            for(b=0;b<2;b++)
            {
             hienthi();
            }  
           for(a=16;a>1;a--)
             {    
               ma[a-1][3]=ma[a-2][3];   
               ma[a-1][4]=ma[a-2][4]; 
               ma[a-1][6]=ma[a-2][6];   
               ma[a-1][7]=ma[a-2][7]; 
             } 
      }   
         
       ma[0][3]=0xff;ma[0][4]=0xff;ma[0][6]=0xff;ma[0][7]=0xff; 
       for(b=0;b<2;b++)
            {
             hienthi();
            } 
            for(a=16;a>1;a--)
             {
               ma[a-1][3]=ma[a-2][3];   
               ma[a-1][4]=ma[a-2][4]; 
               ma[a-1][6]=ma[a-2][6];   
               ma[a-1][7]=ma[a-2][7]; 
             }  
       ma[0][3]=0xff;ma[0][4]=0xff;ma[0][6]=0xff;ma[0][7]=0xff; 
  }   
  else if(giay==0 && phut ==0)
  {
      for(c=0;c<14;c++)
      {
         for(a=16;a>1;a--)
         {   
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1]; 
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4]; 
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7]; 
         }   
             for(b=0;b<2;b++)
            {
             hienthi();
            }    
      }      
      for(c=0;c<14;c++)
      {  
      ma[0][0]=so[nam/10][15-c]; 
      ma[0][1]=so[nam%10][15-c];  
      ma[0][3]=so[phut/10][15-c]; 
      ma[0][4]=so[phut%10][15-c];  
      ma[0][6]=so[giay/10][15-c]; 
      ma[0][7]=so[giay%10][15-c];   
            for(b=0;b<2;b++)
            {
             hienthi();
            }  
           for(a=16;a>1;a--)
             {    
               ma[a-1][0]=ma[a-2][0];   
               ma[a-1][1]=ma[a-2][1]; 
               ma[a-1][3]=ma[a-2][3];   
               ma[a-1][4]=ma[a-2][4]; 
               ma[a-1][6]=ma[a-2][6];   
               ma[a-1][7]=ma[a-2][7]; 
             } 
      }   
         
       ma[0][0]=0xff;ma[0][1]=0xff;ma[0][3]=0xff;ma[0][4]=0xff;ma[0][6]=0xff;ma[0][7]=0xff; 
       for(b=0;b<2;b++)
            {
             hienthi();
            } 
            for(a=16;a>1;a--)
             {
               ma[a-1][0]=ma[a-2][0];   
               ma[a-1][1]=ma[a-2][1]; 
               ma[a-1][3]=ma[a-2][3];   
               ma[a-1][4]=ma[a-2][4]; 
               ma[a-1][6]=ma[a-2][6];   
               ma[a-1][7]=ma[a-2][7]; 
             }  
       ma[0][0]=0xff;ma[0][1]=0xff;ma[0][3]=0xff;ma[0][4]=0xff;ma[0][6]=0xff;ma[0][7]=0xff; 
  } 
  sang=sang+2;    
} 

//----------------------------------------------------


void quetchu() //
{
 unsigned char a,b;   
sang=sang-2;
if(giay!=0)
{ 
 if((giay%2)==1)
 {
  for(b=0;b<8;b++) 
       {    

          for(a=1;a<17;a++) 
               {    
                  ma[a-1][6]=ma[a-1][6] & ~(0x80>>b);                
               }
               hienthi();  hienthi();hienthi();hienthi();
            for(a=1;a<17;a++) 
               {  
                  ma[a-1][6]= ma[a-1][6] | so[giay/10][a-1] &(0x80>>b);          
               } 
            
       }  
    for(b=0;b<8;b++) 
       {    

          for(a=1;a<17;a++) 
               {    
                  ma[a-1][7]=ma[a-1][7] & ~(0x80>>b);                
               }
               hienthi();  hienthi();hienthi();hienthi();
            for(a=1;a<17;a++) 
               {  
                  ma[a-1][7]= ma[a-1][7] | so[giay%10][a-1] &(0x80>>b);          
               } 
       } 
  }
  else
  {      
          for(a=1;a<17;a++) 
               {               
                     ma[a-1][6]=0x00;
                     ma[a-1][7]=0x00;  
                    if(a!=1)
                    { 
                     ma[a-2][6]=so[giay/10][a-2];          
                     ma[a-2][7]=so[giay%10][a-2];     
                    }
                     
                    hienthi();  hienthi();hienthi();hienthi();
               }   
                ma[15][6]=0xff;
                ma[15][7]=0xff;            
  }   
 }  
 else if(giay==0 && phut !=0)
 {
  {      
          for(a=1;a<17;a++) 
               {       
                    ma[a-1][3]=0x00;ma[a-1][4]=0x00;ma[a-1][6]=0x00;ma[a-1][7]=0x00;  
                    if(a!=1)
                    {
                     ma[a-2][3]=so[phut/10][a-2];          
                     ma[a-2][4]=so[phut%10][a-2];      
                     ma[a-2][6]=so[giay/10][a-2];          
                     ma[a-2][7]=so[giay%10][a-2];     
                    }
                     
                    hienthi();  hienthi();hienthi();hienthi();
               }   
                   ma[15][3]=0xff;ma[15][4]=0xff;ma[15][6]=0xff;ma[15][7]=0xff;            
  }
 }
 
 else if(giay==0 && phut ==0)
  {
          for(a=1;a<17;a++) 
               {       
                    ma[a-1][0]=0x00;ma[a-1][1]=0x00;ma[a-1][3]=0x00;ma[a-1][4]=0x00;ma[a-1][6]=0x00;ma[a-1][7]=0x00;  
                    if(a!=1)
                    {   
                     ma[a-2][3]=so[gio/10][a-2];          
                     ma[a-2][4]=so[gio%10][a-2]; 
                     ma[a-2][3]=so[phut/10][a-2];          
                     ma[a-2][4]=so[phut%10][a-2];      
                     ma[a-2][6]=so[giay/10][a-2];          
                     ma[a-2][7]=so[giay%10][a-2];     
                    }
                     
                    hienthi();  hienthi();hienthi();hienthi();
               }   
                  ma[15][0]=0xff;ma[15][1]=0xff; ma[15][3]=0xff;ma[15][4]=0xff;ma[15][6]=0xff;ma[15][7]=0xff;        
 
  }     
  sang=sang+2;
}



//====================================================================================
unsigned int tinhlich(unsigned char ngayduong,unsigned char thangduong, unsigned char namduong)
{
	unsigned int songay,t5;
	unsigned char ngayam,thangam;
if(nam%4==0) songay=count_year[namduong]+count_month1[thangduong]+ngayduong;
else songay=count_year[namduong]+count_month[thangduong]+ngayduong; 
songay--; 
songay=songay-count_year1[namduong]; 

for(t5=sothang[namduong];t5<262;t5++) 
{
	if(songay==0)break;
 	if(songay>50000)break;

 	if(lich[t5]>16) { songay=songay-30;}
	else            { songay=songay-29;}
}
    if(songay==0) { if(lich[t5-1]>16) { thangam=lich[t5-1]-16; ngayam=30; }
                    else              { thangam=lich[t5-1];    ngayam=29; } }
  else            { if(lich[t5-1]>16) { thangam=lich[t5-1]-16; ngayam=songay+30; }
	                  else              { thangam=lich[t5-1];    ngayam=songay+29; } }


	t5= thangam << 8  ;
	t5 = t5 + ngayam;
	return(t5);
}

void am_lich()
 {	
 unsigned int t;
 t = tinhlich(ngay,thang,nam);			
 ngay_al=t & 0xff;
 thang_al= t >> 8;			
 }
                                                                           
//---------------------------The End --------------------------------------------------------------------                                                                          
 
//----------------------Dich Ram sang trai (quet chu Dong Ho Led)------------------------//
void chaychu()
{
  unsigned char i,y;
  for(y=1;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }   
  
    
   for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1;    
          ma[i-1][7]= ma[i-1][7] | ((font[i-1][dem1] & (0x80>>dem) ) >> (7-dem));  
      } 
     dem++;if(dem==8){dem=0;dem1++;if(dem1>42){dem1=0;xoamanhinh();}}   
    for(i=0;i<2;i++){hienthi();} // hien thi 
}
//-------------------------------------------------------------------------------------//

//----------------------Dich Ram sang trai (quet chu gocdiy.com)------------------------//

void chaychu2()
{
  unsigned char i,y;    
  for(y=1;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }    
    
  for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{chonchu='G'-65;break;}  
             case 1:{chonchu='O'-65;break;}
             case 2:{chonchu='C'-65;break;}
             case 3:{chonchu='D'-65;break;}
             case 4:{chonchu='I'-65;break;}
             case 5:{chonchu='Y'-65;break;}
             case 6:{chonchu=27;break;}
             case 7:{chonchu='C'-65;break;}  
             case 8:{chonchu='O'-65;break;}
             case 9:{chonchu='M'-65;break;}  
             case 11:{chonchu=30;break;}
             default:{chonchu=29;break;}                  
           }; 
  
          ma[i-1][7]= ma[i-1][7] | ((chu[chonchu][i-1] & (0x80>>dem) ) >> (7-dem));  
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<3;i++){hienthi();} // hien thi 
}

//----------------------Dich Ram sang trai (quet chu THOI GIAN)------------------------//

void chaychu5()
{ 
  unsigned char i,y;     
  for(y=5;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }     
  for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{chonchu=29;break;}  
             case 1:{chonchu='G'-65;break;}
             case 2:{chonchu='I'-65;break;}
             case 3:{chonchu='A'-65;break;}
             case 4:{chonchu='N'-65;break;}
             case 5:{chonchu=29;break;}
             case 6:{chonchu=29;break;}  
             case 7:{chonchu='T'-65;break;}
             case 8:{chonchu='H'-65;break;}
             case 9:{chonchu=43;break;}
             case 10:{chonchu='I'-65;break;}
             default:{chonchu=29;break;}                  
           }; 
          ma[i-1][7]= ma[i-1][7] | ((chu[chonchu][i-1] & (0x80>>dem) ) >> (7-dem)); 
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<5;i++){hienthi();} // hien thi 
}

//----------------------Dich Ram sang trai (quet chu DO SANG)------------------------//
void chaychu6()
{ 
  unsigned char i,y;     
  for(y=5;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }     
  for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{chonchu=36;break;}  
             case 1:{chonchu='N'-65;break;}
             case 2:{chonchu='G'-65;break;}
             case 3:{chonchu=29;break;}
             case 4:{chonchu=29;break;}
             case 5:{chonchu=45;break;}
             case 6:{chonchu=44;break;}  
             case 7:{chonchu=29;break;} 
             case 8:{chonchu='S'-65;break;}        
             default:{chonchu=29;break;}                  
           }; 
  
          ma[i-1][7]= ma[i-1][7] | ((chu[chonchu][i-1] & (0x80>>dem) ) >> (7-dem));  
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<5;i++){hienthi();} // hien thi 
}

//----------------------Dich Ram sang trai (quet chu BAO THUC)------------------------//
void chaychu7()
{ 
  unsigned char i,y;     
  for(y=5;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }     
  for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{chonchu='T'-65;break;}  
             case 1:{chonchu='H'-65;break;}
             case 2:{chonchu=33;break;}
             case 3:{chonchu='C'-65;break;}
             case 4:{chonchu=29;break;}
             case 5:{chonchu=29;break;}
             case 6:{chonchu='B'-65;break;}  
             case 7:{chonchu=36;break;} 
             case 8:{chonchu='O'-65;break;}        
             default:{chonchu=29;break;}                  
           }; 
  
          ma[i-1][7]= ma[i-1][7] | ((chu[chonchu][i-1] & (0x80>>dem) ) >> (7-dem));  
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<5;i++){hienthi();} // hien thi 
}

//----------------------Dich Ram sang trai (quet chu BU GIO)------------------------//
void chaychu8()
{ 
  unsigned char i,y;     
  for(y=5;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }     
  for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{chonchu='I'-65;break;}  
             case 1:{chonchu=43;break;}
             case 2:{chonchu=29;break;}
             case 3:{chonchu=29;break;}
             case 4:{chonchu='B'-65;break;}
             case 5:{chonchu=46;break;}
             case 6:{chonchu=29;break;}  
             case 7:{chonchu='G'-65;break;}      
             default:{chonchu=29;break;}                  
           }; 
  
          ma[i-1][7]= ma[i-1][7] | ((chu[chonchu][i-1] & (0x80>>dem) ) >> (7-dem));  
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<5;i++){hienthi();} // hien thi 
}



//----------------------Dich Ram sang trai (quet chu Trang Thai)------------------------//
void chaychutrangthai()
{ 
  unsigned char i,y;     
  for(y=5;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }     
  for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{chonchu='G'-65;break;}  
             case 1:{chonchu=29;break;}
             case 2:{chonchu='T'-65;break;}
             case 3:{chonchu='H'-65;break;}
             case 4:{chonchu=36;break;}
             case 5:{chonchu='I'-65;break;}
             case 6:{chonchu=29;break;}   
             case 7:{chonchu=29;break;}  
             case 8:{chonchu='T'-65;break;}      
             case 9:{chonchu='R'-65;break;}      
             case 10:{chonchu=49;break;}         
             case 11:{chonchu='N'-65;break;}      
             default:{chonchu=29;break;}                  
           }; 
  
          ma[i-1][7]= ma[i-1][7] | ((chu[chonchu][i-1] & (0x80>>dem) ) >> (7-dem));  
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<5;i++){hienthi();} // hien thi 
}


//----------------------Dich Ram sang trai chay ngay thang nam------------------------//

void chaychu4()
{
  unsigned char i,y;     
  for(y=1;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }   
  
    
   for(i=1;i<17;i++)
      {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
           {
             case 0:{ma[i-1][7]= ma[i-1][7] | ((chu['H'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 1:{ma[i-1][7]= ma[i-1][7] | ((chu[39][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 2:{ma[i-1][7]= ma[i-1][7] | ((chu['M'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 3:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 4:{ma[i-1][7]= ma[i-1][7] | ((chu['N'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 5:{ma[i-1][7]= ma[i-1][7] | ((chu['A'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 6:{ma[i-1][7]= ma[i-1][7] | ((chu['Y'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 7:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 8:{ma[i-1][7]= ma[i-1][7] | ((chu[t1][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 9:{ma[i-1][7]= ma[i-1][7] | ((chu[t2][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 10:{ma[i-1][7]= ma[i-1][7] | ((chu[t3][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 11:{ma[i-1][7]= ma[i-1][7] | ((chu[t4][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 12:{ma[i-1][7]= ma[i-1][7] | ((chu[t5][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 13:{ma[i-1][7]= ma[i-1][7] | ((chu[t6][i-1] & (0x80>>dem) ) >> (7-dem));break;}   
             case 14:{ma[i-1][7]= ma[i-1][7] | ((chu[t7][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 15:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 16:{ma[i-1][7]= ma[i-1][7] | ((chu['N'-65][i-1] & (0x80>>dem) ) >> (7-dem)); break;}  
             case 17:{ma[i-1][7]= ma[i-1][7] | ((chu['G'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 18:{ma[i-1][7]= ma[i-1][7] | ((chu[35][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 19:{ma[i-1][7]= ma[i-1][7] | ((chu['Y'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 20:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}  
             case 21:{ma[i-1][7]= ma[i-1][7] | ((so[ngay/10][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 22:{ma[i-1][7]= ma[i-1][7] | ((so[ngay%10][i-1] & (0x80>>dem) ) >> (7-dem)); break;}   
             case 23:{ma[i-1][7]= ma[i-1][7] | ((chu[38][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 24:{ma[i-1][7]= ma[i-1][7] | ((so[thang/10][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 25:{ma[i-1][7]= ma[i-1][7] | ((so[thang%10][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 26:{ma[i-1][7]= ma[i-1][7] | ((chu[38][i-1] & (0x80>>dem) ) >> (7-dem)); break;} 
             case 27:{ma[i-1][7]= ma[i-1][7] | ((so[2][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 28:{ma[i-1][7]= ma[i-1][7] | ((so[0][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 29:{ma[i-1][7]= ma[i-1][7] | ((so[nam/10][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 30:{ma[i-1][7]= ma[i-1][7] | ((so[nam%10][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 31:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}    
             case 32:{ma[i-1][7]= ma[i-1][7] | ((so[nhietdo/10][i-1] & (0x80>>dem) ) >> (7-dem)); break;}   
             case 33:{ma[i-1][7]= ma[i-1][7] | ((so[nhietdo%10][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 34:{ma[i-1][7]= ma[i-1][7] | ((chu[41][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 35:{ma[i-1][7]= ma[i-1][7] | ((chu['C'-65][i-1] & (0x80>>dem) ) >> (7-dem)); break;} 
             case 36:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem)); break;}    
             case 37:{ma[i-1][7]= ma[i-1][7] | ((chu[34][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 38:{ma[i-1][7]= ma[i-1][7] | ((chu['L'-65][i-1] & (0x80>>dem) ) >> (7-dem)); break;}   
             case 39:{ma[i-1][7]= ma[i-1][7] | ((chu[28][i-1] & (0x80>>dem) ) >> (7-dem)); break;}   
             case 40:{ma[i-1][7]= ma[i-1][7] | ((so[ngay_al/10][i-1] & (0x80>>dem) ) >> (7-dem)); break;} 
             case 41:{ma[i-1][7]= ma[i-1][7] | ((so[ngay_al%10][i-1] & (0x80>>dem) ) >> (7-dem)); break;} 
             case 42:{ma[i-1][7]= ma[i-1][7] | ((chu[38][i-1] & (0x80>>dem) ) >> (7-dem)); break;}   
             case 43:{ma[i-1][7]= ma[i-1][7] | ((so[thang_al/10][i-1] & (0x80>>dem) ) >> (7-dem)); break;} 
             case 44:{ma[i-1][7]= ma[i-1][7] | ((so[thang_al%10][i-1] & (0x80>>dem) ) >> (7-dem)); break;} 
             default:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}                       
           };   
           
      } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<3;i++){hienthi();} // hien thi 
}



void chaychuchucmungsinhnhat()
{
   unsigned char i,y;     
  for(y=1;y<8;y++)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] << 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y] & 0x80 ) >>7);  
      }   
  }   
  
  for(i=1;i<17;i++)
 {                   
          ma[i-1][7]= ma[i-1][7] << 1; 
           switch (dem1) 
          {
             case 0:{ma[i-1][7]= ma[i-1][7]  | ((chu['C'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 1:{ma[i-1][7]= ma[i-1][7]  | ((chu['H'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 2:{ma[i-1][7]= ma[i-1][7]  | ((chu[33][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 3:{ma[i-1][7]= ma[i-1][7]  | ((chu['C'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 4:{ma[i-1][7]= ma[i-1][7]  | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 5:{ma[i-1][7]= ma[i-1][7]  | ((chu['M'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 6:{ma[i-1][7]= ma[i-1][7]  | ((chu[46][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 7:{ma[i-1][7]= ma[i-1][7]  | ((chu['N'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 8:{ma[i-1][7]= ma[i-1][7]  | ((chu['G'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 9:{ma[i-1][7]= ma[i-1][7]  | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem)); break;}
             case 10:{ma[i-1][7]= ma[i-1][7] | ((chu['S'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}
             case 11:{ma[i-1][7]= ma[i-1][7] | ((chu['I'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 12:{ma[i-1][7]= ma[i-1][7] | ((chu['N'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 13:{ma[i-1][7]= ma[i-1][7] | ((chu['H'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;}   
             case 14:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 15:{ma[i-1][7]= ma[i-1][7] | ((chu['N'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 16:{ma[i-1][7]= ma[i-1][7] | ((chu['H'-65][i-1] & (0x80>>dem) ) >> (7-dem)); break;}  
             case 17:{ma[i-1][7]= ma[i-1][7] | ((chu[40][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             case 18:{ma[i-1][7]= ma[i-1][7] | ((chu['T'-65][i-1] & (0x80>>dem) ) >> (7-dem));break;} 
             default:{ma[i-1][7]= ma[i-1][7] | ((chu[29][i-1] & (0x80>>dem) ) >> (7-dem));break;}                       
           };   
           
 } 
    dem++;if(dem==8){dem=0;dem1++;}
    for(i=0;i<3;i++){hienthi();} // hien thi 
  
 }

//----------------------Dich Ram sang phai------------------------//

void chaychu3()
{
  unsigned char i,y;     
  for(y=8;y>1;y--)
  {        
      for(i=1;i<17;i++)
      {                   
          ma[i-1][y-1]= ma[i-1][y-1] >> 1;
          ma[i-1][y-1]= ma[i-1][y-1] | ((ma[i-1][y-2] & 0x01 ) <<7);  
      }   
  }   
   for(i=1;i<17;i++)
      {                   
          ma[i-1][0]= ma[i-1][0] >> 1;   
           switch (dem1) 
           {
             case 0:{chonchu=giay%10;break;}  
             case 1:{chonchu=giay/10;break;}
             case 2:{chonchu=10;break;}
             case 3:{chonchu=phut%10;break;}
             case 4:{chonchu=phut/10;break;}
             case 5:{chonchu=10;break;}
             case 6:{chonchu=gio%10;break;}
             case 7:{chonchu=gio/10;break;}   
             default:{chonchu=1;break;}          
           };                
          ma[i-1][0]= ma[i-1][0] | ((so[chonchu][i-1] & (0x01<<dem) ) << (7-dem));  
      } 
      dem++;if(dem==8){dem=0;dem1++;}
      for(i=0;i<2;i++){hienthi();} // hien thi 
}

//----------------------------------------------------------------------------------//

void chaychudongholed()
{
 int i;
 for(i=0;i<344;i++)
 { 
   chaychu();
 } 
 dem1=0;
 dem=0;
}

void chaychuwwebsite()
{
 unsigned char a,b,c;      
 //--------------------------------------quet xuong chu web ------------------------//
 for(c=0;c<17;c++)
  {
  ma[0][0]=chu['W'-65][17-c]; 
  ma[0][1]=chu['E'-65][17-c];     
  ma[0][2]=chu['B'-65][17-c];  
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];
         } 
  }   
 //------------------------------------------------------------------------------------   
 //--------------------------------------quet xuong chu site ------------------------//      
for(c=0;c<17;c++)
  {
  ma[0][3]=chu['S'-65][17-c]; 
  ma[0][4]=chu['I'-65][17-c];     
  ma[0][5]=chu['T'-65][17-c];      
  ma[0][6]=chu['E'-65][17-c];  
       for(b=0;b<3;b++){hienthi();}  // hien thi
       for(a=16;a>1;a--)
         {
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];    
           ma[a-1][6]=ma[a-2][6];
         } 
  } 
  //------------------------------------------------------------------------------------//
  //--------------------------------------nhap nhay giau 2 cham ------------------------// 
  for(c=0;c<10;c++)
  {
    for(a=1;a<17;a++)
    {
     ma[a-1][7]=0xFF;     // xoa dau 2 cham khoi man hinh
    } 
    for(b=0;b<10;b++){hienthi();}      // hien thi ra ngoai   
    
    for(a=1;a<17;a++)
    {
     ma[a-1][7]=chu[28][a-1];     // ghi dau 2 cham vao man hinh
    } 
    for(b=0;b<10;b++){hienthi();}      // hien thi ra ngoai        
  }
  //------------------------------------------------------------------------------------//   
  //-------------------------goi ham chay chu gocdiy sang trai--------------------------//   
   for(c=0;c<152;c++)
  {
   chaychu2();
  }      
  dem1=0; 
  dem=0; 
  sang=100;
  for(b=0;b<100;b++){hienthi();}      // delay 1 luc      
  //------------------------------------------------------------------------------------//  
  //---------------------------nap nang luong vao nut keo----------------------------------------// 
  for(c=12;c>2;c--)
  {
    sang=(11-(c-2))*100;   // thay doi do sang
    ma[c][0]=ma[c][0] & 0x9F ;for(b=0;b<50;b++){hienthi();}      // delay 1 luc 
  }   
  //---------------------------nhap nhay nut keo------------------------------------//
  for(c=0;c<10;c++)
  {
    for(a=1;a<17;a++)
    {
     ma[a-1][0]=0xFF;     // xoa nut keo khoi man hinh
    } 
    for(b=0;b<10;b++){hienthi();}      // hien thi ra ngoai   
    
    for(a=1;a<17;a++)
    {
     ma[a-1][0]=chu[31][a-1];     // ghi nut keo vao man hinh
    } 
    for(b=0;b<10;b++){hienthi();}      // hien thi ra ngoai        
  }                
 //---------------------------goi ham dich ram sang phai------------------------------------//     
  laydosang();
   for(c=0;c<64;c++)
  {
   chaychu3();
  }     
  dem=dem1=0;   
}

//--------------------------------------END-------------------------------------------------// 

//-----------------------------cai dat thoi gian-----------------------------------------//
void caigio()
{
unsigned char a,b,c;   
  //--------------------------quet xuong chu GIO ---------------------------------------//
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu['G'-65][17-c]; 
  ma[0][1]=chu['I'-65][17-c];     
  ma[0][2]=chu[32][17-c];   
  ma[0][3]=so[10][17-c]; 
  ma[0][4]=so[gio/10][17-c];     
  ma[0][5]=so[gio%10][17-c];    
  ma[0][6]=0xff;    
  ma[0][7]=0xff; 
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];  
           ma[a-1][6]=ma[a-2][6];     
           ma[a-1][7]=ma[a-2][7];   
         } 
  } 
  ma[0][2]=chu[32][0];    
  while(1)
  {  
  hienthi(); // luon luon phai quet hien thi
  //-----------------------cai gio---------------------//    
  //---code duoi dung de kiem tra nhan nut UP va cuon len tren
  if(up==0 || nut==20)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}gio++;if(gio>23)gio=0;
  for(c=0;c<17;c++)
  {
  ma[0][4]=so[gio/10][17-c];ma[0][5]=so[gio%10][17-c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][4]=ma[a-2][4];ma[a-1][5]=ma[a-2][5];}
  }
  EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
  }   
  //---code duoi dung de kiem tra nhan nut DOWN va cuon xuong duoi
  if(down==0 || nut ==21)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}if(gio>0){gio--;}else gio=23;
  for(c=0;c<15;c++)
  {
  ma[15][4]=so[gio/10][c];ma[15][5]=so[gio%10][c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][4]=ma[a+1][4];ma[a][5]=ma[a+1][5];}
  }
  EIMSK=0x01;  //cho phep ngat ngoai 0  <at328>
  }   
 //---------------------------------------------------//  
 if(ok==0 || nut ==22)
  {    
   EIMSK=0x00;  //  k  cho phep ngat ngoai 0  <at328>             
   nut=0;
   ghids(2,gio);
   while(ok==0){hienthi();}  
 //--------------------------quet xuong chu PHUT ---------------------------------------//
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu['P'-65][17-c]; 
  ma[0][1]=chu['H'-65][17-c];     
  ma[0][2]=chu[33][17-c];  
  ma[0][3]=chu['T'-65][17-c];  
  ma[0][4]=so[10][17-c]; 
  ma[0][5]=so[phut/10][17-c];     
  ma[0][6]=so[phut%10][17-c];    
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];  
         } 
  }   
  
  ma[0][2]=chu[33][0];  
  EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>             
   //-----------------------cai phut---------------------//    
  //---code duoi dung de kiem tra nhan nut UP va cuon len tren    
  while(1)
  {   
  hienthi();
  if(up==0 || nut ==20)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}phut++;if(phut>59)phut=0;
  for(c=0;c<17;c++)
  {
  ma[0][5]=so[phut/10][17-c];ma[0][6]=so[phut%10][17-c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
  }EIMSK=0x01;  // 1 cho phep ngat ngoai 0  <at328>
  }   
  //---code duoi dung de kiem tra nhan nut DOWN va cuon xuong duoi
  if(down==0||nut==21)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}if(phut>0){phut--;}else phut=59;
  for(c=0;c<15;c++)
  {
  ma[15][5]=so[phut/10][c];ma[15][6]=so[phut%10][c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
  }EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
  } 
 //---------------------------------------------------//      
  if(ok==0 || nut ==22)
  {   
   EIMSK=0x00;  //  k  cho phep ngat ngoai 0  <at328>              
   nut=0;
   ghids(1,phut);
   while(ok==0){hienthi();}  
 //--------------------------quet xuong chu GIAY ---------------------------------------//
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu['G'-65][17-c]; 
  ma[0][1]=chu['I'-65][17-c];     
  ma[0][2]=chu[34][17-c];  
  ma[0][3]=chu['Y'-65][17-c];  
  ma[0][4]=so[10][17-c]; 
  ma[0][5]=so[giay/10][17-c];     
  ma[0][6]=so[giay%10][17-c];    
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];  
         } 
  }     
  ma[0][2]=chu[34][0];  
  EIMSK=0x01;  //  k  cho phep ngat ngoai 0  <at328>             
  while(1)
  {   
  hienthi();
  if(up==0 || nut ==20)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}giay++;if(giay>59)giay=0;
  for(c=0;c<17;c++)
  {
  ma[0][5]=so[giay/10][17-c];ma[0][6]=so[giay%10][17-c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
  }EIMSK=0x01;  // 1 cho phep ngat ngoai 0  <at328>
  }   
  //---code duoi dung de kiem tra nhan nut DOWN va cuon xuong duoi
  if(down==0 || nut ==21)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}if(giay>0){giay--;}else giay=59;
  for(c=0;c<15;c++)
  {
  ma[15][5]=so[giay/10][c];ma[15][6]=so[giay%10][c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
  }EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
  } 
 //---------------------------------------------------//        
  if(ok==0 || nut ==22)
  { 
   EIMSK=0x00;  //  k  cho phep ngat ngoai 0  <at328>                  
   nut=0;
   ghids(0,giay);
   while(ok==0){hienthi();}              
   //--------------------------quet xuong chu NGAY ---------------------------------------//
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu['N'-65][17-c]; 
  ma[0][1]=chu['G'-65][17-c];     
  ma[0][2]=chu[35][17-c];  
  ma[0][3]=chu['Y'-65][17-c];  
  ma[0][4]=so[10][17-c]; 
  ma[0][5]=so[ngay/10][17-c];     
  ma[0][6]=so[ngay%10][17-c];    
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];  
         } 
  }     
  ma[0][2]=chu[35][0]; 
  EIMSK=0x01;  //    cho phep ngat ngoai 0  <at328>             
   while(1)
  {   
  hienthi();
  if(up==0 || nut ==20 )
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}ngay++;if(ngay>31)ngay=0;
  for(c=0;c<17;c++)
  {
  ma[0][5]=so[ngay/10][17-c];ma[0][6]=so[ngay%10][17-c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
  }EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
  }   
  //---code duoi dung de kiem tra nhan nut DOWN va cuon xuong duoi
  if(down==0 || nut ==21)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}if(ngay>0){ngay--;}else ngay=31;
  for(c=0;c<15;c++)
  {
  ma[15][5]=so[ngay/10][c];ma[15][6]=so[ngay%10][c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
  }EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
  } 
 //---------------------------------------------------// 
  if(ok==0 || nut ==22)
  {   
   EIMSK=0x00;  //  k  cho phep ngat ngoai 0  <at328>              
   nut=0; 
   ghids(4,ngay);  
   while(ok==0){hienthi();}     
     //--------------------------quet xuong chu THANG ---------------------------------------//
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu['T'-65][17-c]; 
  ma[0][1]=chu['H'-65][17-c];     
  ma[0][2]=chu[36][17-c];  
  ma[0][3]=chu['N'-65][17-c];  
  ma[0][4]=chu['G'-65][17-c]; 
  ma[0][5]=so[10][17-c];     
  ma[0][6]=so[thang/10][17-c];     
  ma[0][7]=so[thang%10][17-c];    
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7];  
         } 
  }     
  ma[0][2]=chu[36][0]; 
  EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>             
   while(1)
  {   
  hienthi();
  if(up==0 || nut ==20)
  {
  EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}thang++;if(thang>12)thang=0;
  for(c=0;c<17;c++)
  {
  ma[0][6]=so[thang/10][17-c];ma[0][7]=so[thang%10][17-c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][6]=ma[a-2][6];ma[a-1][7]=ma[a-2][7];}
  }EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
  }   
  //---code duoi dung de kiem tra nhan nut DOWN va cuon xuong duoi
  if(down==0 || nut ==21)
  {
  EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}if(thang>0){thang--;}else thang=12;
  for(c=0;c<15;c++)
  {
  ma[15][6]=so[thang/10][c];ma[15][7]=so[thang%10][c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][6]=ma[a+1][6];ma[a][7]=ma[a+1][7];}
  }EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
  } 
 //---------------------------------------------------//       
  if(ok==0 || nut==22)
  {   
   EIMSK=0x00;  //  k  cho phep ngat ngoai 0  <at328>                      
   nut=0;  
   ghids(5,thang);
   while(ok==0){hienthi();}     
     //--------------------------quet xuong chu NAM ---------------------------------------//
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu['N'-65][17-c]; 
  ma[0][1]=chu[37][17-c];     
  ma[0][2]=chu['M'-65][17-c];  
  ma[0][3]=so[10][17-c];     
  ma[0][4]=so[2][17-c];     
  ma[0][5]=so[0][17-c];   
  ma[0][6]=so[nam/10][17-c];     
  ma[0][7]=so[nam%10][17-c]; 
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];      
           ma[a-1][4]=ma[a-2][4];  
           ma[a-1][5]=ma[a-2][5];   
           ma[a-1][6]=ma[a-2][6];     
           ma[a-1][7]=ma[a-2][7];      
         } 
  }     
  ma[0][1]=chu[37][0];    
  EIMSK=0x01;  //  k  cho phep ngat ngoai 0  <at328>             
   while(1)
  {   
  hienthi();
  if(up==0 || nut ==20)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}nam++;if(nam>99)nam=17;
  for(c=0;c<17;c++)
  {
  ma[0][6]=so[nam/10][17-c];ma[0][7]=so[nam%10][17-c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][6]=ma[a-2][6];ma[a-1][7]=ma[a-2][7];}
  }EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
  }  
  //---code duoi dung de kiem tra nhan nut DOWN va cuon len
  if(down==0 || nut==21)
  {EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  nut=0;for(a=0;a<10;a++){hienthi();}if(nam>17){nam--;}else if(nam<=17) nam=99;
  for(c=0;c<15;c++)
  {
  ma[15][6]=so[nam/10][c];ma[15][7]=so[nam%10][c];     
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][6]=ma[a+1][6];ma[a][7]=ma[a+1][7];}
  }EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
  } 
 //---------------------------------------------------//     
 if(ok==0 || nut==22)
 {  
   EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>     
   nut=0; 
   ghids(6,nam);
   while(ok==0){hienthi();}       
   
   if(thang>=3)thu = (ngay+2*thang+(3*(thang+1)) / 5 + (2000+nam) + ((2000+nam) / 4)) % 7;
   else thu = (ngay+2*(thang+12)+(3*((thang+12)+1)) / 5 + ((2000+nam)-1) + (((2000+nam)-1) / 4)) % 7;
   thu++;   
   ghids(3,thu); 
   EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328> 
   return ; 
 }
 
 }
            
 }
 }
            
 }
 
 } 
  
}
 
 }
  
 }
 
    
 }
 }
 }  
      
}



void kiemtrathu()
{
 switch (docds(0x03)) 
   {
     case 2:
     {t1='T'-65;t2='H'-65;t3=33;t4=29;t5='H'-65;t6='A'-65;t7='I'-65;break;}  
     case 3:
     {t1='T'-65;t2='H'-65;t3=33;t4=29;t5='B'-65;t6='A'-65;t7=29;break;}  
     case 4:
     {t1='T'-65;t2='H'-65;t3=33;t4=29;t5='T'-65;t6='U'-65;t7=29;break;}  
     case 5:
     {t1='T'-65;t2='H'-65;t3=33;t4=29;t5='N'-65;t6=34;t7='M'-65;break;}  
     case 6:
     {t1='T'-65;t2='H'-65;t3=33;t4=29;t5='S'-65;t6=36;t7='U'-65;break;}  
     case 7:
     {t1='T'-65;t2='H'-65;t3=33;t4=29;t5='B'-65;t6=48;t7='Y'-65;break;}  
     case 1:
     {t1='C'-65;t2='H'-65;t3=27;t4='N'-65;t5='H'-65;t6=40;t7='T'-65;break;}    
   }; 

}

void chayngaythang()
{ 
  unsigned char a,b,c;
  unsigned int d;      
  EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328> 
  cobaothoat=0;
  laythoigiantrongds1(); 
  kiemtrathu();     
  laynhietdo(); 
  am_lich();   
  EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328> 
 // --cuon len : phut :   
  for(c=0;c<15;c++)
  { 
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=0;a<15;a++){ma[a][2]=ma[a+1][2];ma[a][3]=ma[a+1][3];ma[a][4]=ma[a+1][4];ma[a][5]=ma[a+1][5];
  }
  }  
 // --- cuon xuong Gio Giay
  for(c=0;c<17;c++)
  {  
  for(b=0;b<3;b++){hienthi();}  // hien thi 
  for(a=16;a>1;a--){ma[a-1][0]=ma[a-2][0];ma[a-1][1]=ma[a-2][1];ma[a-1][6]=ma[a-2][6];ma[a-1][7]=ma[a-2][7];}
  }  
  //-------------------------------------------------------   
  cobaothoat=0;
  if(ngay==ngaysinhnhat && thang==thangsinhnhat && giay>0 && phut%5==0)
  { 
    for(d=0;d<220;d++)
     {
       chaychuchucmungsinhnhat();  
       if(cobaothoat==1)
       {
        cobaothoat=0;  
         dem1=0; 
         dem=0;
        goto thoatchayngaythang;
       }
      }         
  }   
  else
  {
     for(d=0;d<424;d++)
      {
       chaychu4();  
       if(cobaothoat==1)
       {
        cobaothoat=0;  
         dem1=0; 
         dem=0;
        goto thoatchayngaythang;
       }
      } 
  }   
  
  dem1=0; 
  dem=0; 
  thoatchayngaythang:;  
  //-------------------------------------------------   
 for(c=0;c<15;c++)
  {    
  ma[0][2]=so[10][15-c]; 
  ma[0][3]=so[phut/10][15-c]; 
  ma[0][4]=so[phut%10][15-c];  
  ma[0][5]=so[10][15-c];  
        for(b=0;b<3;b++)
        {
         hienthi();
        }  
       for(a=16;a>1;a--)
         {
           ma[a-1][2]=ma[a-2][2];   
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];   
           ma[a-1][5]=ma[a-2][5];;
         } 
  }   
    
   giay=docds(0x00);      
  for(c=0;c<15;c++)
  {    
  ma[15][0]=so[gio/10][c]; 
  ma[15][1]=so[gio%10][c]; 
  ma[15][6]=so[giay/10][c];  
  ma[15][7]=so[giay%10][c];  
        for(b=0;b<3;b++)
        {
         hienthi();
        }  
       for(a=0;a<15;a++)
         {
           ma[a][0]=ma[a+1][0];   
           ma[a][1]=ma[a+1][1];   
           ma[a][6]=ma[a+1][6];   
           ma[a][7]=ma[a+1][7]; 
         } 
  }   
  
  giay=docds(0);   
}  
                               
void laythoigiantrongds()    // muc dich cua ham nay la lay gia tri thoi gian trong ds1307
{
   giay=docds(0x00); // doc gia tri trong thanh ghi 0x00 ( chính là thanh ghi giay)      
   if(giay==0)
   {
     phut=docds(0x01); // doc gia tri trong thanh ghi 0x01 ( chính là thanh ghi phut)
     if(phut==0)
     {  
       gio=docds(0x02); // doc gia tri trong thanh ghi 0x02 ( chính là thanh ghi gio) 
     }  
   }
}
void laythoigiantrongds3()    // muc dich cua ham nay la lay gia tri thoi gian trong ds1307
{
   giay=docds(0x00); // doc gia tri trong thanh ghi 0x00 ( chính là thanh ghi giay)   
   phut=docds(0x01); // doc gia tri trong thanh ghi 0x01 ( chính là thanh ghi phut)   
   gio=docds(0x02); // doc gia tri trong thanh ghi 0x02 ( chính là thanh ghi gio) 
}
void laythoigiantrongds1()    // muc dich cua ham nay la lay gia tri thoi gian trong ds1307
{
   giay=docds(0x00); // doc gia tri trong thanh ghi 0x00 ( chính là thanh ghi giay)      
   phut=docds(0x01); // doc gia tri trong thanh ghi 0x01 ( chính là thanh ghi phut)
   gio=docds(0x02); // doc gia tri trong thanh ghi 0x02 ( chính là thanh ghi gio) 
   ngay=docds(0x04); // doc gia tri trong thanh ghi 0x04 ( chính là thanh ghi ngay)   
   thu=docds(0x03); // doc gia tri trong thanh ghi 0x03 ( chính là thanh ghi thu)
   thang=docds(0x05); // doc gia tri trong thanh ghi 0x05 ( chính là thanh ghi thang) 
   nam=docds(0x06); // doc gia tri trong thanh ghi 0x06 ( chính là thanh ghi nam)    
}

void xuongchuluccaidat(unsigned char z,unsigned char x,unsigned char r
,unsigned char t,unsigned char j,unsigned char k,unsigned char l,unsigned char h)
{
unsigned char a,b,c;
EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu[z][17-c]; 
  ma[0][1]=chu[x][17-c];     
  ma[0][2]=chu[r][17-c];  
  ma[0][3]=chu[t][17-c];  
  ma[0][4]=chu[j][17-c]; 
  ma[0][5]=chu[k][17-c];     
  ma[0][6]=chu[l][17-c];  
  ma[0][7]=chu[h][17-c];   
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7];
         } 
  } 
  ma[0][1]=chu[35][0]; 
EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
}
void xuongchuluccaidatds(unsigned char z,unsigned char x,unsigned char r
,unsigned char t,unsigned char j,unsigned char k,unsigned char l,unsigned char h)
{
unsigned char a,b,c;
EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  for(c=0;c<17;c++)
  {
  ma[0][0]=chu[z][17-c]; 
  ma[0][1]=chu[x][17-c];     
  ma[0][2]=chu[r][17-c];  
  ma[0][3]=chu[t][17-c];  
  ma[0][4]=so[j][17-c]; 
  ma[0][5]=so[k][17-c];     
  ma[0][6]=so[l][17-c];  
  ma[0][7]=so[h][17-c];   
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7];
         } 
  } 
  ma[0][1]=chu[35][0]; 
EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
}
void xuongsosaucaidat(unsigned char z,unsigned char x,unsigned char r
,unsigned char t,unsigned char j,unsigned char k,unsigned char l,unsigned char h)
{
unsigned char a,b,c;
EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
  for(c=0;c<17;c++)
  {
  ma[0][0]=so[z][17-c]; 
  ma[0][1]=so[x][17-c];     
  ma[0][2]=so[r][17-c];  
  ma[0][3]=so[t][17-c];  
  ma[0][4]=so[j][17-c]; 
  ma[0][5]=so[k][17-c];     
  ma[0][6]=so[l][17-c];  
  ma[0][7]=so[h][17-c];   
  for(b=0;b<3;b++){hienthi();}  // hien thi  
       for(a=16;a>1;a--)
         {
           ma[a-1][0]=ma[a-2][0];   
           ma[a-1][1]=ma[a-2][1];     
           ma[a-1][2]=ma[a-2][2];  
           ma[a-1][3]=ma[a-2][3];   
           ma[a-1][4]=ma[a-2][4];     
           ma[a-1][5]=ma[a-2][5];     
           ma[a-1][6]=ma[a-2][6];   
           ma[a-1][7]=ma[a-2][7];
         } 
  } 
  ma[0][1]=chu[35][0];   
  EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
}


void laydosang()
{ 
  if(docdulieu(24) > 10){ghidulieu(24,3);}
  dosang=docdulieu(24);
     switch (dosang) 
     {
      case 1:{sang=5;break;}  
      case 2:{sang=10;break;}  
      case 3:{sang=30;break;}  
      case 4:{sang=80;break;}  
      case 5:{sang=150;break;} 
      case 6:{sang=300;break;} 
      case 7:{sang=400;break;}  
      case 8:{sang=600;break;}  
      case 9:{sang=800;break;}
      case 10:{sang=1000;break;}
    }; 

}



void caidosang()
{
  unsigned char a;
  xuongchuluccaidatds(45,44,27,'S'-65,11,dosang/10,dosang%10,11); 
  while(1)
  {
   hienthi();
   if(up==0 || nut ==20)
   {  
    EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>       
    nut=0;
    while(up==0){hienthi();} 
    dosang++;if(dosang>10)dosang=1;ghidulieu(24,dosang);laydosang();  
    for(a=1;a<17;a++)
      { 
      ma[a-1][5]=so[dosang/10][a-1];
      ma[a-1][6]=so[dosang%10][a-1];       
     }  
     EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>   
   }   
   if(down==0 || nut ==21)
   {  
    EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>       
    nut=0;
    while(down==0){hienthi();} 
    dosang--;if(dosang==0)dosang=10;ghidulieu(24,dosang);laydosang();   
     for(a=1;a<17;a++)
      { 
      ma[a-1][5]=so[dosang/10][a-1];
      ma[a-1][6]=so[dosang%10][a-1];       
     }
     EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>     
   } 
   if(ok==0 || nut ==22)
   {  
     nut=0;
     while(ok==0){hienthi();} 
     return;
   } 
  }
}
void hoclenh()
{
  lenhIRcu=lenhIR=0;   
  ghidulieu(0x20,0); 
  ghidulieu(0x21,0);
  ghidulieu(0x22,0);
  ghidulieu(0x23,0);
  
  xuongchuluccaidat('C'-65,35,'I'-65,29,29,29,'U'-65,'P'-65); 
  while(1)
  {    
      hienthi();
      if(lenhIR!=lenhIRcu)
      {
         lenhIRcu=lenhIR;
         ghidulieu(20,lenhIR);         
         xuongchuluccaidat('C'-65,35,'I'-65,29,'D'-65,'O'-65,'W'-65,'N'-65);   
         while(1)
         {
             hienthi();
              if(lenhIR!=lenhIRcu)
               {  
                 lenhIRcu=lenhIR;
                 ghidulieu(21,lenhIR);
                 xuongchuluccaidat('C'-65,35,'I'-65,29,29,29,'O'-65,'K'-65);      
                  while(1)
                   {
                     hienthi();
                     if(lenhIR!=lenhIRcu && lenhIR!=docds(20) )
                       {  
                         lenhIRcu=lenhIR;
                         ghidulieu(22,lenhIR); 
                         xuongchuluccaidat('C'-65,35,'I'-65,29,29,'O'-65,'F'-65,'F'-65);      
                         while(1)
                         { 
                            hienthi();    
                            if(lenhIR!=lenhIRcu && lenhIR!=docds(20) && lenhIR!=docds(21))
                            {
                              ghidulieu(23,lenhIR);  
                              goto thoathoclenh;
                            } 
                         }
                         
                       }   
                   }
               }     
         }
      }  
  } 
  thoathoclenh:;
}


void laybaothuc_laybugio()
{
 if(docdulieu(25)>59)ghidulieu(25,0);
 if(docdulieu(26)>59)ghidulieu(26,0);  
 if(docdulieu(27)>59)ghidulieu(27,0);
 if(docdulieu(28)>1)ghidulieu(28,0); 
 if(docdulieu(29)>31)ghidulieu(29,0);
 if(docdulieu(30)>12)ghidulieu(30,0);
 if(docdulieu(31)>1)ghidulieu(31,0);
 if(docdulieu(32)>1)ghidulieu(32,0);
 if(docdulieu(33)>1)ghidulieu(33,1);  
 if(docdulieu(34)>1)ghidulieu(34,1);
 giobt=docdulieu(25);      
 phutbt=docdulieu(26);
 bugio=docdulieu(27);      
 am=docdulieu(28);   
 ngaysinhnhat=docdulieu(29);   
 thangsinhnhat=docdulieu(30);            
 trangthaibaothuc=docdulieu(31); 
 trangthaisinhnhat=docdulieu(32);  
 trangthaiauto=docdulieu(33);    
 hieuungchuyengiay=docdulieu(34);  
}

//--------------------------------------------------------ham cai bao thuc------------------------//
void caibaothuc()
{
  unsigned char a,b,c;                     
  xuongchuluccaidatds('G'-65,'I'-65,43,29,11,giobt/10,giobt%10,11);    
  ma[0][1]=chu['I'-65][0];     
  ma[0][2]=chu[43][0];     
  while(1)
  {
    hienthi();
     if(up==0 || nut ==20)
     {  
      EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
      nut=0;    
      while(up==0){hienthi();}
      giobt++;if(giobt>23)giobt=0;           
       for(c=0;c<17;c++)
          {
          ma[0][5]=so[giobt/10][17-c];ma[0][6]=so[giobt%10][17-c];     
          for(b=0;b<3;b++){hienthi();}  // hien thi 
          for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
          }  
          EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
     } 
     if(down==0 || nut ==21)
     {    
      EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
      nut=0;    
      while(down==0){hienthi();}
      if(giobt>0)giobt--;else giobt=23;         
      for(c=0;c<15;c++)
          {
          ma[15][5]=so[giobt/10][c];ma[15][6]=so[giobt%10][c];     
          for(b=0;b<3;b++){hienthi();}  // hien thi 
          for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
          } 
      EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
     } 
     if(ok==0 || nut ==22)
     {       
        nut=0;           
        while(up==0){hienthi();}
        xuongchuluccaidatds('P'-65,'H'-65,33,'T'-65,11,phutbt/10,phutbt%10,11); 
        ma[0][1]=0xFF;;     
        ma[0][2]=0xF9;                
        while(1)
          {
            hienthi();
            {
             if(up==0 || nut ==20)
             {
              EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
              nut=0;    
              while(up==0){hienthi();}
              phutbt++;if(phutbt>59)phutbt=0;           
               for(c=0;c<17;c++)
                  {
                  ma[0][5]=so[phutbt/10][17-c];ma[0][6]=so[phutbt%10][17-c];     
                  for(b=0;b<3;b++){hienthi();}  // hien thi 
                  for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
                  }
               EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
             } 
             if(down==0 || nut ==21)
             {   
              EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
              nut=0;    
              while(down==0){hienthi();}
              if(phutbt>0)phutbt--;else phutbt=59;       
              for(c=0;c<15;c++)
                  {
                  ma[15][5]=so[phutbt/10][c];ma[15][6]=so[phutbt%10][c];     
                  for(b=0;b<3;b++){hienthi();}  // hien thi 
                  for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
                  }
              EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
             } 
             if(ok==0 || nut ==22)
             {     
                EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328> 
                nut=0;            
                while(up==0){hienthi();}
                ghidulieu(25,giobt);
                ghidulieu(26,phutbt);     
                EIMSK=0x01;  //cho phep ngat ngoai 0  <at328>
                return;
             }
            }
          }
    }
 }
 }   
 
//---------------------ham kiem tra bao thuc---------------//
 void tinhbaothuc()
 {
  if(gio==giobt && phut==phutbt && trangthaibaothuc==1 )
  {
      if(cobaosinhnhat==0)
      {
       chucmungbuoisang();
       delay_ms(500);
       chucmungbuoisang();     
      }
      else
      {
       chucmungsinhnhat();
       delay_ms(500);
       chucmungsinhnhat();     
      }  
      laythoigiantrongds3();
  }
 }   
 

//----------------------------------ham cai bu gio--------------------------------//
 void caibugio()
 {
  unsigned char a,b,c;
  xuongchuluccaidatds('B'-65,46,29,29,13-am,bugio/10,bugio%10,11); 
  ma[0][1]=chu[46][0];  
  ma[0][2]=0xFF;;   
  while(1)
  {
    hienthi();
     if(up==0 || nut ==20)
     {
      EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
      nut=0;    
      while(up==0){hienthi();}   
      if(bugio<59)
      {    
          bugio++;
          for(c=0;c<17;c++)
          {
          ma[0][5]=so[bugio/10][17-c];ma[0][6]=so[bugio%10][17-c];     
          for(b=0;b<3;b++){hienthi();}  // hien thi 
          for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}  
          }  
      } 
      else
      {
         bugio=0; am=1-am; 
         xuongchuluccaidatds('B'-65,46,29,29,13-am,bugio/10,bugio%10,11);       
         ma[0][1]=chu[46][0];  
         ma[0][2]=0xFF;;
      }
      EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
     } 
     
    if(down==0 || nut ==21)
     {   
      EIMSK=0x00;  // cho phep ngat ngoai 0  <at328>
      nut=0;    
      while(down==0){hienthi();}   
      if(bugio>0)
      {    
          bugio--;
          for(c=0;c<15;c++)
              {
              ma[15][5]=so[bugio/10][c];ma[15][6]=so[bugio%10][c];     
              for(b=0;b<3;b++){hienthi();}  // hien thi 
              for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
              }
      } 
      else
      {
         bugio=59; am=1-am; 
         xuongchuluccaidatds('B'-65,46,29,29,13-am,bugio/10,bugio%10,11);   
         ma[0][1]=chu[46][0];  
         ma[0][2]=0xFF;;
      }     
      EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
     }     
       
    if(ok==0 || nut ==22)
     {   
      EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
      nut=0;    
      ghidulieu(28,am);
      ghidulieu(27,bugio);
      while(ok==0){hienthi();}    
      return; 
      EIMSK=0x01;  // k cho phep ngat ngoai 0  <at328>
     }
  } 
 }

//--------------------------Kiem tra bu gio-----------------------------//
 void tinhbugio()
 {
  if(gio==3 && phut == 4 && giay ==5)
  {
   if(am==0)
   {
     if((giay+bugio)>59)
     {
      giay=(giay+bugio)-59;
      phut++;       
     }       
     else giay=giay+bugio;
   } 
   else if(am==1)
   {
     if(bugio>giay)
     {
      giay=59-(bugio-giay);
      phut--;
     }       
     else giay=giay-bugio;
   }
   ghids(0x00,giay);
   ghids(0x01,phut);
  }
 }

//-----------------------------------------------Cai sinh nhat----------------------
void caisinhnhat()
{
  unsigned char a,b,c;                     
  xuongchuluccaidatds('N'-65,'G'-65,35,'Y'-65,11,ngaysinhnhat/10,ngaysinhnhat%10,11);         
  ma[0][2]=chu[35][0];   
  ma[0][1]=0xff;    
  while(1)
  {
    hienthi();
     if(up==0 || nut ==20)
     {  
      EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
      nut=0;    
      while(up==0){hienthi();}  
      ngaysinhnhat++;if(ngaysinhnhat>31)ngaysinhnhat=0;           
       for(c=0;c<17;c++)
          {
          ma[0][5]=so[ngaysinhnhat/10][17-c];ma[0][6]=so[ngaysinhnhat%10][17-c];     
          for(b=0;b<3;b++){hienthi();}  // hien thi 
          for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
          } 
       EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
     } 
     if(down==0 || nut ==21)
     { 
      EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
      nut=0;    
      while(down==0){hienthi();}
      if(ngaysinhnhat>0)ngaysinhnhat--;else ngaysinhnhat=31;         
      for(c=0;c<15;c++)
          {
          ma[15][5]=so[ngaysinhnhat/10][c];ma[15][6]=so[ngaysinhnhat%10][c];     
          for(b=0;b<3;b++){hienthi();}  // hien thi 
          for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
          } 
      EIMSK=0x01;  //cho phep ngat ngoai 0  <at328>
     } 
     if(ok==0 || nut ==22)
     {    
        nut=0;           
        while(up==0){hienthi();}
        xuongchuluccaidatds('T'-65,'H'-65,36,'G'-65,11,thangsinhnhat/10,thangsinhnhat%10,11);  
        ma[0][1]=0xff;   
        ma[0][2]=chu[36][0];                
        while(1)
          {
            hienthi();
            {
             if(up==0 || nut ==20)
             {  
              EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
              nut=0;    
              while(up==0){hienthi();}
              thangsinhnhat++;if(thangsinhnhat>12)thangsinhnhat=0;           
               for(c=0;c<17;c++)
                  {
                  ma[0][5]=so[thangsinhnhat/10][17-c];ma[0][6]=so[thangsinhnhat%10][17-c];     
                  for(b=0;b<3;b++){hienthi();}  // hien thi 
                  for(a=16;a>1;a--){ma[a-1][5]=ma[a-2][5];ma[a-1][6]=ma[a-2][6];}
                  }  
               EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
             } 
             if(down==0 || nut ==21)
             {  
              EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
              nut=0;    
              while(down==0){hienthi();}
              if(thangsinhnhat>0)thangsinhnhat--;else thangsinhnhat=12;       
              for(c=0;c<15;c++)
                  {
                  ma[15][5]=so[thangsinhnhat/10][c];ma[15][6]=so[thangsinhnhat%10][c];     
                  for(b=0;b<3;b++){hienthi();}  // hien thi 
                  for(a=0;a<15;a++){ma[a][5]=ma[a+1][5];ma[a][6]=ma[a+1][6];}
                  }   
              EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
             } 
             if(ok==0 || nut ==22)
             {   
                EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>   
                nut=0;            
                while(up==0){hienthi();}
                ghidulieu(29,ngaysinhnhat);
                ghidulieu(30,thangsinhnhat);     
                EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
                return;
             }
            }
          }
    }
 }
 } 
  
void caitrangthai()
{               
  xuongchuluccaidatds('B'-65,27,'T'-65,29,11,11,11,11);         
  ma[0][1]=chu[27][0];    
  if(trangthaibaothuc==1){thanhtruotbat();}  
  else thanhtruottat();
  while(1)
  {
   hienthi();
   if(up==0 || down ==0 || nut==20 || nut==21)
   {  
     nut=0;
     while(up==0 || down==0){hienthi();}  
     trangthaibaothuc=1-trangthaibaothuc; // ~ trangthaibaothuc 
     if(trangthaibaothuc==1){thanhtruotbat();}  
     else thanhtruottat();
   }    
   if(ok==0 || nut ==22)
   {
     nut=0;
     while(ok==0){hienthi();}      
     xuongchuluccaidatds('S'-65,27,'N'-65,29,11,11,11,11);         
     ma[0][1]=chu[27][0];    
     if(trangthaisinhnhat==1){thanhtruotbat();}  
     else thanhtruottat();
     while(1)
      {
       hienthi();
       if(up==0 || down ==0 || nut==20 || nut==21)
       {
         nut=0;
         while(up==0 || down==0){hienthi();}         
          trangthaisinhnhat=1-trangthaisinhnhat; // ~ trangthai sinh nhat
          if(trangthaisinhnhat==1){thanhtruotbat();}  
          else thanhtruottat();
       }
       if(ok==0 || nut ==22)
       {
         nut=0;
         while(ok==0){hienthi();}      
         xuongchuluccaidatds('A'-65,'U'-65,'T'-65,'O'-65,11,11,11,11);         
         ma[0][1]=0xff;   
         ma[0][0]=0xff; 
         if(trangthaiauto==1){thanhtruotbat();}  
         else thanhtruottat();  
         while(1)
          {
           hienthi();
           if(up==0 || down ==0 || nut==20 || nut==21)
           {
             nut=0;
             while(up==0 || down==0){hienthi();}         
              trangthaiauto=1-trangthaiauto; // ~ trangthaiauto
              if(trangthaiauto==1){thanhtruotbat();}  
              else thanhtruottat();
           }
           if(ok==0 || nut==22)
           {
            nut=0;
            while(ok==0){hienthi();}    
            xuongchuluccaidatds('E'-65,27,'F'-65,29,11,11,11,11);         
            ma[0][1]=chu[27][0];    
            if(hieuungchuyengiay==1){thanhtruotbat();}  
            else thanhtruottat();  
            while(1)
            {
             hienthi();
             if(up==0 || down ==0 || nut==20 || nut==21)
               {
                 nut=0;
                 while(up==0 || down==0){hienthi();}         
                  hieuungchuyengiay=1-hieuungchuyengiay; // ~ trangthaihieu ung
                  if(hieuungchuyengiay==1){thanhtruotbat();}  
                  else thanhtruottat();
               } 
             
              if(ok==0 || nut==22)
               {
                nut=0;
                while(ok==0){hienthi();}  
                ghidulieu(31,trangthaibaothuc);  
                ghidulieu(32,trangthaisinhnhat); 
                ghidulieu(33,trangthaiauto); 
                ghidulieu(34,hieuungchuyengiay);
                return;  
               }  
           }
          } 
         }
          
           
       }
      }
      
       
   }
  }  
}


//--------------------------ham Bat Tat dong ho--------------//
void tatnguon()
{
 if(nut==23)
 {  
  nut=0;
  while(1)
  {
   if(nut==23)
   {    
    EIMSK=0x00;  // k cho phep ngat ngoai 0  <at328>
    nut=0;     
    xuongsosaucaidat(gio/10,gio%10,10,phut/10,phut%10,10,giay/10,giay%10);   
    ma[0][1]=0xff;     
    EIMSK=0x01;  //  cho phep ngat ngoai 0  <at328>
    return;
   }
  }
 }
}

//------------------------end------------------------------//

void caidat()
{
 unsigned char d;
 if(ok==0 || nut==22)   // neu nut ok dc nhan hoac hong ngoai co gia tri ==22
 {   
  nut=0; // tra hong ngoai ve 0
  while(ok==0){hienthi();}        
  xuongchuluccaidat('C'-65,35,'I'-65,29,'T'-65,'H'-65,43,'I'-65);
   while(1)
   {
    for(d=0;d<88;d++)
    {
     chaychu5();
     if(cobaothoat==1){cobaothoat=0;break;}
     if(down==0 || ok==0)break;
    }dem=0;dem1=0;     
    if(ok==0 || nut == 22)
    {   
     nut=0;
     while(ok==0){hienthi();}   
     caigio();   
     goto thoat;
    }
    
    if(down==0 || nut == 21)
    {     
     nut=0;
     while(down==0){hienthi();}  
     xuongchuluccaidat('C'-65,35,'I'-65,29,45,'O'-65,29,'S'-65);   
      while(1)
      {
           for(d=0;d<70;d++)
            {
             chaychu6();
             if(cobaothoat==1){cobaothoat=0;break;}
             if(down==0 || ok==0)break;
            }dem=0;dem1=0;   
           if(ok==0 || nut==22)
            {   
             nut=0;
             while(ok==0){hienthi();}  
             caidosang();
             goto thoat;
            }
            if(down==0||nut==21)
            {   
             nut=0;
             while(down==0){hienthi();}  
             xuongchuluccaidat('C'-65,35,'I'-65,29,'B'-65,36,'O'-65,29);   
              while(1)
              { 
                    for(d=0;d<77;d++)
                    {
                     chaychu7();   
                     if(cobaothoat==1){cobaothoat=0;break;}   
                     if(down==0 || ok==0)break;
                    }dem=0;dem1=0;   
                    if(ok==0 || nut ==22 )
                    {                   
                     nut=0;   
                     caibaothuc();
                     while(ok==0){hienthi();}       
                     goto thoat;
                    } 
                   if(down==0 || nut==21)
                    {     
                     nut=0;
                     while(down==0){hienthi();}  
                     xuongchuluccaidat('C'-65,35,'I'-65,29,'B'-65,46,29,'G'-65);  
                     ma[0][4]=chu[46][0]; 
                      while(1)
                      { 
                       hienthi();
                       for(d=0;d<64;d++)
                         {
                          chaychu8(); 
                          if(cobaothoat==1){cobaothoat=0;break;}  
                          if(down==0 || ok==0)break;
                         }dem=0;dem1=0;   
                         if(ok==0 || nut ==22)
                          { 
                            nut=0;
                            while(ok==0){hienthi();}       
                            caibugio();
                            goto thoat;
                          }    
                          if(down==0 || nut ==21)
                            {      
                             nut=0;
                             while(down==0){hienthi();}  
                             xuongchuluccaidat('C'-65,35,'I'-65,29,'L'-65,47,'N'-65,'H'-65);  
                             ma[0][5]=chu[47][0]; 
                              while(1)
                              { 
                                 hienthi(); 
                                 if(ok==0 || nut ==22)
                                  {   
                                    nut=0;
                                    while(ok==0){hienthi();}  
                                    chedohoclenh=1;     
                                    hoclenh(); 
                                    chedohoclenh=0;
                                    goto thoat;
                                  }  
                                  if(down==0 || nut ==21)
                                  {   
                                    nut=0;
                                    while(ok==0){hienthi();}     
                                    xuongchuluccaidat('C'-65,35,'I'-65,29,29,'S'-65,'N'-65,29);
                                    ma[0][1]=chu[35][0];        
                                    ma[0][2]=0xff;;    
                                  while(1)    
                                   {
                                         hienthi(); 
                                         if(ok==0 || nut ==22)
                                          {   
                                            nut=0;
                                            while(ok==0){hienthi();}    
                                            caisinhnhat(); 
                                            goto thoat;
                                          }   
                                          if(down==0 || nut ==21)
                                     {   
                                            nut=0;
                                            while(down==0){hienthi();}     
                                            xuongchuluccaidat('C'-65,35,'I'-65,29,'T'-65,'R'-65,49,'N'-65); 
                                            ma[0][1]=chu[35][0];   
                                            ma[0][2]=0xff;;    
                                            while(1)
                                            {
                                              hienthi(); 
                                              for(d=0;d<98;d++)
                                             {
                                              chaychutrangthai(); 
                                              if(cobaothoat==1){cobaothoat=0;break;}  
                                              if(down==0 || ok==0)break;
                                             }dem=0;dem1=0;   
                                             if(ok==0 || nut ==22)
                                              {   
                                                nut=0;
                                                while(ok==0){hienthi();}    
                                                caitrangthai(); 
                                                goto thoat;
                                              }   
                                              if(down==0 || nut ==21)
                                              {   
                                               nut=0;
                                               while(down==0){hienthi();}  
                                               goto thoat;   
                                              }  
                                          }  
                                      }
                                    } 
                                  }    
                                  
                              } 
                            }
                          
                      } 
                    }
                  
              } 
            }
      } 
    }         
   }    
  thoat:;     
  giay=docds(0x00);
  xuongsosaucaidat(gio/10,gio%10,10,phut/10,phut%10,10,giay/10,giay%10);    
  ma[0][1]=0xff;
 }      
}

interrupt [EXT_INT0] void Ngat_Ngoai_0(){
    unsigned int pulse_width; 
    unsigned char docirtrongbonho; 
    TCCR1B = 0x00; //Stop Timer 1
    pulse_width = TCNT1L + (TCNT1H*256);
    TCNT1H=0x63;
    TCNT1L=0xC0;   
    
    TCCR1B = 0x02;      // kich hoat timer /8
    pulse_width = pulse_width - 25536;
    switch(IRI){
        case 0: 
                IRI=1;
                break; 
        case 1: 
                if(pulse_width > 4000){
                    IRI=2;    
                    giatri=0;
                }
                else
                    IRI--;
                break;
        case 2: 
                    giatri <<= 1;
                    if(pulse_width > 3000)
                    giatri |= 1;
                    break;
        case 3:       
                IRI=0;  
                lenhIR=giatri; 
                if(chedohoclenh==0)
                {    
                  nut=0;
                  for(docirtrongbonho=20;docirtrongbonho<24;docirtrongbonho++)
                  {
                   if(docdulieu(docirtrongbonho)==lenhIR)
                   {
                     nut=docirtrongbonho;   
                     cobaothoat=1; 
                     break;
                   }                 
                  }
                }
                break;
    }
    
}

interrupt [TIM1_OVF] void Ngat_Timer_1()
{
    TCCR1B = 0x00;
    if(IRI == 1) IRI=0;
    else if(IRI == 2) IRI=3;
}


void tudong()
{
 if(trangthaiauto==1)
 {
    if(gio==6 && phut == 0 && giay <5 ){sang=30;}
    else if(gio == 10 && phut==0 && giay<5){sang=5;hieuungchuyengiay=0;}
    else if(gio == 5 && phut == 30 && giay<5){sang=200;hieuungchuyengiay=1;}
 }
}


void main(void)
{
unsigned char v;
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif


PORTB=0xFF;       // cong B la out put
DDRB=0xFF;

PORTC=0x7F;    // 3 bit dau la IN, con lai Out
DDRC=0x78;

PORTD=0xFF;     //bit thu hai la In , con lai Out
DDRD=0xFB;


// KHOI TAO TIMER1  
TCCR0A=0x00;
TCCR0B=0x00;        // dung timer   // = 0x04 de kich hoat timer /255

TCCR1A=0x00;
TCCR1B=0x00;        // dung timer   // = 0x02 de kich hoat timer /8

//TIMSK=0x05;    // Kich hoat ngat tran TIMER1 va timer 0 cua at8     ( 0x04 la timer 1 | 0x05 la ca 2 time 1 va 0 )
TIMSK0=0x01;  // kich hoat ngat tran t0
TIMSK1=0x01;  // kich hoat ngat tran t1


EIMSK=0x01;  // cho phep ngat ngoai 0  <at328>
EICRA=0x02; //EX0 ngat canh xuong <AT328>

//GICR=0x40; //cho phep ngat ngoai 0 < at8>
//MCUCR=0x02; // ngat canh xuong AT8
#asm("sei")    // Kich hoat ngat toan cuc

i2c_init();     // khoi tao i2c
laydosang(); 
laybaothuc_laybugio();
laythoigiantrongds1();
int_ds18b20();
laynhietdo();


chaychudongholed();
for(v=0;v<100;v++){hienthi();}      // hien thi ra ngoai    
chaychuwwebsite(); 
while (1)
       {       
         tinhbaothuc(); 
         laythoigiantrongds();     
         tinhbugio();            
         if(giay==10 && hieuungchuyengiay!=0)
         {
          chayngaythang();     
          giay=docds(0);
         }
         if(hieuungchuyengiay==1){if(giay!=giaycu){giaycu=giay;if((phut%2)==1)quetchu(); else lattrang();}} 
         else {ghithoigian();}  
         hienthi();  
         caidat();         
         tatnguon();  
         tudong(); 
                                     
       }
}