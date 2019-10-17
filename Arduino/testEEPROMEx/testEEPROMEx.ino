/*
 * EEPROMEx 
 *
 * Demonstrates reading, writing and updating data in the EEPROM
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROMex.h>

#include "Arduino.h"

void writeAndReadCharArray();


const int maxAllowedWrites = 80;
const int memBase          = 0;
int addressCharArray;

String a;



// Test reading and updating a string (char array) to EEPROM
void writeAndReadCharArray() {
      
    Serial.println("writing and reading a char array");     
    Serial.println("---------------------------------");     
    
    char input[] = "0929034450";
    char output[] = "";

    EEPROM.writeBlock<char>(addressCharArray, input, 10);
    EEPROM.readBlock<char>(addressCharArray,output,10);

    Serial.print("adress: ");
    Serial.println(addressCharArray);
    Serial.print("input: ");
    Serial.println(input);
    Serial.print("output: ");
    Serial.println(output);
    a = output;
    Serial.print("output22: ");
    Serial.println(a);
    
    Serial.println("");
}

void setup()
{
  Serial.begin(9600);

  EEPROM.setMemPool(memBase, EEPROMSizeUno);
  

  EEPROM.setMaxAllowedWrites(maxAllowedWrites);
  delay(100);
  Serial.println("");       
  
  // Luôn lấy địa chỉ trước và theo cùng một thứ tự
  addressCharArray = EEPROM.getAddress(sizeof(char)*10);  

  // Đọc và viết các mảng dữ liệu khác nhau
  writeAndReadCharArray();    
 
}

void loop()
{
  // Nothing to do during loop
}

void StringToChar(String string, char s){
   char s[]="";
   int i; 
    /for (i = 0; i < string.length() ; i++) { 
      // chữ số có ý nghĩa nhất của bài đọc nằm ở vị trí 15 trong báo cáoString:
  char mostSignificantDigit = string.charAt(i);
        s[i] = mostSignificantDigit;
        Serial.println( s[i]); 
    } 
 }
