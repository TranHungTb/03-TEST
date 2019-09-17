/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
Servo myservo;   


int servoPin = D1; 


void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
    Serial.println();
  delay(10);
  myservo.attach(servoPin); 
  
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("GFD Office Network", "gfd@1352468");

  
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://138.197.46.187:1347/level")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          
          Serial.println(payload);
          int val=1;
          if (payload.indexOf("level:1") != -1) {
            val = 1;
            // vô hiệu hóa D0( chân led D0 có sẵn nối dương nên ta kích 1 thì led tắt)
            myservo.write(val*2*18-18);
          }
          
          else if (payload.indexOf("level:2") != -1) {
            val = 2;
            // Bật D0
            myservo.write(val*2*18-18);
          }
          else if (payload.indexOf("level:3") != -1) {
            val = 3;
            // Bật D0
            myservo.write(val*2*18-18);
          }
          else if (payload.indexOf("level:4") != -1) {
            val = 4;
            // Bật D0
            myservo.write(val*2*18-18);
          }
          else if (payload.indexOf("level:5") != -1) {
            val = 5;
            // Bật D0
            myservo.write(val*2*18-18);
          }
          else {
            Serial.println("[-] Yêu cầu không hợp lệ");
          }
         
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
     
      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
