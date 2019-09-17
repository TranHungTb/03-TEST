#include <Ubidots_Arduino_GPRS.h>
#include <SoftwareSerial.h> 
//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 

#define APN "Your_apn_of_your_SIM_here" 
#define USER "Your_username_here"  // if your apn doesnt have username just put ""
#define PASS "Your_password_here"  // if your apn doesnt have password just put ""
#define TOKEN "Your_token_here"  // Remplace it with your token
#define ID "Your_id_here" // Remplace it with your variable ID

Ubidots client(TOKEN);  
  
void setup() {
  Serial.begin(19200);             // the Serial port of Arduino baud rate.  
  client.powerUpOrDown();
  client.setApn(APN,USER,PASS);
}

void loop() {
  float value = client.getValue(ID);
  Serial.println(value);
  delay(600);  // 600 milliseconds 
  Serial.println(value);
}
