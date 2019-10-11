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

void waitUntilReady();

void setup();
void loop();
const int maxAllowedWrites = 80;
const int memBase          = 350;

int addressByte;
int addressInt;
int addressLong;
int addressFloat;
int addressDouble;
int addressByteArray;
int addressCharArray;
    char input[] = "0929034450";
    char output[] = "";

// Test reading and writing byte to EEPROM

// Test reading and updating a string (char array) to EEPROM
void writeAndReadCharArray() {
    Serial.println("---------------------------------");     
    Serial.println("writing and reading a char array");     
    Serial.println("---------------------------------");     
    


    EEPROM.writeBlock<char>(addressCharArray, input, 10);
    delay(10);
    EEPROM.readBlock<char>(addressCharArray, output, 10);

    Serial.print("adress: ");
    Serial.println(addressCharArray);
    Serial.print("input: ");
    Serial.println(input);
    Serial.print("output: ");
    Serial.println(output);
    Serial.println("");
}


// Check how much time until EEPROM ready to be accessed
void waitUntilReady() { 
    Serial.println("-----------------------------------------------------");     
    Serial.println("Kiểm tra bao nhiêu thời gian cho đến khi EEPROM sẵn sàng để được truy cập");     
    Serial.println("-----------------------------------------------------");      
    int startMillis;
    int endMillis; 
    int waitMillis;

    // Write byte..       
    startMillis = millis();
    EEPROM.writeByte(addressByte,16);
    endMillis = millis();            
    // .. and wait for ready    
    waitMillis = 0;   
    while (!EEPROM.isReady()) { delay(1); waitMillis++; }

    Serial.print("Thời gian để viết 1 byte (ms)  : "); 
    Serial.println(endMillis-startMillis); 
    Serial.print("Thời gian phục hồi sau khi viết byte (ms)             : "); 
    Serial.println(waitMillis);    
            
    // Write long ..       
    startMillis = millis();
    EEPROM.writeLong(addressLong,106);
    endMillis = millis();               
    // .. and wait for ready    
    waitMillis = 0;   
    while (!EEPROM.isReady()) { delay(1); waitMillis++; }
    Serial.print("Thời gian để viết Dài (4 byte) (ms)                 : "); 
    Serial.println(endMillis-startMillis); 
    Serial.print("Thời gian phục hồi sau khi viết dài (ms)             : "); 
    Serial.println(waitMillis);    
    
    // Read long ..
    startMillis = millis();
    EEPROM.readLong(addressLong);
    endMillis = millis();
    // .. and wait for ready      
    waitMillis = 0;   
    while (!EEPROM.isReady()) { delay(1); waitMillis++; }
    Serial.print("Thời gian để đọc Dài (4 byte) (ms)                : ");    
    Serial.println(endMillis-startMillis);     
    Serial.print("Thời gian phục hồi sau khi đọc dài (ms)            : "); 
    Serial.println(waitMillis);      
 
    // Write times arrays 
    int itemsInArray = 7;
    byte array7[]    = {64, 32, 16, 8 , 4 , 2 , 1 };
    byte arraydif7[] = {1 , 2 , 4 , 8 , 16, 32, 64};    
    byte arrayDif3[] = {1 , 0 , 4 , 0 , 16, 0 , 64};
    byte output[sizeof(array7)];

    // Time to write 7 byte array 
    startMillis = millis();
    EEPROM.writeBlock<byte>(addressByteArray, array7, itemsInArray);
    endMillis = millis(); 
    Serial.print("Thời gian để viết mảng 7 byte (ms)               : ");    
    Serial.println(endMillis-startMillis); 

    // Time to update 7 byte array with 7 new values
    startMillis = millis();    
    EEPROM.updateBlock<byte>(addressByteArray, arraydif7, itemsInArray);
    endMillis = millis(); 
    Serial.print("Thời gian để cập nhật mảng 7 byte với 7 giá trị mới (ms): ");    
    Serial.println(endMillis-startMillis); 

    // Time to update 7 byte array with 3 new values
    startMillis = millis();    
    EEPROM.updateBlock<byte>(addressByteArray, arrayDif3, itemsInArray);
    endMillis = millis(); 
    Serial.print("Thời gian để cập nhật mảng 7 byte với 3 giá trị mới (ms): ");    
    Serial.println(endMillis-startMillis);

    // Time to read 7 byte array
    startMillis = millis(); 
    EEPROM.readBlock<byte>(addressByteArray, output, itemsInArray);   
    endMillis = millis(); 
    Serial.print("Thời gian để đọc mảng 7 byte (ms)                 : ");    
    Serial.println(endMillis-startMillis);
}


  
void setup()
{
  Serial.begin(9600);

  delay(100);
  Serial.println("");       
  
  // Luôn lấy địa chỉ trước và theo thứ tự
 
//  addressCharArray = EEPROM.getAddress(sizeof(char)*10);  


  // đọc và viết vào eeprom
  writeAndReadCharArray();   
  
  

  
}

void loop()
{
  // Nothing to do during loop
}    
